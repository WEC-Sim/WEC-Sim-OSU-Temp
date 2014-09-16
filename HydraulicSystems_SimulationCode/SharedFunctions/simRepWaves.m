function simResults = simRepWaves(mdl, waveRep, wec, pto, simParam)
% INPUT: 
%   mdl  - string of model name to simulate 
%   wave - structure of wave data  
%   wec  - structure of buoy hydrodynamic parameters 
%   pto  - structure of pto parameters 
% OUTPUT: 
%   simResults - structure containing simulation data and results 
% 
%
% Sean Casey
% 2/2/13
% GRA - OSU

%% Start Analysis
for i = 1:size(waveRep,1)
    for j = 1:size(waveRep,2)
        
        %% Signals
        eta     = waveRep(i,j).sig.eta;
        etaDot  = waveRep(i,j).sig.etaDot;
        eta2Dot = waveRep(i,j).sig.eta2Dot;
        eta3Dot = waveRep(i,j).sig.eta3Dot;
        
        %% RUN SIMULATION
        sim(mdl);
        
        % Get logged data
        for k = 1:logsout.numElements
            name = logsout.get(k).Name;
            eval(['simData.' name ' = logsout.get(k).Values.data;']);
        end

        simResults(i,j).simData = simData;
    end
end

