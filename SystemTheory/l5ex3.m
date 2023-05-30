close all
clear all
clc

fileID = fopen('ECGdata.txt', 'r');
A=fscanf(fileID, '%f %f', [2,Inf]);
fclose (fileID)
time = A(1,:);
necg = A(2,:);

%figure, plot(time, necg), grid on
%xlabel ('t(sec)'), ylabel ('ECG normalized')

% Butterworth filter

[num,den] = butter (4, [0.5*2*pi 50*2*pi], 'bandpass', 's');
butter_filter = tf (num,den);

%bode plot for the filter

figure, bode(butter_filter), grid on
hold on



num = [1/pi 0];
den = conv([1/pi 1] , [1/(100*pi) 1]);
sys2= tf(num,den);
sys2=sys2*sys2*sys2*sys2;
bode(sys2), grid on;


figure, lsim(sys2, necg, time), grid on 
hold on
 lsim(butter_filter, necg,time), grid on