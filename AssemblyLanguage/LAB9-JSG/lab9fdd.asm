DATA SEGMENT PARA PUBLIC 'DATA'
SUMSIR DW ?
DATA ENDS


COD2 SEGMENT PARA 'CODE'
PUBLIC SUM
ASSUME CS:COD2

SUM PROC FAR
MOV AX, DATA;SUM PROCEDURE, DATA INITIALIZATION
MOV ES, AX
ASSUME ES:DATA

MOV SUMSIR, 0
MOV DS, DX
XOR AX, AX
XOR SI, SI

l1:
MOV AL, DS:BX[SI];CALCULATING THE VALUE OF EACH DIGIT OF THE STRING 
SUB AL, '0';AND ADDING THEM TO RESULT (FROM ASCII TO INT THEN ADD TO SUMSIR)
ADD SUMSIR, AX
INC SI
LOOP l1

MOV AX, SUMSIR
RETF

SUM ENDP
COD2 ENDS
END