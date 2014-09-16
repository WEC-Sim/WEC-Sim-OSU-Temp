function wave = makeWave2D(Hs, T, df, type, ph)
% Generates 2D linear stochastic wave timeseries with random phases
% generated from BM spectrum

% INPUT:
%   Hs - significant wave height
%   Ts - significant period
%   df - frequency spacing
% type - String: 'Regular' or 'Irregular'

% OUTPUT:
%   wave.t              - time vector
%   wave.z              - wave height
%   wave.zComp.z        - component wave height
%   wave.zComp.k        - component wave number
%   wave.zComp.L        - component wave length
%   wave.zComp.phase    - component phase
%   wave.spectrum.s     - spectrum amplitude
%   wave.spectrum.f     - spectrum frequency

%% Generate Wave Data
h = 1000; % [m] deepwater depth
g = 9.81;
rho = 1025;

switch type
    % IRREGULAR WAVES
    case 'Irregular'
        
        % Generate Wave Spectrum Spectrum
        [sBM, f] = spectrum_BM(Hs, T, df);
        
        zComp = (2*sBM.*df).^(1/2);          % Wave amplitude at each frequency  (Goda - Ch. 9)
        zComp(zComp < 0.001) = 0;           % set very low frequencies to zero (avoid numerical underflow)
        
        T = 1./f;                               % component periods
        sigma = 2*pi./T;                        % component radial frequency
        
        % Develop random wave profile based on spectrum - Time Series
        % PHASES
        if isempty(ph)
            a       = 0;
            b       = 2*pi;
            phi     = a + (b-a).*rand(size(f));     % Generate random phases between 0 and 2pi
        else
            phi = ph;       % use phase shift input
        end
        
        % Dispersion relationship - calculate wave number for each frequency
        h = 1000;                               % deep water
        k = zeros(1, length(f));
        L = zeros(1, length(f));
        for i = 1:length(f)
            [k(i), L(i)] = calcDR(T(i), h);
        end
        
        wave.spectrum.s     = sBM;
        wave.spectrum.f     = f;
        
        m0 = sum(f.^0.*sBM);
        mneg1 = sum(f.^-1.*sBM);
        Te = mneg1/m0;
        [mMax mInd] = max(sBM);
        Tp = 1/f(mInd);
        Tsig = Tp/1.05;
        
        Power = rho*g^2*Hs^2*Te/64/pi;
        
        wave.Te = Te;
        wave.Tp = Tp;
        wave.Tsig = Tsig;
        wave.Power = Power;
        
        % REGULAR WAVES
    case 'Regular'
        
        zComp = Hs/2;
        [k, L] = calcDR(T, h);
        phi = 0;
        sigma = 2*pi/T;
        Te = T;
        
        wave.Te = Te;
        wave.Hs = Hs;
        wave.Power = rho*g^2*Hs^2*Te/64/pi;
        
        
end

% TIME SERIES
tf      = 1/df;                         % interval of periodicity
dt      = 1/20*max(sigma);              % ensure no aliasing
t   	= 0 : dt : tf;                  % Time vector

x = 0;

[z]             = waveHeight_TS(t, zComp, sigma, phi, k, x);
[u, w]          = waveVelocity_TS(t, zComp, sigma, phi, k, x, h, zComp); % velocity at surface
[udot, wdot]    = waveAcceleration_TS(t, zComp, sigma, phi, k, x, h, zComp); % acceleration at surface
[u2dot, w2dot]  = waveJerk_TS(t, zComp, sigma, phi, k, x, h, zComp); % acceleration at surface

%% Output Data
wave.ts.t      = t;
wave.ts.z      = z;
wave.ts.u      = u;
wave.ts.w      = w;
wave.ts.udot   = udot;
wave.ts.wdot   = wdot;
wave.ts.u2dot  = u2dot;
wave.ts.w2dot  = w2dot;

wave.zComp.z            = zComp;
wave.zComp.k            = k;
wave.zComp.L            = L;
wave.zComp.T            = T;
wave.zComp.sigma        = sigma;
wave.zComp.phase        = phi;



end