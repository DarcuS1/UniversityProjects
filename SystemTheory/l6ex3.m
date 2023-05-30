close all
clear all
clc

G1=tf(5,[5 15.5 11.5 6]);
sys=tf(1,1);
step(G1/sys);
roots([5 15.5 11.5 6]);

