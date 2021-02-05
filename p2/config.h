#ifndef _CONFIG_H
#define _CONFIG_H

extern char getchar(void);
extern void putchar(char data);

typedef struct bullsAndCowsTag{
	unsigned bulls:4; /* dont use: unsigned char bulls:4; */
	unsigned cows:4;  /* dont use: unsigned char cows:4; */
}bullsAndCowsType;

bullsAndCowsType evalBullsAndCows(char *secret, char *guess);
void gets(char *str);
void puts(char *str);
void itoa(unsigned int num, char *str, unsigned char base);
unsigned int atoi(char *str);

#define arraySize 5

#endif
