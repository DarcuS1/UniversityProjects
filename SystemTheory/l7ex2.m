close all 
clear all
clc
A = [1 -4 4; 1 0 0; 0 1 0]; 
B = [1; 0; 0];
C = [0 1 -1] ; 
D = [0];
x0 = [1 2]; 
valori_proprii_A = eig (A)
disp('controllability matrix: ')
Pc = ctrb (A,B)
 disp('the rank of Pc: ')
 rang_Pc= rank (ctrb (A,B))
 disp('state feedback gain: ')
K= place (A, B, [-1 -2])