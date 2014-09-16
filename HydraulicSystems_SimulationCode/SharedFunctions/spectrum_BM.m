function [sBM, f] = spectrum_BM(Hs, Ts, df)
% Creates a Bretschneider-Mitsyasu spectrum (Goda - eq: 2.10)
% INPUT: 
%   Hs        - significant wave height
%   Ts        - significant period
%   df        - frequency bin width
% OUTPUT: 
%   sBM       - spectral density 
%   eta_comp  - wave height at each frequency 
%   f         - frequency bins 

%% Generate Wave Spectrum Spectrum 
f   = df:df:0.4;                                    % Frequency bins 
sBM = 0.257*Hs^2/Ts^4./f.^5.*exp(-1.03./(Ts*f).^4); % Spectral Density 


m_0 = trapz(f,sBM);                                 % First spectral moment
hs_check = 4*sqrt(m_0); 
