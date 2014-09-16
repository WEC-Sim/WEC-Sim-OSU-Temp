function [u, w] = waveVelocity_TS(t, eta_comp, sigma, phi, k, x, h, z)
% Creates a timeseries of wave heights from components of initial wave
% heights and frequencies 
% INPUT: 
%   sigma           - vector of frequency bins 
%   eta_comp        - initial wave height components 
%   phi             - phase of each component wave 
%   k               - wave number for each frequency
%   x               - location of timeseries (wave gauge) 
%   h               - depth
%   z               - vertical point to calculate velocity 
% OUTPUT:
%   eta_t           - summation of wave height components at each time step
%   t               - timeseries vector
%   u               - horizontal velocity of water particle
%   w               - vertical velocity of water particle 


%% 


% COMPUTE ETA           
u = zeros(1, length(t)); % initialize time component wave heights array
w = zeros(1, length(t)); % initialize time component wave heights array
for i = 1:length(eta_comp) 
    u = u + eta_comp(i).*sigma(i).*cosh(k(i).*(h + z(i)))./sinh(k(i)*h).*cos(k(i)*x - sigma(i)*t - phi(i));
    w = w + eta_comp(i).*sigma(i).*sinh(k(i).*(h + z(i)))./sinh(k(i)*h).*sin(k(i)*x - sigma(i)*t - phi(i));
end 


