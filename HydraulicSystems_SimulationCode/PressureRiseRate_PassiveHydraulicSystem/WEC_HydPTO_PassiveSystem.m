%% Non-Linear Hydraulic PTO - GMREC Conference
% Sean Casey
% 2/10/13
% GRA - OSU
%
%   ODE calls are programmatic - NO simulink
%
% Notes:

%% Initialize Workspace
clear; %clc; %close all
set(0,'DefaultFigureWindowStyle','docked')
funPath         = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
savePath        = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\PressureRiseRate_PassiveHydraulicSystem\SimulationDataFiles\';
analysisPath    = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\AnalysisFiles\';
addpath(funPath, savePath, analysisPath);

saveData            = 1;       % 1 == 'save data',                          0 == 'do not save data'
waveSrc             = 0;       % 1 == 'Regular',                            0 == 'Irregular'
makeNewWaves        = 1;       % 1 == 'Create and save new wave profile',   0 == 'Use existing wave profile under 'nameWave'
quickPlots          = 1;       % 1 == 'Show results',                       0 == 'Do not show results' 
usePhaseShift       = 0;

nameWave            = 'wave_irr_Hs3_Te10_40minTEST'; % 'wave_reg_Hs3_Te10_10min';
nameDyn             = 'dynModel_PassiveSystem';
namePTO             = 'PTO_150kW_Hs3_Ts10_PassiveSystem';        % Specify PTO determined from 'PTOsizeCaller.m'

%% Simulation parameters
init.ti = 0;                % Initial time
init.tf = 600;              % Final time
init.del_t = 0.01;          % Step size

tspan = [init.ti, init.tf];
%% Signal Data
% Time
df = 1/init.tf;

% Wave Data
% Ts = 11.1 -- Te = 10;  Ts = 8.85 -- Te = 8;  Ts = 13.33 -- Te = 12
init.seaState = 'ss2';
switch init.seaState
    case 'ss1'
        Ts = 8.85;                  % Significant wave period
        Te = 8;
        Hs = 4;                     % Significant wave height
        
    case 'ss2'
        Ts = 11.1;
        Te = 10;
        Hs = 3;
        
    case 'ss3'
        Ts = 13.33;
        Te = 12;
        Hs = 3;
        
end

if waveSrc == 1
    T = Te;
elseif waveSrc == 0
    T = Ts;
end

if usePhaseShift == 1
    load([analysisPath 'phase'])
else 
    ph =[];
end

if makeNewWaves == 1
    wave = makeRepWaves(T, Hs, df, waveSrc, ph);
    save([analysisPath nameWave], 'wave')
else
    load([analysisPath nameWave])
end


%% Load Physical Parameters
% 
% alpha   = (1.1:0.1:1.3);
% bg      = (0.5:1:3.5);
% vC0     = (3:10);
Ap      = (0.7:0.1:1.3);
% 
% paramName = {'alpha', 'bg', 'vC0', 'Ap'};
% param = {alpha, bg, vC0, Ap} ;

% Ap          = 1;
paramName   = {'Ap'};
param       = {Ap};

