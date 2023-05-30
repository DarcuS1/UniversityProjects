close all
clear all
clc

A = [-5 -20 0;
      8  -3  1;
      1  -2  4];
B = [1; 0; 0];
C=[1 0 0];
C2=eye(3);
D=[0;0;0];
desired_poles = [-20 - 4j, -20 + 4j, -10];
eigenvalues = eig(A);
disp('Eigenvalues:');
disp(eigenvalues);

controllability_matrix = ctrb(A, B);
rank_controllability = rank(controllability_matrix);
disp('Rank of Controllability Matrix:');
disp(rank_controllability);
init = [-20 - 4i; -20 + 4i; -10 ];

K = place(A, B, desired_poles);
N = 1/(C*inv(A-B*K)*B);

disp('Gain matrix K:');
disp(K);
