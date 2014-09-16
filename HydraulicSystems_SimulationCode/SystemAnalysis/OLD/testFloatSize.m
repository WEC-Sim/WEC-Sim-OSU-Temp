%% Non-Linear Hydraulic PTO - GMREC Conference
% Sean Casey
% 3/4/13
% GRA - OSU
%
%   find float size with good damping charecteristics
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
waveSrc             = 1;       % 1 == 'Regular', 0 == 'Irregular'
makeNewWaves        = 1;
doSim               = 1;

nameWave            = 'waveRegTest';
nameDyn             = 'dynModel_ActiveSystem';
namePTO             = 'PTO_150kW_Hs3_Ts10_ActiveSystem';        % Specify PTO determined from 'PTOsizeCaller.m'

%% Simulation parameters
% Configuration parameters
init.ti = 0;                % Initial time
init.tf = 200;              % Final time
init.del_t = 0.01;          % Step size

tspan = [init.ti, init.tf];
%% Signal Data
% Time
df = 1/init.tf;

% Wave Data
Ts =  10;                       % Significant wave period
Hs = 3;                         % Significant wave height

if makeNewWaves == 1
    wave = makeRepWaves(Ts, Hs, df, waveSrc);
    save([savePath nameWave], 'wave')
else
    load([savePath nameWave])
end

%% Load Physical Parameters
% Physical Constants
con.rho = 1025;     % Density of saltwater [kg/m^3]
con.g   = 9.81;     % acceleration due to gravity [m/s^2]

% Hydraulic PTO Parameters

% Load Size Data from - 'PTO_Size_Caller.m'
load([savePath namePTO], 'ptoS')

% Fluid
pto.rho     = 850;                                      % Hydraulic Fluid Density
pto.b_e     = 1.86e9;                                   % Bulk Modulus of the fluid

% Pump
pto.Ap      = 1.5*ptoS.pump.A_p;                            % Area of pump*
pto.dp      = ptoS.pump.d_p;
pto.V0      = pto.Ap*3;
pto.Ct       = 0.10*pto.Ap/30e6;  % (1 - volEff_total)*QmaxPump/pAmax            %2.4e-12; 1.86e-9 ;
pto.Ci      = 1.4e-11;
% pto.Ct      = 9.0e-11;
pto.pR      = 2e6;  0;

% Motor/Gen
pto.D       = ptoS.motor.V_nom;                         % Nominal motor displacement
pto.J       = 3.961;                                    % Total moment of inertia - drive train
pto.bg      = 1*ptoS.gen.bg;                              % generation damping
pto.bf      = 0.05*pto.bg;
pto.tau_r   = ptoS.gen.tau_r;                           % Total generator torque
pto.alpha   = 1;
pto.omega_r = ptoS.gen.omega_r;

pto.delP_r = ptoS.motor.del_p_r;

figure
%%
h = [1 2 3 4 5];
d = [2 3 4];
col = distinguishable_colors(20);
for j = 1:length(d)
    for i = 1:length(h)
        
        % WEC Buoy Parameters
        wec.h           = h(i);                     % See pg. 185 Falnes
        wec.d           = wec.h*d(j);                 % Float radius [m]
        wec.V           = pi*wec.d^2/4*wec.h;       % displaced volume
        wec.m           = wec.V*con.rho;            % mass required for equilibrium
        T = 10;
        [wec.B, wec.A]  = getHydroParams(wec.d, wec.h, T);  % assumes 10s waves
        wec.K           = pi*con.rho*con.g*wec.d^2/4;
        
        
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
        
        subplot(3,1, j)
        plot(wave.sig.tFe, wave.sig.eta(:,2), 'color', col(end,:));  hold on
        c = plot(wave.sig.tFe, wave.zDotOpt, 'color', col(i,:));
        legend(c, ['h = ' num2str(h(i))])
        
    end
    
end

