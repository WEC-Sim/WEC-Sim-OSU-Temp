function [con, wec, pto] = loadSimParameters_PassiveSystem(savePath, namePTO, T)

%% Physical Constants
con.rho = 1025;     % Density of saltwater [kg/m^3]
con.g   = 9.81;     % acceleration due to gravity [m/s^2]

%% WEC Buoy Parameters
wec.h           = 4;                                % See pg. 185 Falnes
wec.d           = wec.h*2;                          % Float radius [m]
wec.V           = pi*wec.d^2/4*wec.h;               % displaced volume 
wec.m           = wec.V*con.rho;                    % mass required for equilibrium
[wec.B, wec.A]  = getHydroParams(wec.d, wec.h, T);  % assumes 10s waves 
wec.K           = pi*con.rho*con.g*wec.d^2/4;
wec.omega_0     = sqrt(wec.K/(wec.m+wec.A)); 
wec.T_0         = 2*pi/wec.omega_0; 

%% Hydraulic PTO Parameters

% Load Size Data from - 'PTO_Size_Caller.m'
load([savePath namePTO], 'ptoS')

% Fluid
pto.rho   = 850;                                        % Hydraulic Fluid Density
pto.v     = 5.5e-5;                                     % kinematic viscosity at 40C - hydraulic formulary
pto.Rt    = 10;                                         % Transition Reynolds number - merrit

% Valve
pto.Cd          = 0.61;
pto.Av          = 0.001;
pto.Dh          = sqrt(4*pto.Av/pi); 
pto.Amax        = pto.Av;                                     % For valve area equation 
pto.Amin        = 1e-8; 
pto.pmax        = 1e6;
pto.pmin        = 3/4*pto.pmax;
pto.av1         = (pto.Amax - pto.Amin)/2+pto.Amin;
pto.av2         = (pto.Amax - pto.Amin)/2;
pto.av3         = (pto.pmax+pto.pmin)/2; 
pto.k1          = 200;     % absolute value 
pto.k2          = atanh((pto.Amin - (pto.Amax - pto.Amin)/2)...
                    *2/(pto.Amax - pto.Amin))* 1/(pto.pmin - (pto.pmax+pto.pmin)/2); %25; 2.5e-4;     % Valve opening
pto.pCrack      = 0; 

% Pump
pto.Ap      = 1.5*ptoS.pump.A_p;                            % Area of pump
pto.d_p     = ptoS.pump.d_p;
pto.b_e     = 1.86e9;
pto.V0      = pto.Ap*5;
pto.Ct      = 0.10*pto.Ap/ptoS.motor.del_p_r;  % (1 - volEff_total)*QmaxPump/pAmax            %2.4e-12; 1.86e-9 ;
% pto.Ci      = 1.4e-11;

% Motor/Gen
pto.D       = ptoS.motor.V_nom;                         % Nominal motor displacement
pto.J       = 3.961;                                        % Total moment of inertia - drive train
pto.bg      = ptoS.gen.bg;   %2.1/1.583*                           % generation damping
pto.tau_r   = ptoS.gen.tau_r;                           % Total generator torque
pto.alpha   = 1; %180/250;
pto.omega_r = ptoS.gen.omega_r; 
pto.bf      = 0.05*pto.bg; 

% % Tank
pto.p_T     = 1.01325e5;                                % Tank pressure

% Accumulator D
pto.vD0    = 3;                                         % Accumulator volume
pto.pDr    = 16e6; %18.75e6; %pDr(i);
pto.pD2    = 4/3*pto.pDr; %                             % Upper working pressure
pto.pD1    = 0.5*pto.pD2;                               % Lower working pressure
pto.pD0    = 0.9*pto.pD1;                               % Precharge pressure
pto.vD2    = pto.vD0*(1-(pto.pD0/pto.pD2)^(1/1.4));     % Max volume of oil in accumulator
pto.vD1    = pto.vD0*(1-(pto.pD0/pto.pD1)^(1/1.4));     % Min volume of oil in accumulator
pto.vDeq   = pto.vD2;
pto.pDeq   = pto.pD0/(1-pto.vDeq/pto.vD0)^1.4;

% Accumulator C
pto.vC0    = 7.5;% a(j)*pto.vD0;                          % Accumulator volume
pto.pCeq   = pto.pDeq;
pto.pCr    = (ptoS.motor.del_p_r + pto.pDr);
pto.pC1    = pto.pCeq;
pto.pC0    = 0.9*pto.pC1;
pto.vCeq   = pto.vC0*(1-(pto.pC0/pto.pCeq)^(1/1.4));    % Min volume of oil in accumulator
pto.pC2    = 1.5*pto.pC1;  %pto.pCr;%
pto.vC2    = pto.vC0*(1-(pto.pC0/pto.pC2)^(1/1.4));     % Max volume of oil in accumulator
pto.vC1    = pto.vC0*(1-(pto.pC0/pto.pC1)^(1/1.4));     % Min volume of oil in accumulator

pto.pAeq   = pto.pCeq; 
pto.pBeq   = pto.pCeq; 
