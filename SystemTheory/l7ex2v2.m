close all
clear all
clc

A=[1 -4 4; 1 0 0; 0 1 0];
poles = eig(A)
% system is unstable internally cause of pole p1=1
B=[1; 0; 0];
C= eye ( 3 );
D=[0;0;0];
initial_cond = [-2; -5; -10];

syms s;

invMatrix = inv (s*eye(3) - A)
H= C*invMatrix*B;
H=simplify(H)

K=place(A,B,[-2 -5 -10])