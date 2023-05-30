% Define the damping factor
zeta = 0.7;

% Plot the root locus
rlocus(sys)

% Add the damping factor plot
sgrid(zeta, [])

% Calculate and plot the closed-loop poles with maximum damping factor
r = 1 - zeta^2;
theta = acos(zeta);
pole1 = -1 - r*exp(1j*theta);
pole2 = -1 - r*exp(-1j*theta);
hold on
plot(real(pole1), imag(pole1), 'rx', 'LineWidth', 2)
plot(real(pole2), imag(pole2), 'rx', 'LineWidth', 2)
hold off