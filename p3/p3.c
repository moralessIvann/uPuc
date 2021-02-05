/* Morales Rosales Iván A
   1231098
   P3 Sección de memoria (prueba de memoria RAM)
   uPuC */
   
/* PEEK- a memory function that returns the byte stored at a specified memory location */
extern unsigned char peek(unsigned int segment, unsigned int offset); 

/* POKE- a memory statement that writes a byte into a memory location */
extern void poke(unsigned int segment, unsigned int offset, unsigned char data); 

extern void putchar(char c);
extern char getchar(void);
void puts(const char *str);


void printDataBusTest(unsigned char status);
void printAddressBusTest(unsigned int successAddress);
unsigned char dataBusTest(const unsigned int segment, const unsigned int offset);
unsigned int addressBusTest(const unsigned int segment,const unsigned int offset);

const unsigned int segment = 0;
const unsigned int offset = 0x2200; /* AD9 fail in 2200h  2800*/
unsigned int  var = 0;

int main(void)
{
	while(1){
		
		getchar();
		printDataBusTest(dataBusTest(segment,offset)); /* print data bus status */
		puts("\n\r");
		
		if(var==1){
			return  var=0;
		}
		else{
			printAddressBusTest(addressBusTest(segment,offset)); /* print address bus status */
		}
	}
	return 0;
}


unsigned char dataBusTest(const unsigned int segment, const unsigned int offset){ /* test data bus performing a walking 1's test */
	
	unsigned char pattern, successDataBus=0; /* pattern is data bus width (8 bits) */
	
	for(pattern=1; pattern!=0; pattern<<=1){ 
		poke(segment,offset,pattern); /* write the test pattern */
		
		if(peek(segment,offset) != pattern) /* read pattern back and compare */
			successDataBus |= pattern;/* se va a ir sumando el patron a la otra variable */
	}
	return successDataBus; /*returns 0 if the test succeeds, else returns 0x20 (0010 0000) means dataline 5 failed*/
}


void printDataBusTest(unsigned char successDataBus){ /* print results from testing data bus */
	
	unsigned char i=0;
	
	if(successDataBus == 0xFF){
		var=1;
		puts("CATASTROPHIC ERROR\n");
		puts("\n\r");
		return;
	}
	
	
	puts("****Data test****\n\r");
	while(i<8){
		putchar(i+'0'); 
		if(successDataBus & (0x01<<i)) 		
			puts(" Data line failed");		
		else								 
			puts(" Data line passed");	
		i++;
		puts("\n\r");
	}
}

unsigned int addressBusTest(const unsigned int segment,const unsigned int offset){ /* test address bus performing a walking 1's test */
	
	unsigned int successAddress=0, i; /* initialize in 0 (means succeeds), i: offset to test */
	unsigned char pattern=0xAA; 
	
		for(i=1; i<(1<<11); i<<=1)/* write the default pattern at each of the power-of-two offsets */
			poke(segment,offset+i,successAddress); /* write in locations */

		poke(segment,offset,pattern); /* write pattern */
		
		for(i=1; i<(1<<11); i<<=1){
			if(peek(segment,offset+i) == pattern || peek(segment,offset+i) != 0)/* cmp pattern wrote in locations with pattern */
					successAddress |= i;
		}
	return successAddress; /* returns 0 if the test succeeds, else returns address that failed */
}	

void printAddressBusTest(unsigned int successAddress){
	
	unsigned int i=0;
	puts("****Address test****\n\r");
	while(i<11){
		putchar((i>9) ? i+'0'+7 : i+'0');
		if(successAddress & (0x0001<<i))
			puts(" Address line failed");			
		else								 
			puts(" Address line passed");	
		i++;
		puts("\n\r");	
	}
	puts("\n\r");
}

void puts(const char *str){
	while(*str)
		putchar(*str++);
}
