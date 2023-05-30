
% Define the transfer function
num = 1;
den = [1, 1, 2, 1];
G = tf(num, den);

% Open the root locus design tool
rltool(G);