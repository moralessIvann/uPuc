.global delay

;delay_1ms
	delay:
    ldi  r18,21
	ldi  r19,198

nxt:dec  r19
    brne nxt
    dec  r18
    brne nxt
    nop
	nop	 
	nop
    ret ;-10
.end
