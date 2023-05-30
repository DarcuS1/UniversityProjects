close all
clear all
clc

% Define the symbolic variable and parameter
syms z T

s = (1-z^-1)/T;
G = 1/s^2;
Gc = 8*(s+1)/(s+4);

Gc1 = Gc;
Gc1 =simplify(Gc1)
%Gc2=((8*T+8)*z-8)/((4*T+1)*z-1);
%simplify(Gc1);
% Display the controller pulse-transfer function
disp('Controller pulse-transfer function Gc1(z):');
disp(Gc1);

T=0.01;
