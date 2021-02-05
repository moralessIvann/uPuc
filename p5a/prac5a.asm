dosseg
.model tiny
.code
	org 100h
				  
	;public _peek  ;unsigned char peek(unsigned int seg, unsigned int offset)  read
	public _poke  ;void poke(unsigned int seg, unsigned int offset, unsigned int data) write
	public _pokeW
	public _putchar
	
	_poke PROC
		  push bp
		  mov bp,sp
		 
		  mov bx,[bp+6] ;tomar offset
		  push ds
		  mov ds,[bp+4] ;tomar seg
		  mov al,[bp+8] ; tomar dato word
		  mov [bx],al	;escribir a puerto
		  
		  pop ds
		  pop bp
		  ret
	_poke ENDP
	
   _pokeW PROC
		  push bp
		  mov bp,sp
		 
		  mov bx,[bp+6] ;tomar offset
		  push ds
		  mov ds,[bp+4] ;tomar seg
		  mov ax,[bp+8] ; tomar dato word
		  mov [bx],ax	;escribir a puerto
		  
		  pop ds
		  pop bp
		  ret
   _pokeW ENDP
	
_putchar PROC
		 push bp
		 mov bp,sp
		 mov dl,[bp+4]
		 
		 mov ah,02h
		 int 21h
		 
		 pop bp
		 ret
_putchar ENDP

END