for i = 1:length(param)
    
    nParam = length(param{i});
    
    for j = 1:nParam;
        % Set up parameters to vary
        [con, wec, pto] = loadSimParameters_PassiveSystem(savePath, namePTO, Te);
        
        switch paramName{i}
            case 'alpha'
                pto.alpha = alpha(j);
            case 'bg'
                pto.bg = bg(j);
                pto.bf = 0.05*pto.bg;
            case 'vC0'
                pto.vC0   = vC0(j);
                pto.vCeq  = pto.vC0*(1-(pto.pC0/pto.pCeq)^(1/1.4));    % Min volume of oil in accumulator
                pto.pC2   = 1.5*pto.pC1;
                pto.vC2   = pto.vC0*(1-(pto.pC0/pto.pC2)^(1/1.4));     % Max volume of oil in accumulator
                pto.vC1   = pto.vC0*(1-(pto.pC0/pto.pC1)^(1/1.4));     % Min volume of oil in accumulator
                pto.pAeq  = pto.pCeq;
                pto.pBeq  = pto.pCeq;
            case 'Ap'
                pto.Ap = Ap(j)*pto.Ap;
            otherwise
        end
        
        dynModel = getDynModelPassive(pto, wec, con);           % load dynamic model with chosen parameters
        
        %% Initial Conditions
        wec.zDot_i  = 0;
        
        wec.z_i     = 0;
        
        pto.pAi    = pto.pAeq;                                    % Initial accumulator pressure
        
        pto.pBi    = pto.pBeq;                                    % Initial accumulator pressure
        
        pto.pCi    = pto.pCeq;                                    % Initial accumulator pressure
        pto.vCi    = pto.vC0*(1-(pto.pC0/pto.pCi)^(1/1.4));     % Initial accumulator volume
        
        pto.pDi    = pto.pDeq;                                    % Initial accumulator pressure
        pto.vDi    = pto.vD0*(1-(pto.pD0/pto.pDi)^(1/1.4));     % Initial accumulator volume
        
        pto.omega_i =  0;                         % Initial speed - drivetrain
        
        pto.alpha_i = pto.alpha;
        
        xi  =  [pto.pAi;            % z1
                pto.pBi;            % z2
                pto.vCi;
                pto.vDi;
                0;
                0;                  % del_p
                0];                 %1*pto.omega_r]; % omega
        
        init.xi = xi;
        
        %% Forcing Signal
        mask                    = linspace(0,1,150);
        mask                    = mask';
        remainingLength         = length(wave.sig.eta(:,2)) - length(mask);
        mask                    = [mask;  ones(remainingLength,1)];
        wave.sig.eta(:,2)       = wave.sig.eta(:,2).*mask;
        wave.sig.etaDot(:,2)    = wave.sig.etaDot(:,2).*mask;
        wave.sig.eta2Dot(:,2)   = wave.sig.eta2Dot(:,2).*mask;
        wave.sig.Fe             = (wec.A*wave.sig.eta2Dot(:,2) + wec.B*wave.sig.etaDot(:,2) + wec.K*wave.sig.eta(:,2));
        wave.sig.FeDot          = (wec.A*wave.sig.eta3Dot(:,2) + wec.B*wave.sig.eta2Dot(:,2) + wec.K*wave.sig.etaDot(:,2));
        wave.sig.tFe            = wave.sig.eta(:,1);
        wave.zDotOpt            = wave.sig.Fe/2/wec.B.*mask;
        wave.z2DotOpt           = wave.sig.FeDot/2/wec.B.*mask;
        wave.zDotOptFun         = @(t) interp1(wave.sig.tFe, wave.zDotOpt, t, 'cubic', 'extrap');
        wave.z2DotOptFun        = @(t) interp1(wave.sig.tFe, wave.z2DotOpt, t, 'cubic', 'extrap');
        
        %% Simulation
        simData = hydPTO_PassiveSystem(tspan, dynModel, init, pto, wec, wave);
        
        fprintf(['\nSimulation completed - Passive System -- ' paramName{i} ' %3.0f of %3.0f \n'], j, nParam)
        
        %% Quick plots
        if quickPlots == 1
            close all
            close all hidden
            
            val = 600;
            [t_delta, t_ind] = min(abs(simData.time-val));
            
            tspanCalc = [simData.time(t_ind) simData.time(end)];
            simData = getStats(simData, tspanCalc, pto, wec,wave, con);
            getPlots(simData, wave, pto);
            
        end 
        
        %% Save Data
        if saveData == 1
            
            out.simData   = simData;
            out.pto       = pto;
            out.wec       = wec;
            out.init      = init;
            out.wave      = wave;
            out.nameWave  = nameWave;
            out.nameDyn   = nameDyn;
            out.con       = con; 
         
            save([analysisPath 'PassiveSystem_REDO_' nameWave '_' paramName{i} '_' num2str(j)], 'out')
%             pause
        end
    end
end

% Close out
rmpath(funPath)
rmpath(savePath)