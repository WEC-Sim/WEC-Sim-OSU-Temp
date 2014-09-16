function [con, wec, pto] = loadSimulationParameters(savePath, namePTO, nameSystemType, T)

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

% Common Parameters
% Fluid
pto.rho     = 850;                   % Hydraulic Fluid Density
pto.v       = 5.5e-5;                % kinematic viscosity at 40C - hydraulic formulary
pto.Rt      = 10;                    % Transition Reynolds number - merrit
pto.b_e     = 1.86e9;                % Bulk Modulus of the fluid
% Pump
pto.Ap      = 1.5*ptoS.pump.A_p;     % Area of pump - multiplied by 1.5 for better performance 
pto.dp      = ptoS.pump.d_p;         % Diameter of pressurized area of pump
pto.V0      = pto.Ap*5;              % Volume of pump                   
% Motor/Gen
pto.D       = ptoS.motor.V_nom;      % Nominal motor displacement
pto.J       = 3.961;                 % Total moment of inertia - drive train
pto.bg      = 1*ptoS.gen.bg;         % generation damping
pto.bf      = 0.05*pto.bg;
pto.tau_r   = ptoS.gen.tau_r;        % Total generator torque
pto.alpha   = 1;
pto.omega_r = ptoS.gen.omega_r;

% System Pressure
pto.p_T     = 1.01325e5;             % Tank pressure
pto.delP_r  = ptoS.motor.del_p_r;

switch nameSystemType
    case 'Active'
        
        pto.Ct = 0.10*pto.Ap/40e6;  % Total leakage coeficient
        pto.Ci = 1.4e-11;           % Internal leakage coeficient
        pto.pR = 2e6;               % Charge pump pressure 
        
    case 'Passive'
        
        % Valve
        pto.Cd     = 0.61;                               
        pto.Av     = 0.001;
        pto.Dh     = sqrt(4*pto.Av/pi);
        pto.Amax   = pto.Av;                                                    % Maximum valve area
        pto.Amin   = 1e-8;                                                      % Minimum valve area
        pto.pmax   = 1e6;                                                       % Pressure threshold where valve is fully open
        pto.pmin   = 3/4*pto.pmax;                                              % Pressure threshold where valve is fully closed
        pto.av1    = (pto.Amax - pto.Amin)/2+pto.Amin;                          % Term 1 in valve opening equation
        pto.av2    = (pto.Amax - pto.Amin)/2;                                   % Term 2 in valve opening equation
        pto.av3    = (pto.pmax+pto.pmin)/2;                                     % Term 3 in valve opening equation
        pto.k1     = 200;                                                       % tanh function -- absolute value
        pto.k2     = atanh((pto.Amin - (pto.Amax - pto.Amin)/2)...              % tanh function -- valve opening
            *2/(pto.Amax - pto.Amin))* 1/(pto.pmin - (pto.pmax+pto.pmin)/2);    
        pto.pCrack = 0;                                                         % Leakage through valve (Might not use) check
        
        % Accumulator D - low pressure resevoir
        pto.vD0    = 3;                                         % Accumulator volume
        pto.pDr    = 16e6;                                      % Rated working pressure
        pto.pD2    = 4/3*pto.pDr; %                             % Upper working pressure
        pto.pD1    = 0.5*pto.pD2;                               % Lower working pressure
        pto.pD0    = 0.9*pto.pD1;                               % Precharge pressure
        pto.vD2    = pto.vD0*(1-(pto.pD0/pto.pD2)^(1/1.4));     % Max volume of oil in accumulator
        pto.vD1    = pto.vD0*(1-(pto.pD0/pto.pD1)^(1/1.4));     % Min volume of oil in accumulator
        pto.vDeq   = pto.vD2;                                   % Volume of oil at equilibrium pressure
        pto.pDeq   = pto.pD0/(1-pto.vDeq/pto.vD0)^1.4;          % Equilibrium pressure
        
        % Accumulator C - high pressure accumulator
        pto.vC0    = 7.5;                                       % Accumulator volume
        pto.pCeq   = pto.pDeq;                                  % Equilibrium pressure                         
        pto.pCr    = (ptoS.motor.del_p_r + pto.pDr);            % Rated working pressure
        pto.pC1    = pto.pCeq;                                  % Lower working pressure
        pto.pC0    = 0.9*pto.pC1;                               % Precharge pressure
        pto.vCeq   = pto.vC0*(1-(pto.pC0/pto.pCeq)^(1/1.4));    % Volume of oil at equilibrium
        pto.pC2    = 1.5*pto.pC1;                               % Upper working pressure
        pto.vC2    = pto.vC0*(1-(pto.pC0/pto.pC2)^(1/1.4));     % Max volume of oil in accumulator
        pto.vC1    = pto.vC0*(1-(pto.pC0/pto.pC1)^(1/1.4));     % Min volume of oil in accumulator
        
        pto.pAeq   = pto.pCeq;                                  % Equilibrium pressures for pump
        pto.pBeq   = pto.pCeq;
        
end