#include "sam.h"
#include "sam_led.h"
#include "uart.h"
#include "can_controller.h"
#include "printf-stdarg.h"

//MCK = 84MHz & CAN baud rate = 125kbit/s
//16 time quanta | bit time = 1 / 125kbit/S = 8us | Tcsc = bit time / 16 = 500ns | BRP = (Tcsc * MCK) - 1 = (500ns * 84MHz) - 1 = 42 - 1 = 41
//SMP = SAMPLE_1X = 0 | BRP = 41 | SJW = 1 - 1 = 0 | PROPSEG = 2 - 1 = 1 | PS1 = 7 - 1 = 6 | PS2 = 6 - 1 = 5 | 
// -> 0b 00000000 00101001 00000001 01100101 -> 0x290165
#define CAN_BAUDRATE 0x0290165

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
	can_init_def_tx_rx_mb(CAN_BAUDRATE);
	CAN_MESSAGE rec;

	char msg_str[10];
	
	
    while (1) {
		can_receive(&rec, 0);
		itoa((int8_t)rec.data[0], msg_str, 10);
			
		printf("x: %s\t", msg_str);
			
		itoa((int8_t)rec.data[1], msg_str, 10);
		printf("y: %s\r\n", msg_str);

    }
}
