DATA SEGMENT PARA PUBLIC 'DATA'
NUMBERS DB 10 DUP(?)
DATA ENDS

CODE SEGMENT PARA PUBLIC 'CODE'

START PROC FAR

ASSUME CS:CODE, DS:DATA
PUSH DS ;prepare to return to DOS
XOR AX,AX
PUSH AX
MOV AX,DATA; initialise DS
MOV DS, AX

MOV AX, 325;random nr then div by cx
MOV CX, 10
MOV SI,0

L:
CWD
DIV CX
MOV NUMBERS[SI], DL ;put the rest of the div in numbers
ADD NUMBERS[SI], '0';add the value of 0 in ascii
INC SI
CMP AX, 0
JNE L

MOV CX, SI
MOV AH, 02H;prepare 
DEC SI

L2: 
MOV DL, NUMBERS[SI]  ;   output in reverse order beacuse si has last value
INT 21H;output
DEC SI
LOOP L2

 
RET

START ENDP
CODE ENDS
END START
