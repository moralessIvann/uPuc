.INCLUDE "m2560def.inc"
.equ VALUE = 0
.equ RX = $5500;1234
.equ RY = $AA00;9876
.equ RZ = $8000;3456



start:
		ldi r24,VALUE  ;load initial values
		ldi r31,high(RZ)
		ldi r30,low(RZ)
		ldi r29,high(RY)
		ldi r28,low(RY)
		ldi r27,high(RX)
		ldi r26,low(RX)

		rcall invierte_pos
		rjmp start



invierte_pos :
									push r16

									cpi r24,0
									breq r29_r26
									cpi r24,1
									brne fin

									ldi r16,8
do:									rol r31
									ror r28
									dec r16
									brne do
									rol r31

									ldi r16,8
do2:								rol r30
									ror r29
									dec r16
									brne do2
									rol r30
									rjmp fin

r29_r26: 							ldi r16,8
do3:								rol r29
									ror r26
									dec r16
									brne do3
									rol r29

									ldi r16,8
do4:								rol r28
									ror r27
									dec r16
									brne do4
									rol r28

fin:								pop r16
									ret
