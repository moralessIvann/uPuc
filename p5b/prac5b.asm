dosseg
.model tiny
.code
	org 100h
				  
	public _inportb  
	public _outportb 
	public _putchar
	public _getchar
	
_inportb PROC
		 push bp
		 
		 mov bp,sp
		 mov dx,[bp+4]
		 in al,dx
		 
		 pop bp
		 ret
_inportb ENDP
	
_outportb PROC
		  push bp
		 
		  mov bp,sp
		  mov dx,[bp+4]
		  mov al,[bp+6]
		  out dx,al
		
		  pop bp
		  ret
_outportb ENDP

_putchar PROC
		 push bp
		 
		 mov bp,sp
		 mov dl,[bp+4]
		 mov ah,02h
		 int 21h
		 
		 pop bp
		 ret
_putchar ENDP

_getchar PROC 		
		 push bp
		 mov bp,sp
		 mov ah,08 ;08 sin eco
		 int 21h
		 pop bp
		 ret
_getchar ENDP

END