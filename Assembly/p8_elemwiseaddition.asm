; Element-wise addition of two arrays of 16-bit numbers.

DATA SEGMENT
  arr1 DW 1000H, 2000H, 3000H, 4000H
  arr2 DW 4000H, 3000H, 2000H, 1000H
  sum DW 4 DUP(?)
  count DW 4
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA
START:
  MOV AX, DATA
  MOV DS, AX
  MOV CX, count
  LEA SI, arr1
  LEA DI, arr2
  LEA BX, sum

SUMLOOP:
  MOV AX, [SI]
  ADD AX, [DI]
  MOV [BX], AX
  ADD SI, 2
  ADD DI, 2
  ADD BX, 2
  LOOP SUMLOOP

EXIT:
  MOV AX, 4CH
  INT 21H
CODE ENDS
END START