#ifndef _UART_H
#define _UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#define FCPU 16000000
#define MYUBRR(BAUD) (FCPU/16/BAUD-1)
#define BUFFER_SIZE 64
#define IS_BUFFER_EMPTY(buff) (buff.in_idx == buff.out_idx) 		//returns 1 if buffer is empty		
#define IS_BUFFER_FULL(buff) (MOD(buff.in_idx+1) == buff.out_idx)	//returns 1 if buffer is full
#define MOD(n) ((n)&(BUFFER_SIZE-1))

//Colors
#define COLOR_GRAY "30m"
#define COLOR_RED "31m"
#define COLOR_GREEN "32m"
#define COLOR_YELLOW "33m"
#define COLOR_BLUE "34m"
#define COLOR_MAGENTA "35m"
#define COLOR_CYAN "36m"
#define COLOR_WHITE "37m"

#define GRAY 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

typedef struct {
    char buffer[BUFFER_SIZE];
    volatile unsigned char in_idx; //In index
    volatile unsigned char out_idx; //Out index
}ring_buffer_t;

// Prototypes
// Initialization
void UART_Ini(uint8_t com, uint16_t baudrate, uint8_t size, uint8_t parity, uint8_t stop);
void buffer_ini();
void UART_AutoBaudRate();

// Send
void UART_puts(uint8_t com, char *str);
void UART_putchar(uint8_t com, char data);

// Received
uint8_t UART_available(uint8_t com);	//returns 1 if data exists in buffer
char UART_getchar(uint8_t com);
void UART_gets(uint8_t com,char *str);

// Escape sequences
void UART_gotoxy(uint8_t com, uint8_t x,uint8_t y);
void UART_setColor(uint8_t com, uint8_t color);
void UART_clrscr(uint8_t com);

// Utils
void itoa(uint16_t num, char* str, uint8_t base);
uint16_t atoi(char *str);

#endif
