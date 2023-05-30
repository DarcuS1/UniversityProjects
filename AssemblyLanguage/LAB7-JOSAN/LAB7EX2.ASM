DATA SEGMENT PARA PUBLIC 'DATA'

SIR DB "ana are 8354128 *^$*(^(& MeRe R005ii";stringul initial
LEN1 EQU $-SIR;lungimea sirului

DATA ENDS

CODE SEGMENT PARA PUBLIC 'CODE'

ASSUME CS:CODE, DS:DATA

MAIN PROC FAR
;PUSH DS

MOV AX,DATA
MOV DS,AX
XOR AX,AX
MOV CX, LEN1;initializam countul loopurilor cu lungimea sirului

XOR SI,SI


L1: 

CMP SIR[SI],97;comparam cu litera a mic
JGE L2;daca e mai mare trecem l2
INC SI
CMP CX,0;am ajuns la final-iesim
JE OUT_LAB

LOOP L1

L2:
MOV AL,SIR[SI];incarcam pentru comparare
MOV BL,123

CMP AL,BL ;daca e mai mic decat litera z mic face o scadere de 32 
;pentru a ajunge la o litera mare

JLE  LESS
     
JMP NEXT
            
LESS: 

SUB SIR[SI],32 ;scaderea ptn litera mare 
 
NEXT: 
 
INC SI
JMP L1

LOOP L2

OUT_LAB:;iesire
;POP DS

RET


MAIN ENDP
CODE ENDS
END MAIN

