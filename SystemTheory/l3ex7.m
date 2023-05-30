close all
clear all
clc
s = tf('s');
G = 1 / (s^2 + 2*s + 1);
K = rltool(G);
step(feedback(K*G, 1));
