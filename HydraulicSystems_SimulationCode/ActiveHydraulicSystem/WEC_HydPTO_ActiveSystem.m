%% Variable Pressure Hydraulic PTO - 1-DOF Heaving Body Point Absorber
% Sean Casey
% 6/12/13
% GRA - OSU
%
%   Variable pressure hydraulic PTO connected to a 1-DOF heaving body point
%   absorber. Regular and irregular waves can be simulated. Uncontrolled
%   and Linear Quadratic Control can be applied. 
%
% Notes:

%% Initialize Workspace
clear; %clc; %close all
set(0,'DefaultFigureWindowStyle','docked')
funPath         = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
savePath        = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\ActiveHydraulicSystem\SimulationDataFiles\';
analysisPath    = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\AnalysisFiles\';
addpath(funPath, savePath, analysisPath);

saveData            = 1;       % 1 == 'save data',                          0 == 'do not save data'
waveSrc             = 0;       % 1 == 'Regular',                            0 == 'Irregular'
makeNewWaves        = 0;       % 1 == 'Create and save new wave profile',   0 == 'Use existing wave profile under 'nameWave'
quickPlots          = 1;       % 1 == 'Show results',                       0 == 'Do not show results'
usePhaseShift       = 1;

nameWave            = 'wave_irr_Hs4_Te10_40min'; %'wave_reg_Hs3_Te10_10min'; 
nameDyn             = 'dynModel_ActiveSystem';
namePTO             = 'PTO_150kW_Hs3_Ts10_ActiveSystem';        % Specify PTO determined from 'PTOsizeCaller.m'

%% Simulation parameters
init.ti = 0;                % Initial time
init.tf = 2400;              % Final time
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
        Hs = 2;                     % Significant wave height
        
        init.R = [0.452  0    ;
            0     3030];
        init.Q = [0   0       0      0   ;
            0   0.8     0      0   ;
            0   0       0      0   ;
            0   0       0      1.5];  % Vc = 7.5 Vd = 3
    case 'ss2'
        Ts = 11.1;
        Te = 10;
        Hs = 3;
        
%         init.R = [1.0 0    ;
%             0     1870];
%         init.Q = [0   0       0      0   ;
%             0   4     0      0   ;
%             0   0       0      0   ;
%             0   0       0      1];
        init.R = [0.452  0    ;
            0     3030];
        init.Q = [0   0       0      0   ;
            0   0.8     0      0   ;
            0   0       0      0   ;
            0   0       0      1.5];  % Vc = 7.5 Vd = 3
%         init.R = [0.444  0    ;
%             0     2935];
%         init.Q = [0   0       0      0   ;
%             0   0.8     0      0   ;
%             0   0       0      0   ;
%             0   0       0      1.5];  % Vc = 5 Vd = 2
        %         init.R = [1.0 0    ;
        %             0     1870];
        %         init.Q = [0   0       0      0   ;
        %             0   4     0      0   ;
        %             0   0       0      0   ;
        %             0   0       0      1];
        %
    case 'ss3'
        Ts = 13.33;
        Te = 12;
        Hs = 4;
        init.R = [0.452  0    ;
            0     3030];
        init.Q = [0   0       0      0   ;
            0   0.8     0      0   ;
            0   0       0      0   ;
            0   0       0      1.5];  % Vc = 7.5 Vd = 3
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

% figure
% plot(wave.sig.eta(:,1), wave.sig.eta(:,2))

%% Load Physical Parameters
% bg      = (1:8);
% Ap      = (0.5:0.5:4);
%
% paramName =  {'bg', 'Ap};
% param = {alpha, bg, vC0, Ap} ;

Ap          = 1;
paramName   = {'Ap'};
param       = {Ap};

% R_alpha     = 0.4:0.05:0.6;
% R_torque    = 2600:200:3400;
% paramName   = {'Ap', 'R_torque', 'R_alpha'};
% param       = {Ap, R_torque, R_alpha};
% bg = linspace(0.5,3.5, 7);
% paramName =  {'bg'};
% param = {bg} ;
for i = 1:length(param)
    
    nParam = length(param{i});
    
    for j = 1:nParam;
        % Set up parameters to vary
        [con, wec, pto] = loadSimParameters_ActiveSystem(savePath, namePTO, T);
        
        switch paramName{i}
            case 'bg'
                pto.bg = bg(j);
                pto.bf = 0.05*pto.bg;
            case 'Ap'
                pto.Ap = Ap(j)*pto.Ap;
                
            case 'R_torque'
                init.R = [0.452  0    ;
                          0      param{i}(j)];
                init.Q = [0   0       0      0   ;
                          0   0.8     0      0   ;
                          0   0       0      0   ;
                          0   0       0      1.5];  % Vc = 7.5 Vd = 3
            case 'R_alpha'
                init.R = [param{i}(j)  0    ;
                          0      3030];
                init.Q = [0   0       0      0   ;
                          0   0.8     0      0   ;
                          0   0       0      0   ;
                          0   0       0      1.5];  % Vc = 7.5 Vd = 3
        end
        
        dynModel = getDynModelActive(pto, wec, con);           % load dynamic model with chosen parameters
        
        %% Initial Conditions
        xi =   [0;            % z1
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
        
        %% Load Dynamics Model
        % load([savePath nameDyn])
        
        dynModel.Df = [0; 1/(wec.m+wec.A); 0; 0];
        dynModel.F = @(t) interp1(wave.sig.tFe, wave.sig.Fe, t, 'cubic', 'extrap');
        
        %% Simulation
        simData = hydPTO_ActiveSystem(tspan, dynModel, init, pto, wec, wave);
        
        fprintf('\nSimulations completed\n')
        
        %% Quick plots
        if quickPlots == 1
            close all
            close all hidden
            
            val = 600;
            [t_delta, t_ind] = min(abs(simData.time-val));
            
            tspan = [simData.time(t_ind) simData.time(end)];
            simData = getStats(simData, tspan, pto, wec, wave, con);
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
            
            save([analysisPath 'ActiveSystem_' nameWave '_' paramName{i} '_' num2str(j)], 'out')
            %             pause
            
        end
    end
end

% Close out
rmpath(funPath)
rmpath(savePath)