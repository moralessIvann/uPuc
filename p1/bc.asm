;Morales Rosales Ivan
;1231098

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
	  secrete  	DB  4 dup(0)
	  guess    	DB  4 dup(0)

.code
             org 100h
	
;*************************************************************
;  Procedimiento principal
;*************************************************************	
	principal proc
	
		@@again:
            mov sp,0fffh	; inicializa SP (Stack Pointer)
			;mov ax,@data  	; inicializar DS al la direccion
			;mov ds,ax    	; del segmento de datos (.DATA)
			
			mov si, offset secrete 
			mov di, offset guess 
			mov dx, offset msgGet
			call puts
			mov dx,si  ;copy array address for secret num 
			call getDigits
			mov dx, offset done
			call puts
			mov dx, offset msgGuess
			call puts
			mov dx, offset msgBoard
			call puts
			
			mov ax,00h ;counter for guesses
		@@nextGuess:
			push ax	;save counter value
			mov dx,di ;copy array address for guess num
			call getDigits 
			call evalGuess ;return bulls and cows
			call printHint
			mov dx, offset new_line
			call puts
			cmp al,04h ;cmp, if 4 bulls win
			je @@win
			pop ax	;return counter value
			inc al	;inc counter value
			cmp al,08h ;cmp counter value
			je @@loose
			jmp @@nextGuess
		@@win:
			lea dx,msgWin
			call puts
			jmp @@again
		@@loose:
			pop ax	;return counter value
			lea dx,msgLoose
			call puts
			jmp @@again
		
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
	
	getche	proc					; yes eco
			mov ah,1				
			int 21h				
			ret
			endp
			
	puts	proc
			push ax
			push bx
			
			mov  bx,dx
		@@nxt: 
			mov  al,[bx]  ;cmp if digit is zero
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
			
			mov bx,dx ;copy address where secrete digits will be stored
			mov cx,4
		@@gnxt: 
			call getch
			cmp al,'0'
			jb @@gnxt
			cmp al,'9'
			ja @@gnxt
			mov [bx],al ;store each secrete digit in di:[bx] 
			inc bx 		;nxt position to store digit
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
			call puts ; print guessed num
			
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
			
			xor cx,cx
			xor ax,ax
			xor bx,bx
			xor dx,dx
			
		@@cmpDigits:
			cmp dl,04
			je @@end
			mov bl,byte ptr[si] ;get secret digit		
			mov bh,byte ptr[di] ;get guess digit		
			cmp bl,bh ;cmp digits						
			je @@cmpFlags																	
			jne @@chkDigits								
		@@cmpFlags:
			cmp dl,04																
			je @@end															
			cmp dh,dl ;cmp flags													
			je @@cntBulls																		
			jne @@cntCows																														
		@@cntBulls:
			inc al	;bulls counter																
			mov cl,dh ;save secret flag															
			sub si,cx ;back to 1st digit to cmp again											
			xor cx,cx
			mov dh,0 ;rst secret flag if match													
			inc di ;move to nxt guess digit to cmp												
			inc dl ;inc guess flag																
			cmp dl,04																			
			je @@end																			
			jmp @@cmpDigits																		
		@@cntCows:
			inc ah ;inc cows counter							   				
			mov cl,dh ;save secret flag											
			sub si,cx ;back to 1st digit to cmp again							
			mov dh,0 ;rst secret flag if match									
			xor cx,cx					
			inc di ;move to nxt guess digit to cmp								
			cmp di,04
			je @@rstGuessFlag																											
			inc dl ;inc guess flag																									
		@@back:																																
			cmp dl,04 ;cmp flag																
			je @@end
			jmp @@cmpDigits																													
		@@rstGuessFlag:
			dec di ;back 1 position																														
			inc si ;nxt digit																														
			inc dh ;inc flag																														
			jmp @@back
		@@chkDigits:
			cmp dl,04 ;cmp flag		
			je @@end									
			inc si ;nxt digit to cmp					
			inc dh ;inc secret flag						
			cmp dh,04 ;cmp flag																															
			je @@rstSecretFlag																																	
			jmp @@cmpDigits																
		@@rstSecretFlag:
			mov cl,dh ;save secret flag																											
			sub si,cx ;back to 1st digit to cmp again																											
			mov dh,0 ;clr flag																											
			inc di ;nxt digit to cmp																												
			inc dl ;inc flag																												
			cmp dl,04 ;cmp flag																														
			je @@end																											
			jmp @@cmpDigits
		@@end:
			sub di,04h ;back to 1st digit
			mov dx,offset di ;get guess address
			ret
			endp
			
	clrRegs proc
			xor ax,ax
			xor bx,bx
			xor cx,cx
			xor dx,dx
			xor di,di
			xor si,si
			ret
			endp
			
end   principal              ; End of program 





