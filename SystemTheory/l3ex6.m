 close all
 clear all
 clc

 sys=zpk([-1],[0 1 -6],1)
 rlocus(sys)
