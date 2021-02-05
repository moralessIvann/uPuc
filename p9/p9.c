#include <avr/io.h>
#include "timer0.h"
#include "uart.h"


/* incluir lo necesario para hacer uso de UART0 */
void UART_AutoBaudRate(void);

int main(){
    
	char str[20];
	/* llamar a función para inicializar puertos E/S */
	UART_AutoBaudRate();
	UART_Ini(0,9600,8,0,1); /* llamar a función para inicializar UART0 */
	
    UART_clrscr(0);
    UART_gotoxy(0,5,1);
    UART_puts(0,"Autobauding done. UBRR0=");
    itoa(UBRR0,str,10);
    UART_puts(0,str);
    UART_puts(0,"\n\r");

    Timer0_Ini(); /* Inicializar contador de millis.*/
    Clock_Ini(06,43,00);
	
    while(1){ /* == main loop == */
        if(Timer0_SecFlag()){ /* ¿ha pasado un Segundo? */
			//UART_putchar(0,'Z');
			UART_gotoxy(0,5,2);
			Clock_Update();
            Clock_Display();
            //UART_gotoxy(0,5,3);
        }else
			UART_gotoxy(0,5,3);
			
    } /* fin del loop principal */
    return 0; /* <-- no se llega aquí */
}


