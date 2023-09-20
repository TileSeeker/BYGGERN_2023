#include "uart_lib.h"

#define F_CPU 4915200UL //4.9152MHz
#define BAUD 9600
#define BAUD_PRESCALE ((F_CPU / (BAUD * 16UL)) - 1)
volatile uint8_t transmissionComplete = 1;

static int UART_transmit(char message, FILE *stream) {
	//Wait for prev transmission to complete
	while (!transmissionComplete);
	//Set TXC flag to indicate busy
	transmissionComplete = 0;
	
	//Put data into UDR buffer, sends the data
	UDR0 = message;
	if (message == '\n') {
		UART_transmit('\r', stream);
	}
	return 0;
}

char UART_recive() {
	//Wait for unread data in UDR buffer
	while (!(UCSR0A & (1 << RXC0)));
	
	//Return received data from buffer
	return UDR0;
}

void UART_init() {
	//Set baud rate
	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;
	
	//Enable receiver and transmitter + TX complete interrupt
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << TXCIE0);
	
	//Set frame format: 8-bit data, stop bit = 2_bit
	UCSR0C |= (1 << URSEL0) | (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00); //UCSZ10 -> UCSZ01

	//struct FIFO fifo_tx;
	//init_fifo(&fifo_tx, uart_tx_buffer, buffer_size);
	fdevopen(&UART_transmit, &UART_recive);
}

void uart_send_byte(char data){
	if (UCSR0A & (1<<UDRE0)){ //If Transmit Register is empty-> Load data to TXR
		UDR0 = data;
	}
	else{ //IF TX Register is not empty -> store the data in fifo.
		fifo_push(&fifo_tx, data);
	}
}

int uart_send_byte_printf(char var, FILE *stream){
    if (var == '\n') uart_send_byte('\r');
    uart_send_byte(var);
    return 0;
}

void uart_send_string(char* str){
	int length = strlen(str);
	for (int i=0; i<length;i++){
		uart_send_byte(str[i]);
	}
}

char uart_read_byte(void){
	return fifo_pop(&fifo_rx);
}

ISR (USART0_RXC_vect){
	char data = UDR0;
	fifo_push(&fifo_rx, data);
}

// ISR (USART0_TXC_vect){
// 	if (!(fifo_empty(&fifo_tx))){
// 		UDR0 = fifo_pop(&fifo_tx);
// 	}
// }
	
void init_fifo(struct FIFO* fifo_object, char* array, uint16_t size){
	fifo_object->buffer = array;
	fifo_object->size = size;
	fifo_object->head = 0;
	fifo_object->tail = 0;

	fdevopen(&UART_transmit, &UART_recive);
}

//UART transmission complete interrupt handler
ISR(USART0_TXC_vect) {
	//Set flag to indicate completion
	transmissionComplete = 1;
}