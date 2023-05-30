close all 
clear all
clc
A = [0.5 -2; -0.5 -0.3]; 
B = [1;0];
C = eye (2) ; % the outputs are both states! 
D = [0;0];
x0 = [1 2]; % initial conditions
 % is this system unstable? 
valori_proprii_A = eig (A)
disp('controllability matrix: ')
Pc = ctrb (A,B) % compute the controllability matrix
 disp('the rank of Pc: ')
 rang_Pc= rank (ctrb (A,B)) % determine the rank of Pe
 disp('state feedback gain: ')
K= place (A, B, [-1 -2]) % compute K
% run Simulink model exl-simulink.slx