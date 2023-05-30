
% Define transfer functions
G1 = tf(1, [1 1]);
G2 = tf(1, [1 -1]);
G3 = tf(1, [1 -1 0]);
G4 = tf(1, [1 0 1]);
G5 = tf(1, [1 2 17]);
G6 = tf(1, [1 -2 17]);

% Plot impulse and step response for each transfer function
figure;
subplot(2, 1, 1);
impulse(G1);
title('Impulse response of G1');
subplot(2, 1, 2);
step(G1);
title('Step response of G1');

figure;
subplot(2, 1, 1);
impulse(G2);
title('Impulse response of G2');
subplot(2, 1, 2);
step(G2);
title('Step response of G2');

figure;
subplot(2, 1, 1);
impulse(G3);
title('Impulse response of G3');
subplot(2, 1, 2);
step(G3);
title('Step response of G3');

subplot(2, 1, 1);
impulse(G4);
title('Impulse response of G4');
subplot(2, 1, 2);
step(G4);
title('Step response of G4');

figure;
subplot(2, 1, 1);
impulse(G5);
title('Impulse response of G5');
subplot(2, 1, 2);
step(G5);
title('Step response of G5');

figure;
subplot(2, 1, 1);
impulse(G6);
title('Impulse response of G6');
subplot(2, 1, 2);
step(G6);
title('Step response of G6');