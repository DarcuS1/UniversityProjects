 close all
 clear all
 clc
 % p l o t the s t e p r e s p o n s e and the im pul s e r e s p o n s e
 % H1:
 num=4; den =[1 5 4 ] ; % i npu t the numerator and denominator
 H1 = tf (num, den ) ; % c r e a t e the t r a n s f e r f u n c ti o n H1
 disp('polesofH1:' )
 r=roots(den); % de te rmi ne the r o o t s o f the denominator
 figure
 subplot( 211 ) , step (H1) , grid on % f i n a l time o f sim ul a ti o n
 subplot( 212 ) , impulse (H1) , grid on % i s chosen a u t om a ti c all y
 %−−−−−−−−−−−−−−−−−−−−−−−−−−−−
 % H7:
 num=4; den=conv ( [ 1 0 4 ] , [ 1 0 4 ] ) ; % denominator i s ( s ˆ2+4) ˆ2
 H7 = tf (num, den); % c r e a t e the t r a n s f e r f u n c ti o n H7
 disp('polesofH7:')
 r=roots ( den ); % de te rmi ne the r o o t s o f the denominator
 figure
 subplot( 211 ) , step(H7, 30 ) , grid on % f i n a l time o f sim ul a ti o n
 subplot( 212 ) , impulse(H7, 30 ) , grid on % i s s e t by the u s e r (30 s e c )
