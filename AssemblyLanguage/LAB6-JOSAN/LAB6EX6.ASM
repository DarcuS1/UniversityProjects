DATA SEGMENT PARA PUBLIC 'DATA'

STR1 DW 11,15   ;string cu valori initiale
STR2 DW 2 DUP(?)  ;string in care o sa se scrie
DATA ENDS

CODE SEGMENT PARA PUBLIC 'CODE'
ASSUME CS:CODE,DS:DATA


START PROC FAR
PUSH DS
MOV AX,DATA
MOV DS,AX

MOV AX,STR1[0]  ;mut pe ax si dau push
PUSH AX
MOV AX,STR1[1]
PUSH AX
                    ;luam valorile in bx
POP BX             ;le punem in string 2
MOV STR2[0],BX

POP BX
MOV STR2[1],BX


POP DS
RET

START ENDP
CODE ENDS
END START
