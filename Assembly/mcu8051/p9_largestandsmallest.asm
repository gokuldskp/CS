; Find the largest and smallest of 8-bit numbers

ORG 0000H

MOV DPTR, #100H
MOV R0, #08H
MOV R1, #7FH
MOV R2, #00H

LOOP:
	MOVX A, @DPTR
	SUBB A, R2
	JNC LARGE
CHECKSMALL:
	MOVX A, @DPTR
	SUBB A, R1
	JC SMALL
	JNC INCREMENT
	
LARGE:
	MOVX A, @DPTR
	MOV R2, A
	JMP CHECKSMALL

SMALL:
	MOVX A, @DPTR
	MOV R1, A

INCREMENT:
	INC DPTR
	DJNZ R0, LOOP
	
END