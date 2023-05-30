DATA SEGMENT PARA PUBLIC 'DATA'

TREI_F DD 3.0
REZ DQ ?

DATA ENDS


stk segment para STACK 'STACK'
 db 32 DUP ('stack_1')
stk ends


COD SEGMENT PARA 'CODE'
MAIN PROC FAR 
 ASSUME CS:COD, DS:DATA
	PUSH DS 
	XOR AX,AX 
	PUSH AX 
	MOV AX,DATA 
	MOV DS,AX 
	
    FINIT ; pornire coprocessor 
	FLD1 ; punem 1 pe stack
	FDIV TREI_F ; impartim pe 1 la 3.0
	F2XM1 ; 2^(1/3)-1.0
	FLD1 ; incarcam 1 iarasi sa facem adunare
	FADD ; 2^(1/3)-1.0+1.0
	FSTP REZ; mutam rezultatul
	
	FWAIT ;
	
 RET ;gives the control to dos
MAIN ENDP
COD ENDS
END MAIN

