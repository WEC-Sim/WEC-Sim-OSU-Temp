%% PTO Size Caller\
% Sean Casey
% 2/8/13
% GRA - OSU

%% Initialize Workspace
clear; %clc; close all
set(0,'DefaultFigureWindowStyle','docked')
funPath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\PressureRiseRate_PassiveHydraulicSystem\SimulationDataFiles\';
addpath(funPath);
addpath(savePath); 

%% Signal Data
waveSrc = 1; % 1 == 'Regular', 0 == 'Irregular'
makeNewWaves = 1;

% Configuration parameters
simParam.ti = 0;                % Initial time
simParam.tf = 1600;              % Final time
simParam.del_t = 0.01;          % Step size

% Time
df = 1/simParam.tf;

% Wave Data
Ts = 10;                        % Significant wave period
Hs = 3;                         % Significant wave height

%% PTO Data
ptoConfig.V_nom     = 250;              % motor displacement [cm^3/rot]
ptoConfig.omega_r   = 2400;             % generator speed at steady state [rpm]
ptoConfig.eta_vm    = 0.93;             % motor volumetric efficiency
ptoConfig.eta_hm    = 0.91;             % motor hydro-mechanical efficiency
ptoConfig.eta_vp    = 0.94;             % motor volumetric efficiency
ptoConfig.eta_hp    = 0.93;             % motor hydro-mechanical efficiency
ptoConfig.eta_g     = 0.97;             % generator efficiency
ptoConfig.Pg_r      = 150;              % generator rated power [kW]

%% Size PTO
[ptoS] = PTOsize(ptoConfig, Ts, Hs, waveSrc, 'noEff');

save([savePath 'PTO_150kW_Hs3_Ts10_PassiveSystem'], 'ptoS')

%% Close out
rmpath(funPath)
rmpath(savePath)