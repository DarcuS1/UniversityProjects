
z0 = 1e-2;
i0 = 100;
m = 1e4;
k = 1e-3;
g = 10;

num_EMS = 2*k*(i0^2/z0^3)-2*k*(i0/z0^2);
den_EMS = [m, k*(i0^2/z0^2), 0];
G_EMS = tf(num_EMS, den_EMS);


num_EDS = -2*k*(i0^2/z0^3)+2*k*(i0/z0^2);
den_EDS = [m, k*(i0/z0^2), 0];
G_EDS = tf(num_EDS, den_EDS);


figure;
impulse(G_EMS, 0.1);
title('Impulse response for EMS');


figure;
impulse(G_EDS, 1);
title('Impulse response for EDS');