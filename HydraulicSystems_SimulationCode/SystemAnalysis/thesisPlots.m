%% Plotting and Analysis Functions for Thesis
% Sean Casey
% 5/6/13
% GRA - OSU
%
% Notes:

%% Initialize Workspace
clear; %clc; %close all
set(0,'DefaultFigureWindowStyle','docked')
funPath         = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
savePath        = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\PressureRiseRate_PassiveHydraulicSystem\SimulationDataFiles\';
analysisPath    = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\AnalysisFiles\';
addpath(funPath, savePath, analysisPath);

%% Plotting Parameters

% Specify plot colors 
col = [255   0       0; 
       83     0     156; 
       0    118     255;
       252  174     0;
       15   188     0]/256;   
   
%% Load Data 

paramName = {'bg'}; %{'alpha', 'bg', 'vC0', 'Ap'};
nameSys   = 'PassiveSystem';
nameWave  = 'wave_irr_Hs3_Te10_40min';
varNum    = '*';

for i = 1:length(paramName)
    
    fnames = dir([analysisPath, nameSys '_' nameWave '_' paramName{i} '_' varNum '.mat']); 
    
    for j = 1:length(fnames)
        
        data.(paramName{i})(j) = load([analysisPath fnames(j).name]);
        
    end
    
end
clc

%% Plot/Analyze Data

for i = 1:length(paramName)
   
    switch paramName{i}
        case 'bg'
            
            ti = 600; 
            tf = []; 
            plot_bg(data.(paramName{i}), ti, tf)
            
        case 'alpha'
            
            plot_alpha(data.paramName{i})
            
        case 'Ap'
            
            plot_Ap(data.paramName{i})
            
        case 'vC0' 
            
            plot_vC0(data.paramName{i})
            
    end
    
end



