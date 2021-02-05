.model tiny

   ;----- Insert INCLUDE "filename" directives here
   ;----- Insert EQU and = equates here
   
   locals
   
.data
      
      msgGet 	DB  'Introduce the secrete 4 digits:',10,13,0
	  msgBoard 	DB  'Bulls: ',9,'Cows: ',9,'Guesses:',10,13,0 ;tabulaciones no apareceran bien
	  msgGuess	DB 	'Guess the 4 digit sequence',10,10,13,0
	  msgWin	DB 	'You win!',10,10,13,0
	  msgLoose	DB 	'You LOOSE!',10,10,13,0
	  done		DB 	'Done.',10,13,0
	  new_line	DB 	10,13,0
	  secrete  	DB  5 dup(0)
	  guess    	DB  5 dup(0)

.code
             org 100h
	
;*************************************************************
;  Procedimiento principal
;*************************************************************	
	principal proc
            mov sp,0fffh	; inicializa SP (Stack Pointer)
			mov ax,@data  	; inicializar DS al la direccion
			;mov ds,ax    	; del segmento de datos (.DATA)
			
			mov si, offset secrete 
			mov di, offset guess 
						
			mov dx, offset msgGet
			call puts
			mov dx,si
			call getDigits
			
			mov dx, offset done
			call puts
			mov dx, offset msgGuess
			call puts
			
			mov dx, offset msgBoard
			call puts

		@@nextGuess:
			mov dx,di
			call getDigits
			call evalGuess
			call printHint
			mov dx, offset new_line
			call puts
			jmp @@nextGuess
		; Add the following conditions:
		; 	The "game" end when Bulls equals 4 (You win)
		; 	or the number of guesses is greater then 8
		
		@@sigue:
			jmp @@sigue
			
			ret						; nunca se llega aquí
			endp

			
;***************************************************************
;  procedimientos
;***************************************************************            
    putchar	proc
			push ax
			push dx
			mov dl,al
			mov ah,2				; imprimir caracter DL
			int 21h					; usando servico 2 (ah=2)
			pop dx					; del int 21h
			pop ax
			ret
			endp
	
	getch	proc
			mov ah,8				; no echo
			int 21h				
			ret
			endp
	
	getche	proc
			mov ah,1				
			int 21h				
			ret
			endp
			
	puts	proc
			push ax
			push bx
			
			mov  bx,dx
		@@nxt: 
			mov  al,[bx]
			cmp  al,0
			je   @@end
			call putchar
			inc  bx
			jmp  @@nxt
			
		@@end: 
			pop  bx
			pop  ax
			ret
			endp
	
	getDigits proc
			push ax
			push bx
			push cx
			
			mov bx,dx
			mov cx,4
		@@gnxt: 
			call getch
			cmp al,'0'
			jb @@gnxt
			cmp al,'9'
			ja @@gnxt
			mov [bx],al
			inc bx
			loop  @@gnxt
			
			pop cx
			pop bx
			pop ax
			ret
			endp
	
	printHint proc
			push ax
			push dx
			
			add al,'0'
			call putchar ; print Bulls
			
			mov al,9
			call putchar ; tab
			
			mov al, ah
			add al,'0'
			call putchar ; print Cows
			
			mov al,9
			call putchar ; tab
			
			mov dx,di
			call puts
			
			pop dx
			pop ax
			ret
			endp

;***************************************************************
;  	Procedure that evaluates the Bulls (correct number in the correct place)
;  	and Cows (correct number but incorrect position) based on the two arrays
;	given by SI (secrete) and DI (guess).
;	Returns Bulls in AL, and Cows in AH	
;***************************************************************            
	evalGuess proc
			; place code here 
			mov ah,2 	;remove this
			mov al,2	;remove this
			ret
			endp
						
end   principal              ; End of program 
