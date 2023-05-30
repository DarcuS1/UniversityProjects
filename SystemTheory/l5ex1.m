close all
clear all
clc

 t = 0 : 0.01 : 30 ;
 input = sin(t) ; 

 G1 = tf ( [ 0.1 1 ] , [ 1 1] ) ; 
 G2 = tf ( [ 10 10 ] , [ 1 10] ) ; 
  G3 = tf ( [10]  , [1 1 1] ) ; 
   G4 = tf ( [ 1 1 1 ] , [ 1 1 10] ) ; 


% w = 1; 
% s = 1i*w; 
% M = abs ( ( 0.1*s + 1) /(s +1) )
% phi = angle ( (0.1*s + 1) /( s +1) ) 
  % figure
  % lsim (G1, input , t ) , grid on 
  %  figure
  % lsim (G2, input , t ) , grid on 
  %  figure
  %lsim (G3, input , t ) , grid on 
  %  figure
  % lsim (G4, input , t ) , grid on 



%figure
%bode(G1), grid on
%figure
%bode(G2), grid on
%figure
%bode(G3), grid on
%figure
%bode(G4), grid on
%G5 = tf ( [  10 10000 ] , [ 1 1 1] ) ; 
%figure 
%bode(G5), grid on

G6 = tf ( [ 1000000000 0 ] , [ 1 10000000000 10000000000] ) ; 
figure 
bode(G6), grid on



