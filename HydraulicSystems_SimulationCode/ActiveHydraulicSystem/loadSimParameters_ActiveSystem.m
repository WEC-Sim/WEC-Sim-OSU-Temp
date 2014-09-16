function [con, wec, pto] = loadSimParameters_ActiveSystem(savePath, namePTO, T) 

%% Physical Constants
con.rho = 1025;     % Density of saltwater [kg/m^3]
con.g   = 9.81;     % acceleration due to gravity [m/s^2]

%% WEC Buoy Parameters
wec.h           = 4;                     % See pg. 185 Falnes
wec.d           = wec.h*2;                 % Float radius [m]
wec.V           = pi*wec.d^2/4*wec.h;       % displaced volume 
wec.m           = wec.V*con.rho;            % mass required for equilibrium
% T = 10; 
[wec.B, wec.A]  = getHydroParams(wec.d, wec.h, T);  % assumes 10s waves 
wec.K           = pi*con.rho*con.g*wec.d^2/4;

wec.omega_0 = sqrt(wec.K/(wec.m+wec.A)); 
wec.T_0 = 2*pi/wec.omega_0; 
%% Hydraulic PTO Parameters

% Load Size Data from - 'PTO_Size_Caller.m'
load([savePath namePTO], 'ptoS')

% Fluid
pto.rho     = 850;                                      % Hydraulic Fluid Density
pto.b_e     = 1.86e9;                                   % Bulk Modulus of the fluid 

% Pump
pto.Ap      = 1.5*ptoS.pump.A_p;                            % Area of pump*
pto.dp      = ptoS.pump.d_p;
pto.V0      = pto.Ap*5; 
pto.Ct       = 0.10*pto.Ap/30e6; %0.10*pto.Ap/30e6;  % (1 - volEff_total)*QmaxPump/pAmax            %2.4e-12; 1.86e-9 ;
pto.Ci      = 1.4e-11; %1.4e-11
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

