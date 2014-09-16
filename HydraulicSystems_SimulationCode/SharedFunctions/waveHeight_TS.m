function [eta] = waveHeight_TS(t, eta_comp, sigma, phi, k, x)
% Creates a timeseries of wave heights from components of initial wave
% heights and frequencies 
% INPUT: 
%   sigma           - vector of frequency bins 
%   eta_comp        - initial wave height components 
%   phi             - phase of each component wave 
%   k               - wave number for each frequency
%   x               - location of timeseries (wave gauge) 
% OUTPUT:
%   eta_t           - summation of wave height components at each time step
%   t               - timeseries vector


%% 

% COMPUTE ETA 
eta = zeros(1, length(t));            % initialize time component wave heights array
for i = 1:length(eta_comp) 
    eta = eta + eta_comp(i).*cos(k(i)*x - sigma(i).*t - phi(i));     % computes components of time-series wave height of fourier series
end 


