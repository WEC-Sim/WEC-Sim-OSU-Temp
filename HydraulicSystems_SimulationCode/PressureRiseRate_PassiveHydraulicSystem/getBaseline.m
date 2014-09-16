%% Non-Linear Hydraulic PTO - GMREC Conference
% Sean Casey
% 2/10/13
% GRA - OSU
%
%   Obtain baseline uncontrolled operation and wave signals
%
% Notes:

%% Initialize Workspace
clear; clc; close all
set(0,'DefaultFigureWindowStyle','docked')
simPath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\HydPTO_ClosedCircuit\Functions\';
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\HydPTO_ClosedCircuit\SimulationDataFiles\';
addpath(simPath);
addpath(savePath);

saveData            = 1;
waveSrc             = 1;       % 1 == 'Regular', 0 == 'Irregular'
makeNewWaves        = 1;
doSim               = 1;

nameWave            = 'waveMat_BL_reg_Hs3_Ts10';
nameSimParam        = 'simParameters_BL_reg_Hs3_Ts10';
nameResults         = 'simResults_BL_reg_Hs3_Ts10';
namePTO             = 'PTO_50kW_Hs3_Ts10';        % Specify PTO determined from 'PTOsizeCaller.m'

% Load Data Set
load([savePath nameWave])           % Waves
load([savePath nameSimParam])       % simulation and model parameters
load([savePath nameResults])        % simulation results
% load([savePath namePP])             % Post processing data
load([savePath namePTO], 'ptoS')

%%

% plotSimData
tDesired = input('Specify steady state time:       ')


simData = simResults.simData;

% tDesired = 541;
[tDelta, tInd] = min(abs(waveRep.ts.t-tDesired));

tStart = waveRep.ts.t(tInd);
tFinal = simData.time(end);
dt = 0.01;
timeSim = tStart:dt:tFinal;

IC = deval(simData.simSol, tStart);                % Get initial conditions for starting hybrid system


% Simulation variables
init.time = timeSim - tStart;    % create time vector to evaluate
init.IC   = IC;
init.xBar = mean(simData.simSol.y,2);           % get steady state values of state variables
init.uBar = [simData.u;
    0];

init.tFe        = waveRep.ts.t(tInd:end) - tStart; 
init.eta        = waveRep.sig.eta(tInd:end, 2);
init.etaDot     = waveRep.sig.etaDot(tInd:end, 2);
init.eta2Dot    = waveRep.sig.eta2Dot(tInd:end, 2);
init.tInd       = tInd; 
save([savePath 'init_BL_reg_Hs3_Ts10'], 'init')


