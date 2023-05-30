
DATA SEGMENT PARA PUBLIC 'DATA'
SIR DB 250,250,3,4

N EQU $-SIR
;we get sir length from substracting adresses

SUM DW 0
;sum goes from db to dw(byte to word)
DATA ENDS

CODE SEGMENT PARA PUBLIC 'CODE'
ASSUME CS:CODE,DS:DATA


START PROC FAR

MOV AX,DATA
MOV DS,AX

XOR AX,AX
;make the ax reg 0
MOV SI,0
;make index 0
XOR CX,CX
;make cx 0
MOV CL,N
;make cl 0
XOR BX,BX
;using the auxiliary register bx that is made 0
L1:
;a loop
ADD BL,SIR[SI]
;add sir of si in bl
ADD AX,BX
;add the whole registers
XOR BX,BX
;clean bx
INC SI
;increment si by 1
LOOP L1

MOV SUM,AX
;mov the result to sum
RET
START ENDP
CODE ENDS
END START
