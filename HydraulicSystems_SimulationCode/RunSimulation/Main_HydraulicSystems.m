%% Main Simulation Code
% Sean Casey
% 6/12/13
% GRA - OSU
%
%   Runs either the Active (Variable Pressure) or Passive (Constant
%   Pressure) hydraulic systems connected to a 1-DOF heaving body point
%   absorber. Regular and irregular waves can be simulated.
%
% Notes:
%   - Systems are tuned to Hs = 3m / Te = 10s waves 
%   - See ReadMe.txt for more information
%
%% Initialize Workspace
clear; clc; close all
set(0,'DefaultFigureWindowStyle','docked')
funPath         = 'C:\Users\Sean\Desktop\WaveEnergyResearch\HydraulicSystems_SimulationCode\RunSimulation\Main_Functions\';
savePath        = 'C:\Users\Sean\Desktop\WaveEnergyResearch\HydraulicSystems_SimulationCode\RunSimulation\SavedSimulationData\';
addpath(genpath(funPath), savePath);

%% Simulation parameters 
% User can edit this cell 
init.ti     = 0;                % Initial time
init.tf     = 200;              % Final time
init.del_t  = 0.01;             % Step size

Te = 10;                    % Energy period (for a bretshneider spectrum multiply Te by 1.11 to get Significant Period)
Ts = 11.1;                  % Significant period 
Hs = 3;                     % Significan wave height

saveData            = 1;       % 1 == 'save data',                          0 == 'do not save data'
waveType            = 0;       % 1 == 'Regular',                            0 == 'Irregular'
makeNewWaves        = 1;       % 1 == 'Create and save new wave profile',   0 == 'Use existing wave profile under 'nameWave'
quickPlots          = 1;       % 1 == 'Show results',                       0 == 'Do not show results'
systemType          = 1;       % 1 == 'Passive',                            0 == 'Active'
usePhase            = 0;       % 1 == 'Use predefined phase difference',    0 == 'Generate random phase difference'

namePTO             = 'PTO_250cc_150kW_Hs3_Ts10';        % Specify PTO determined from 'PTOsizeCaller.m'

%% Convert Options into strings 
% may want to elimnate this altogether
if waveType 
    nameWaveType = 'Regular';
else
    nameWaveType = 'Irregular';
end

if systemType 
    nameSystemType = 'Passive';
else
    nameSystemType = 'Active';
end

%% Signal Data
% Time
tspan = [init.ti, init.tf];  % Time span of simulation
df = 1/init.tf;              % Frequency bin spacing -- assures the random wave does not repeat (i.e. longest period wave is tf)

% Create time series wave profile
nameWave = ['wave_' nameWaveType '_Hs' num2str(Hs) '_Te' num2str(Te) '_t' num2str(init.tf)];  % create save string for wave -- Hs, Te, and init.tf must be whole numbers or else change your naming convention
if waveType
    T = Te;
else
    T = Ts; 
end

if usePhase 
    phaseDiff = load('phaseDiff');   % Use a predefined phase difference saved under 'phaseDiff.mat' 
else
    phaseDiff = []; 
end

if makeNewWaves == 1
    wave = makeRepWaves(T, Hs, df, waveType, phaseDiff);
    save([savePath nameWave], 'wave')
else
    load([savePath nameWave])
end

%% Prepare Simulation
% Load physical parameters - user can edit this function containing system parameters
[con, wec, pto] = loadSimulationParameters(savePath, namePTO, nameSystemType, T);

% Create wave and forcing signals 
wave = makeWaveSignal(wave, wec); 

% Load dynamic model
switch nameSystemType
    case 'Active'
        dynModel = getDynModelActive(pto, wec, con);    
        
        % Initial Conditions for Active System
        xi =   [0;        % z1
            0;            % z2
            0;            % del_p
            0];           % omega
        
        xBar = [0;
            0;
            0;
            pto.omega_r];
        
        uBar = [0;
            pto.bg];
        
        init.xi     = xi;
        init.xBar   = xBar;
        init.uBar   = uBar;
        
        % Weighting matrices for LQT controller for active system . 
        % Tuned to passive system in 3m, 10s regular waves - similar power inputs/outputs
        init.R = [0.452  0    ;
            0      3030];
        init.Q = [0   0       0      0   ;
            0   0.8     0      0   ;
            0   0       0      0   ;
            0   0       0      1.5];
        
    case 'Passive'
        dynModel = getDynModelPassive(pto, wec, con);   
        
        % Initial Conditions for Passive SYstem
        wec.zDot_i  = 0;
        wec.z_i     = 0;
        pto.pAi     = pto.pAeq;                                  % Initial accumulator pressure
        pto.pBi     = pto.pBeq;                                  % Initial accumulator pressure
        pto.pCi     = pto.pCeq;                                  % Initial accumulator pressure
        pto.vCi     = pto.vC0*(1-(pto.pC0/pto.pCi)^(1/1.4));     % Initial accumulator volume
        pto.pDi     = pto.pDeq;                                  % Initial accumulator pressure
        pto.vDi     = pto.vD0*(1-(pto.pD0/pto.pDi)^(1/1.4));     % Initial accumulator volume
        pto.omega_i =  0;                                        % Initial speed - drivetrain
        pto.alpha_i = pto.alpha;
        
        init.xi  =  [pto.pAi;        
            pto.pBi;            
            pto.vCi;
            pto.vDi;
            0;
            0;                  % del_p
            0];                 %1*pto.omega_r]; % omega
        
end

%% Simulation
switch nameSystemType
    case 'Active'
        simData = hydPTO_ActiveSystem(tspan, dynModel, init, pto, wec, wave);   
    case 'Passive'
        simData = hydPTO_PassiveSystem(tspan, dynModel, init, pto, wec, wave);  
end
fprintf('\nSimulations completed\n')

%% Quick plots
if quickPlots == 1
    close all
    close all hidden
    
    val = 600;
    [t_delta, t_ind] = min(abs(simData.time-val));
    
    tspan = [simData.time(t_ind) simData.time(end)];
    simData = getStats(simData, tspan, pto, wec, wave, con);
    
    switch nameSystemType
        case 'Active'
           getPlots_Active(simData, wave, pto);
        case 'Passive'
           getPlots_Passive(simData, wave, pto);
    end
    
end

%% Save Data
if saveData == 1
    
    out.simData   = simData;
    out.pto       = pto;
    out.wec       = wec;
    out.init      = init;
    out.wave      = wave;
    out.nameWave  = nameWave;
    out.con       = con;
    
    save([savePath nameSystemType '_' nameWave], 'out')
    
end

%% Close out
rmpath(funPath, savePath)