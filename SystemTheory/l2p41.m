% Define system parameters
m = 0.5; % mass of the ball
l = 1; % length of the rod
g = 9.8; % acceleration due to gravity
b = 0.5; % viscous friction coefficient

% Define transfer function
s = tf('s');
H = 1 / (m*l^2*s^2 + b*l*s + m*g*l);

% Plot impulse response
figure;
impulse(H);
title('Impulse Response of Pendulum System');
xlabel('Time (seconds)');
ylabel('Pendulum Angle (radians)');

% Define the state-space matrices
A = [0 1; -g/l -b/(m*l^2)];
B = [0; 1/(m*l^2)];
C = [1 0];
D = 0;

% Create the state-space model
sys = ss(A, B, C, D);


% Impulse response
impulse(H);

% Step response
step(H);

% Impulse response
impulse(sys);

% Step response
step(sys);