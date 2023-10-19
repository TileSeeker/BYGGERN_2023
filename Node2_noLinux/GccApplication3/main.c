#include "sam.h"
#include "sam_led.h"
#include "uart.h"
#include "can_controller.h"

//MCK = 84MHz & CAN baud rate = 125kbit/s
//16 time quanta | bit time = 1 / 125kbit/S = 8us | Tcsc = bit time / 16 = 500ns | BRP = (Tcsc * MCK) - 1 = (500ns * 84MHz) - 1 = 42 - 1 = 41
//SMP = SAMPLE_1X = 0 | BRP = 41 | SJW = 1 - 1 = 0 | PROPSEG = 2 - 1 = 1 | PS1 = 7 - 1 = 6 | PS2 = 6 - 1 = 5 | 
// -> 0b 00000000 00101001 00000001 01100101 -> 0x290165
#define CAN_BAUDRATE 0x290165

int main(void)
{
	SystemInit();					//Initialize the SAM system
	WDT->WDT_MR |= WDT_MR_WDDIS;	//Disable watchdog timer
	PMC->PMC_WPMR &= ~(0x1);		//WPEN bit clear for PIO write protect mode register 
	
	//Led ON
	led_init();
	
	//UART test
	configure_uart();				//Baudrate = master clock / (16 * clock divider) = 84MHz / (16 * 547) = 9600
	//uart_putchar('A');
	
	//CAN test
	CAN_MESSAGE test = {
		.id = 10,
		.data_length = 3,
		.data[0] = "A",
		.data[1] = "B",
		.data[2] = "A"
	};
	
	can_init_def_tx_rx_mb(CAN_BAUDRATE);
	can_send(&test, 1);
	
    while (1) {
    }
}
