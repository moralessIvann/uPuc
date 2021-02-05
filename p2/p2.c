
/* Morales Rosales Iván A
   1231098 
   P5a Introducción al intérprete 80X86 sobre la plataforma T-Juino
   uPuC 
*/
#include "config.h"
char secret[5];
char guess[5];
char cad[5];

unsigned int secretNum, guessNum;

int main(void){
	
	char i, j;
	struct bullsAndCowsTag var;
	
	while(1){ /*main loop*/
		puts("Introduce the secrete 4 digits:");
		puts("\n\r");
		
		for(i=0; i<4; i++){  /*get 4 digits for secret num*/
			secret[i] = getchar();
		}
		secret[i] = '\0'; /*end of string*/
		puts("Done.");
		puts("\n\r");
		puts("Guess the 4 digit sequence");
		puts("\n\r");
		puts("Bulls:\tCows:\tGuesses:");
		puts("\n\r");
		i = 0; /*rst var*/
		
		while(i<8){ /*guesses loop*/
			for(j=0; j<4; j++){ /*get digits for guess num*/
			guess[j] = getchar();
			}
			guess[j] = '\0'; /*end of string*/
			var = evalBullsAndCows(secret,guess);
			if(var.bulls == 4){ /*cmp bulls*/
				itoa(var.bulls,cad,10); /*cnvrt to ascii*/
				puts(cad);
				puts("        ");
				itoa(var.cows,cad,10);/*cnvrt to ascii*/
				puts(cad);
				puts("        ");
				puts(guess);
				puts("\n\r");
				puts("You win!");
				puts("\n\r");
				break; /*warning*/
			}else{
				itoa(var.bulls,cad,10);/*cnvrt to ascii*/
				puts(cad);
				puts("        ");
				itoa(var.cows,cad,10);/*cnvrt to ascii*/
				puts(cad);
				puts("        ");
				puts(guess);
				puts("\n\r");
			}
			i++;
		}
	}
	if(i == 8){ /*cmp attempts*/
		puts("You LOOSE!");
		puts("\n\r");
	}	
	return 0;
}


bullsAndCowsType evalBullsAndCows(char *secret, char *guess){
	
	char i, j;
	struct bullsAndCowsTag val;
	val.bulls = 0;
	val.cows = 0;
	
	for(i=0; i<4; i++){ /*main loop*/
		for(j=0; j<4; j++){ /*nested loop to cmp digits*/
			if(secret[i] == guess[j]){ /*cmp digits*/
				if(i == j) /*if equal*/
					val.bulls = val.bulls + 1; /*inc bulls*/
				else
					val.cows = val.cows + 1; /*inc cows*/
			}
		}
	}
	return val;
}


void gets(char *str){
	
	int cnt = 0;
	
	while((str[cnt] = getchar()) != '\r'){ /* check every char received while is not '\r' */
		
		if(str[cnt]=='\b' && cnt>0){ /* cmp if char is '\b' and greater than zero */
			
			putchar(str[cnt--]), putchar(' '), putchar('\b'); 
			/* dec 1position in str, put blankspace, put backspace */
		}
		else if(str[cnt]!='\b' && cnt<arraySize){ /* cmp if char is not '\b' and less str size */
			
			putchar(str[cnt++]); /* inc 1position in str */
		}
	}
	
	str[cnt] = '\0'; /* end str correctly */
	putchar('\n'); /* new line */
	putchar('\r'); /* carriage return */
}

void puts(char *str){
	
	while(*str) /* while theres a char... */
		putchar(*str++); /*... print next char */
}

void itoa(unsigned int num, char *str, unsigned char base){
	
	char reminder = 0;
	char *ptr = str;
	
	do{
		
		reminder = num%base + '0';
		*str++ = (reminder > '9') ? reminder+7:reminder;
		num /= base;

	}while(num > 0);
	
	*str-- = '\0';
	
	while(ptr < str){
		
		reminder = *str;
		*str = *ptr;
		*ptr = reminder;
		ptr++;
		str--;
	}
}

unsigned int atoi(char *str){
	
	unsigned int cnt, num = 0;
	
	for(cnt=0; str[cnt]!='\0' && str[cnt]>47 && str[cnt]<58; cnt++){
		
		num = (num*10) + (str[cnt] - '0');
	}
	return num;
}




