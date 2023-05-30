 close all
 clear all
 clc


num = [1 2];
den = [1 0 0];
sys = tf(num, den);

rlocus(sys)