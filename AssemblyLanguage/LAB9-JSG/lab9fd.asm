EXTRN SUM : FAR 

DATA SEGMENT PARA PUBLIC 'DATA'

SIR DB "567";INITIALIZE A STRING WITH LENGTH AND ADDRES,AND A 
LEN DW $-SIR ;SUM AS RESULT
ADD1 DD SIR


DATA ENDS



CODE SEGMENT PARA PUBLIC 'CODE'
ASSUME CS:CODE,DS:DATA

START PROC FAR

PUSH DS
XOR AX, AX
PUSH AX
MOV AX, DATA
MOV DS, AX

LDS BX, ADD1;GIVE THE REGISTERS THE DATA BEFORE CALL
MOV CX, LEN
MOV DX, DS
 
CALL SUM

RET

START ENDP
CODE ENDS
END START