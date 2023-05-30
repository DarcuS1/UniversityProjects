close all 
clear all
clc
% input the transfer functions 

K = 1; W = 1; C = 0;   sys1 = tf(K, [1 2*C*W W^2]);
K = 1; W = 3; C = 0;   sys2 =  tf(K, [1 2*C*W W^2]);
K = 1; W = 1; C = 0.1; sys3 = tf(K, [1 2*C*W W^2]);
K = 1; W = 1; C = 0.6; sys4 = tf(K, [1 2*C*W W^2]);
K = 1; W = 1; C = 1;   sys5 = tf(K, [1 2*C*W W^2]);
K = 1; W = 1; C = 2;   sys6 = tf(K, [1 2*C*W W^2]);
K = 3; W = 1; C = 0.6; sys7 = tf(K, [1 2*C*W W^2]);
% simulate the step responses for 25 seconds
 step (sys1, sys2, sys3, sys4,sys5 ,sys6 ,sys7, 25), grid on
legend ('H1: K = 1; Wn = 1; Ct= 0', 'H2: K = 1; Wn = 3; Ct= 0', 'H3: K = 1; Wn = 1; Ct= 0.1', 'H4: K = 1; Wn = 1; Ct= 0.6', 'H5: K = 1; Wn = 1; Ct= 1', 'H6: K = 1; Wn = 1; Ct= 2','H7: K=1; Wn;Ct=2')