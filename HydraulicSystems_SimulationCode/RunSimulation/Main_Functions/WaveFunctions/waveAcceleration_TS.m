function [udot, wdot] = waveAcceleration_TS(t, zComp, sigma, phi, k, x, h, z)
% Creates a timeseries of wave heights from components of initial wave
% heights and frequencies 
% INPUT: 
%   sigma           - vector of frequency bins 
%   zComp        - initial wave height components 
%   phi             - phase of each component wave 
%   k               - wave number for each frequency
%   x               - location of timeseries (wave gauge) 
%   h               - depth
%   z               - point to calculate velocity 
% OUTPUT:
%   z_t             - summation of wave height components at each time step
%   t               - timeseries vector
%   udot            - horizontal acceleration of water particle
%   wdot            - vertical acceleration of water particle 


%% 

% COMPUTE ETA           
u2dot = zeros(1, length(t)); % initialize time component wave heights array
w2dot = zeros(1, length(t)); % initialize time component wave heights array
for i = 1:length(zComp) 
    udot = u2dot + zComp(i).*sigma(i)^2.*cosh(k(i).*(h + z(i)))./sinh(k(i)*h).*sin(k(i)*x - sigma(i)*t - phi(i)); 
    wdot = w2dot - zComp(i).*sigma(i)^2.*sinh(k(i).*(h + z(i)))./sinh(k(i)*h).*cos(k(i)*x - sigma(i)*t - phi(i));
end 


