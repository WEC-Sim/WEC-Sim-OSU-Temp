%% Non-Linear Hydraulic PTO - GMREC Conference
% Sean Casey
% 3/4/13
% GRA - OSU
%
%   Hybrid system model of hydraulic PTO
%
% Notes:

%% Initialize Workspace
clear; clc; close all
set(0,'DefaultFigureWindowStyle','docked')
funPath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\ActiveHydraulicSystem\SimulationDataFiles\';
addpath(funPath);
addpath(savePath);


saveData            = 0;
waveSrc             = 0;       % 1 == 'Regular', 0 == 'Irregular'
makeNewWaves        = 1;
doSim               = 1;

nameWave            = 'wave_irr_Hs3_Ts10_controlled_4x2';
nameDyn             = 'dynModel_ActiveSystem';
namePTO             = 'PTO_150kW_Hs3_Ts10_ActiveSystem';        % Specify PTO determined from 'PTOsizeCaller.m'

%% Simulation parameters
% Configuration parameters
init.ti = 0;                % Initial time
init.tf = 400;              % Final time
init.del_t = 0.01;          % Step size

tspan = [init.ti, init.tf];
%% Signal Data
% Time
df = 1/init.tf;

% Wave Data
% Ts = 11.1 -- Te = 10;  Ts = 8.85 -- Te = 8;  Ts = 13.33 -- Te = 12
Ts =  11.1; %8.85; 13.33;                        % Significant wave period
Hs = 3;                             % Significant wave height
init.seaState = [Hs Ts]; 

if makeNewWaves == 1
    wave = makeRepWaves(Ts, Hs, df, waveSrc);
%     wave = makeRepWaves(wave.irr.Te, Hs, df, 1);
    save([savePath nameWave], 'wave')
else
    load([savePath nameWave])
end


