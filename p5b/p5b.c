
#define WORD unsigned int 
#define BYTE unsigned char 

#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43 
#define PTOs_all_out 0x88 /*0x80 1000 1000*/ 

#define PA1PB2 0x89  /*1000 1001*/
#define PB2PC3 0x98  /*1001 1000*/
#define PC3PA1 0x8A  /*1000 1010*/
#define PC4PC3 0x92  /*1001 0010*/
#define capturePC4 0x9B /*1001 1011*/

extern void outportb(WORD port, BYTE data);
extern BYTE inportb(WORD port);
extern void putchar(char c);

void setBitPort(WORD port, BYTE numBit);
void clrBitPort(WORD port, BYTE numBit);
/*void notBitPort(WORD port, BYTE numBit);*/
BYTE testBitPort(WORD port, BYTE numBit);
void printBin(BYTE dato);
void delay(BYTE);

void reverseBitsPort();  /*WORD port*/
void getBit();
void ledsON();

BYTE dato = 0, rvrsDato = 0;

void main( void ){
	
	while(1){
		
		getBit();
		reverseBitsPort();
		
		while(1){
			ledsON();
		}
	}
}

void getBit(){ /* byte a capturar: 1010 1111*/
	
	BYTE i, tmp = 0;
	
	outportb(RCtr,capturePC4);
	
	for(i=0; i<8; i++){
		getchar();
		tmp = testBitPort(PC,4);
		dato |= tmp << (7-i);
		printBin(dato);
		putchar(' ');
	}
	/*outportb(PB,dato); /*return dato capturado*/
}

void reverseBitsPort(){ /*byte invertido: 1111 0101 */
	
	BYTE numBit, aux = 0, data; /**/
	/*data = inportb(port);*/
	
	for(numBit=0; numBit<8; numBit++){
		/*
		printBin(data);
		putchar(' ');
		*/
		aux = (dato>>numBit) & 0x01;	
		if(aux){
			rvrsDato |= aux << (7 - numBit);
		}else{
			rvrsDato |= aux << (7 - numBit);
		}
	}
}

void ledsON(){ /*1111 0101*/
	
	BYTE bit = 0, value = 0;
	
	while(bit<8){
		
		value = (rvrsDato)&(0x01<<bit); /*es 1 o 0 ?*/
	 	
		if(value){
			if(bit==0 || bit==1){ 
				outportb(RCtr,PA1PB2);
				if(bit==0){/*D1 ON*/
					setBitPort(PB,2);
					clrBitPort(PA,1);
				}else{/*D2 ON*/
					setBitPort(PA,1);
					clrBitPort(PB,2);
				}
			}
			else if(bit==2 || bit==3){
				outportb(RCtr,PB2PC3);
				if(bit==2){/*D3 ON*/
					setBitPort(PC,3);
					clrBitPort(PB,2);
				}else{/*D4 ON*/
					setBitPort(PB,2);
					clrBitPort(PC,3);
				}
			}
			else if(bit==4 || bit==5){
				outportb(RCtr,PC3PA1);
				if(bit==4){ /*D5 ON*/
					setBitPort(PA,1);
					clrBitPort(PC,3);
				}else{ /*D6 ON*/
					setBitPort(PC,3);
					clrBitPort(PA,1);
				}
			}
			else{
				outportb(RCtr,PC4PC3);
				if(bit==6){ /*D7 ON*/
					setBitPort(PC,4);
					clrBitPort(PC,3);
				}else{/*D8 ON*/
					setBitPort(PC,3);
					clrBitPort(PC,4);
				}
			}
		}
		bit++; value=0;  delay(75);/*  flicker*/
	}
	bit=0;
}

/* función simple para desplegar un byte en formato binario */
void printBin(BYTE dato){
	BYTE msk=0x80;
	do{
		putchar( (dato & msk) ? '1' : '0' );
		msk>>=1;
	}while( msk );
}

void setBitPort(WORD port, BYTE numBit){	
	outportb(port,inportb(port)|(0x01<<numBit));
}

void clrBitPort(WORD port, BYTE numBit){	
	outportb(port,inportb(port)&(0x00<<numBit));
}

/*
void notBitPort(WORD port, BYTE numBit){	
	outportb(port,inportb(port)~(0x01<<numBit));
}
*/

BYTE testBitPort(WORD port, BYTE numBit){	
	return inportb(port)&(0x01<<numBit) ? 1:0;
}

void delay(BYTE d){
	while(d--);
}






