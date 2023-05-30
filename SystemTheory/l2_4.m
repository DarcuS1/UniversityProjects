syms s m g l b X M

% Define system parameters
m = 0.5; % mass of ball in kg
g = 9.8; % acceleration due to gravity in m/s^2
l = 1; % length of rod in m
b = 0.5; % viscous friction coefficient

% Define transfer function
H = X/M;
eqn = m*l^2*s^2*X + b*s*X + m*g*l*X == M;
H = simplify(H*solve(eqn, X))

% Simplify transfer function
H = simplify(H)