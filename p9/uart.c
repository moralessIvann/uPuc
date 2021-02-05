
#include "uart.h"

ring_buffer_t txBuffer; //transmit buffer
ring_buffer_t rxBuffer; //recieve buffer

void buffer_ini(){
	
    sei(); //__asm__ ("sei");
	txBuffer.in_idx = 0;
	txBuffer.out_idx = 0;
	rxBuffer.in_idx = 0;
	rxBuffer.out_idx = 0;
}

void UART_Ini(uint8_t com, uint16_t baudrate, uint8_t size, uint8_t parity, uint8_t stop){
	
	buffer_ini();
	uint8_t *address;
	uint16_t xUBRR = 0;
	
	//config com
	if(com==0)
		address = (uint8_t *) 0xC0; //UCSR0
	else if(com==1)
		address = (uint8_t *) 0xC8; //UCSR1
	else if(com==2)
		address = (uint8_t *) 0xD0; //UCSR2
	else
		address = (uint8_t *) 0x130; //UCSR3
	
	//enable RX, TX and interrupts
	*(address + 1) |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
	
	//config baudrate
	xUBRR = MYUBRR(baudrate); //get UBRR
	*(address + 5) |= 0; //load UBRRH 4 MSbits
	*(address + 4) |= (uint8_t) xUBRR; //load UBRRL 8 LSbits
	
	//config size
	*(address + 2) &= ~(1<<UCSZ01)&~(1<<UCSZ00);
	*(address + 1) &= ~(1<<UCSZ02);
	switch(size){
		case 5: break;
		case 6: *(address + 2) |=(1<<UCSZ00); break;
		case 7: *(address + 2) |= (1<<UCSZ01); break;
		case 8: *(address + 2) |= (1<<UCSZ01)|(1<<UCSZ00); break;
		default: break;
	}
	
	//config parity
	switch(parity){
		case 0: *(address + 2) &= ~(1<<UPM01)&~(1<<UPM00); break; //disable
		case 1: *(address + 2) |= (1<<UPM01)|(1<<UPM00); break; //odd
		case 2: *(address + 2) |= (1<<UPM01); break; //even
		default: break;
	}
	
	//cofig stop bit
	switch(stop){
		case 1: *(address + 2) &= ~(1<<USBS0); break;
		case 2: *(address + 2) |= (1<<USBS0); break;
		default: break;
	}
}

//Transmit UART0
ISR(SIG_USART0_DATA){ //send data to UARTx

	if(IS_BUFFER_EMPTY(txBuffer)) //if buffer_TX is empty
		UCSR0B &= ~(1<<UDRIE0);	  //disable UDR interrupt
	else{
		txBuffer.out_idx = MOD(txBuffer.out_idx+1); //delimit buffer space  (+1)
		UDR0 = txBuffer.buffer[txBuffer.out_idx]; //out data from buffer to UARTx
	}
}

//Receive UART0
ISR(SIG_USART0_RECV){ //receive data into buffer_RX
	
	//if the buffer is full, the character in the IN index will be overwritten	
	rxBuffer.buffer[rxBuffer.in_idx] = UDR0;	//in data from UARTx to buffer
	if(!IS_BUFFER_FULL(rxBuffer))  				//if buffer is not full 
	    rxBuffer.in_idx = MOD(rxBuffer.in_idx+1); //delimit buffer
}

uint8_t UART_available(uint8_t com){
	
	return IS_BUFFER_EMPTY(rxBuffer); //1 if buffer is not empty ??
}

void UART_putchar(uint8_t com, char data){
    
	while(IS_BUFFER_FULL(txBuffer)); //stay here if buffer_TX is full, otherwise continue...
    txBuffer.buffer[txBuffer.in_idx] = data; //in data
    txBuffer.in_idx = MOD(txBuffer.in_idx+1); //delimit buffer space  (+1)
	UCSR0B |= (1<<UDRIE0);	//enable UDR interrupt
}

char UART_getchar(uint8_t com){
	
	char data = 0;
	while(IS_BUFFER_EMPTY(rxBuffer))  //stay here if buffer is empty
		UART_putchar(com,0);				//NOP

	data = rxBuffer.buffer[rxBuffer.out_idx]; //out data from buffer
   	rxBuffer.out_idx = MOD(rxBuffer.out_idx+1); //delimt buffer
	//UART_putchar(0,data);	/*echo*/
	return data;
}

void UART_gets(uint8_t com, char *str){
    
	char dato = 'a';
    int contador = 0;
	
    while(dato!=13){         //until enter is pressed
        dato = UART_getchar(0);
        if(dato == 8){     //If backspace is pressed
            if(contador > 0){
                str[contador] = 0;
                contador--;
				UART_putchar(com,8);
				dato = ' ';
				UART_putchar(com,dato);
				UART_putchar(com,8);
            }
        }else if(dato != 13){
            if(contador < 19){    //If any other character is pressed
                str[contador]=dato;
                UART_putchar(com,dato);
                contador++;
            }
        }
    }
	str[contador] = 0;
}

void UART_puts(uint8_t com, char *str) {
	
	while(*str)
		UART_putchar(com, *str++);
}

void itoa(uint16_t num, char* str, uint8_t base){ 
   
   int i=0, c=0;
   int aux;

	if(num == 0){
		str[0] = '0';
		str[1] = 0;		
	}else{	
		while (num != 0){ 
			aux = num % base;
			if(aux>9)
				str[i] = (aux-10)+'A';
			else
				str[i] = aux + '0'; 
			
			num = num/base; 
			i++;
		}
		str[i--] = 0;
		
		for(c = 0; c < (i/2)+1; c++){
			aux = str[i-c];
			str[i-c] = str[c];
			str[c] = aux;
		}
	}
}

uint16_t atoi(char *str){
    
	uint16_t numero = 0;
	int i=0;
	while(str[i] >= '0' && str[i] <= '9'){
		numero = (numero*10) + (str[i]-'0');
		i++;
	}
    return numero;
}

void UART_gotoxy(uint8_t com, uint8_t x,uint8_t y){
 
 static char str[] = "\x1b[00;00H";

  /*convert dec to char*/
    str[3] = '0' + y %10;
    y/=10;
    str[2] = '0' + y %10; 

    str[6] = '0' + x %10;
    x/=10;
    str[5] = '0' + x %10; 

  UART_puts(com,str);
}

void UART_setColor(uint8_t com, uint8_t color){
	
	static char *colors[8]={COLOR_GRAY,COLOR_RED,COLOR_GREEN,COLOR_YELLOW,
							COLOR_BLUE,COLOR_MAGENTA,COLOR_CYAN,COLOR_WHITE};
	UART_puts(com,"\033[1;");
	UART_puts(com,colors[color]);
}

void UART_clrscr(uint8_t com){
   
    UART_puts(com,"\x1b[2J");
    UART_puts(com,"\x1b[H");
}
