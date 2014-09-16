function waveRep = makeRepWaves(Ts, Hs, df, waveSrc, ph)
% INPUT: 
%   Ts - scalar or vector of wave periods 
%   Hs - scalar or vector of significant wave heights 
%   waveSrc - 1 = regular waves
%             0 = irregular waves 
% OUTPUT: 
%   waveRep - structure of representative wave data 
% 
% Generates sea states at various periods and significant wave heights for
% use with model.

% Sean Casey
% 2/2/13
% GRA - OSU
%% 

for i = 1:length(Ts)
    for j = 1:length(Hs)
        if waveSrc == 1
            wave = makeWave2D(Hs(j), Ts(i), df, 'Regular', ph);
        elseif waveSrc == 0
            wave = makeWave2D(Hs(j), Ts(i), df, 'Irregular', ph);
        end
        
        wave.sig.eta(:, 1)       = wave.ts.t;            % Wave Displacement
        wave.sig.eta(:, 2)       = wave.ts.z;
        wave.sig.etaDot(:, 1)    = wave.ts.t;            % Wave Velocity
        wave.sig.etaDot(:, 2)    = wave.ts.w;
        wave.sig.eta2Dot(:, 1)   = wave.ts.t;            % Wave Acceleration
        wave.sig.eta2Dot(:, 2)   = wave.ts.wdot;
        wave.sig.eta3Dot(:, 1)   = wave.ts.t;            % Wave Jerk
        wave.sig.eta3Dot(:, 2)   = wave.ts.w2dot;
        
        wave.Ts = Ts(i); 
        wave.Hs = Hs(j); 
        
        waveRep(i,j) = wave;
        
        
        
        clear wave 
    end
end




