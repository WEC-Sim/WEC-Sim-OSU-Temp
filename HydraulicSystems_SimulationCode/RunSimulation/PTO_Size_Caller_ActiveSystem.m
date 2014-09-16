%% PTO Size Caller
% Sean Casey
% 2/8/13
% GRA - OSU

%% Initialize Workspace
clear; clc; close all
set(0,'DefaultFigureWindowStyle','docked')
funPath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\HydraulicSystems_SimulationCode\RunSimulation\Main_Functions\';
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\HydraulicSystems_SimulationCode\RunSimulation\SavedSimulationData\';
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
Te = 10;                        % Significant wave period
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
[ptoS] = PTOsize(ptoConfig, Te, Hs, waveSrc, 'noEff');

save([savePath 'PTO_' num2str(ptoConfig.V_nom) 'cc_' num2str(ptoConfig.Pg_r) 'kW_Hs' num2str(Hs) '_Ts' num2str(Te)], 'ptoS')

% Close out
rmpath(funPath, savePath)