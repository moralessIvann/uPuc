dosseg
.model tiny
.code
	org 100h
				  
	public _peek  ;unsigned char peek(unsigned int seg, unsigned int offset)  read
	public _poke  ;void poke(unsigned int seg, unsigned int offset, unsigned char data) write
	public _putchar
	public _getchar
	
	
		_peek	PROC
				push bp
				push ds
				
				mov bp,sp
				
				mov ds,[bp+6] ;seg
				;mov ds,dx
				mov bx,[bp+8] ;offset
				mov al,byte ptr[bx] ;pasar byte almacenado en ds*10h+offset
				
				pop ds
				pop bp
				ret
				ENDP
				
		_poke	PROC
				push bp
				push ds
				
				mov bp,sp
				
				mov ds,[bp+6]  ;seg
				;mov ds,dx
				mov bx,[bp+8]  ;offset
				mov ax,[bp+10]  ;data
				mov byte ptr[bx],al
				
				pop ds
				pop bp
				ret
				ENDP
	
	_putchar    PROC 
				push bp
				mov bp,sp
				mov dl,[bp+4]
				mov ah,02 
				int 21h		
				pop bp
				ret
	_putchar 	ENDP
				
	_getchar	PROC 		
				push bp
				mov bp,sp
				mov ah,08 ;08 sin eco
				int 21h
				pop bp
				ret
	_getchar    ENDP
	
END