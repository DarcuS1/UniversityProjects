DATA SEGMENT PARA PUBLIC 'DATA'

SIR DW 1,2,3,4
;schimbam din DB(byte ) in DW
N EQU ($-SIR)/2
;este impartita marimea pentru difernta dintre byte si word
SUM DW 0

DATA ENDS


CODE SEGMENT PARA PUBLIC 'CODE'
ASSUME CS:CODE,DS:DATA

START PROC FAR

MOV AX,DATA
MOV DS,AX

XOR AX,AX
;facem AX 0
MOV SI,0
;facem indexul 0
MOV CX,0
;facem counter 0
MOV CL,N
;facem counter lungimea sirului 
L1: 
;un loop
ADD AX,SIR[SI]
;adaugam elementele sirului la ax
ADD SI,2
;adaugam 2 pentru diferenta de la byte la word 

LOOP L1

MOV SUM,AX
;mutam rezultatul ax in suma
;MOV AX,400CH
INT 21H

START ENDP
CODE ENDS
END START
