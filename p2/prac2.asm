dosseg
.model tiny
.code
	org 100h
	
	public _getchar
	public _putchar
	
	
	_getchar	PROC
				
				mov ah,08h ;01 eco 
				int 21h ;return char in al
			
				ret
	_getchar	ENDP
	
	_putchar	PROC 
				push bp 
				mov bp,sp
				
				mov dl,[bp+4] ;get char
				mov ah,02h  
				int 21h
				
				pop bp
				ret
	_putchar	ENDP
	
	END