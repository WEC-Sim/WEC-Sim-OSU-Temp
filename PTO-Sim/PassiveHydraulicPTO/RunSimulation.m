%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author: Ratanak So
% Graduate Research Assistant
% Oregon State University
% Reference model by Sean Casey
% Detail of Sean's work can be found below 
% Modeling, Simulation, and Analysis of Two Hydraulic Power Take-off 
% Systems for Wave Energy Conversion
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Passive Hydraulic PTO

clear all
close all
clc


%% Load Relative Velocity

%load zDot_regular_wave
load zDot_irregular_wave


%% Simulation Parameters

param.stop = 200;


%% Constants

Ap = 2.35e-2;                       % Piston area [m^2]
Beta_e = 1.86e9;                    % Effective bulk modulus [Pa]
Vo = Ap*5;                          % Vol. Cylinder Chamber [m^3]                                     
Cd = 0.61;                          % Discharge coefficient
Amax = 0.001;                       % Maximum valve area [m^2]
Amin = 1e-8;                        % Minimum valve area [m^2]
pMax = 1e6;                         % Maximum area pressure [Pa]
pMin = 0.75e6;                      % Cracking pressure [Pa]
rho = 850;                          % Hydraulic fluid density [kg/m^2]
alpha = 1;                          % Swashplate angle ratio 
bg = 2.3747;                        % Generator damping [kg-m^2/s]
bf = 0.05*bg;                       % Fractional damping [kg-m^2/s]
D = 3.9789e-5;                      % Norminal Motor displacement [m^3]
J = 3.961;                          % Motor Moment of Inertia [kg-m^2] 
Rt = 10;                            % Transition reynolds number - merrit                                    
v = 5.5e-5;                         % Kinematic viscosity at 40 degree C
Av = 0.001;                         % Valve area [m^2]
Dh = sqrt(4*Av/pi);                 % Valve diameter [m]
omegaInit = 0;                        
omegaGen = 251.3274;               % Rotational speed of the generator

k1 = 200;                             
k2 = atanh((Amin-(Amax-Amin)/2)*...
     2/(Amax - Amin))*1/(pMin-(pMax + pMin)/2);                      



%% Low Pressure Accumulator D 
                  
VD0 = 3;                                    % Vol. Accumulator D [m^3]
pDrated = 16e6;                             % Rated working pressure
pDupper_limit = (4/3)*pDrated;              % Uppder working pressure   
pDlower_limit = (0.5)*pDupper_limit;        % Lower workig pressure
pDprecharge = 0.9*pDlower_limit;            % Precharge pressure

VDmax = VD0*(1-(pDprecharge/pDupper_limit)^(1/1.4));  
VDmin = VD0*(1-(pDprecharge/pDlower_limit)^(1/1.4));
VDeq = VDmax;
pDeq = pDprecharge/(1-VDeq/VD0)^(1.4);


%% High Pressure Accumulator C

VC0 = 7.5;                                  % Vol. Accumulator C [m^3]

motor.del_p_r = 15e6;

pCrated = motor.del_p_r + pDrated;
pCeq = pDeq;
pClower_limit = pCeq;
pCupper_limit = 1.5*pClower_limit;
pCprecharge = 0.9*pClower_limit;

VCeq = VC0*(1-(pCprecharge/pCeq)^(1/1.4));
VCmax = VC0*(1-(pCprecharge/pCupper_limit)^(1/1.4));
VCmin = VC0*(1-(pCprecharge/pClower_limit)^(1/1.4));


%% Top and Bottom Pressures A and B 

pAeq = pCeq;
pBeq = pCeq;
pAupper_limit = 32e6;
pAlower_limit = 20e6;

% Pressure A
pAi = pAeq;                     

% Pressure B

pBi = pBeq;
pBupper_limit = 32e6;
pBlower_limit = 20e6;


%% Simulation

sim('Passive_Hydraulic_PTO_Sim')

HighPressure = logsout.getElement(1);
HighPressure = HighPressure.Values(:,1);
HighPressure = HighPressure.Data;

LowPressure = logsout.getElement(2);
LowPressure = LowPressure.Values(:,1);
LowPressure = LowPressure.Data;

zDot = logsout.getElement(3);
zDot = zDot.Values(:,1);
zDot = zDot.Data;

Tgen = logsout.getElement(4);
Tgen = Tgen.Values(:,1);
Tgen = Tgen.Data;

Vdotm = logsout.getElement(5);
Vdotm = Vdotm.Values(:,1);
Vdotm = Vdotm.Data;

omega = logsout.getElement(6);
omega = omega.Values(:,1);
omega = omega.Data;

Pmech = logsout.getElement(7);
Pmech = Pmech.Values(:,1);
Pmech = Pmech.Data;

Fpto = logsout.getElement(10);
Fpto = Fpto.Values(:,1);
Fpto = Fpto.Data;

Vdotp = logsout.getElement(11);
Vdotp = Vdotp.Values(:,1);
Vdotp = Vdotp.Data;

TopPistonPressure = logsout.getElement(9);                 
TopPistonPressure = TopPistonPressure.Values(:,1);
TopPistonPressure = TopPistonPressure.Data;

BottomPistonPressure = logsout.getElement(8);              
BottomPistonPressure = BottomPistonPressure.Values(:,1);
BottomPistonPressure = BottomPistonPressure.Data;

Pabs = logsout.getElement(12);
Pabs = Pabs.Values(:,1);
Pabs = Pabs.Data;

Vdot1 = logsout.getElement(13);
Vdot1 = Vdot1.Values(:,1);
Vdot1 = Vdot1.Data;

Vdot2 = logsout.getElement(14);
Vdot2 = Vdot2.Values(:,1);
Vdot2 = Vdot2.Data;

Vdot3 = logsout.getElement(15);
Vdot3 = Vdot3.Values(:,1);
Vdot3 = Vdot3.Data;

Vdot4 = logsout.getElement(16);
Vdot4 = Vdot4.Values(:,1);
Vdot4 = Vdot4.Data;


%% Plots

set(0,'DefaultFigureWindowStyle','docked')

figure
plot(time,zDot);
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('m/s')
title('zDot')
grid on

figure
plot(time,TopPistonPressure/1e6,time,BottomPistonPressure/1e6,time,HighPressure/1e6,time,LowPressure/1e6);
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Pressure (MPa)')
title('Pressure')
legend('TopPistonPressure','BottomPistonPressure','HighPressure','LowPressure');
grid on

figure
plot(time,Fpto/1e6);
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Force (MN)')
title('PTO Force')
legend('F_{pto}');
grid on

figure
plot(time,Vdotm,time,Vdotp)
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Volumetric Flow (m^3/s)')
title('Motor and Pump Volumetric Flow')
legend('Vdot_m','Vdot_p')
grid on

figure
plot(time,Vdot1,time,Vdot2,time,-Vdot3,time,-Vdot4)
set(findall(gcf,'type','axes'),'fontsize',18)
legend('Vdot_1','Vdot_2','Vdot_3','Vdot_4')
grid on

figure
subplot(211)
plot(time,omega,time,omegaGen*ones(length(time),1))
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Speed (rad/s)')
title('Generator Speed')
grid on
subplot(212)
plot(time,Tgen)
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Generator Torque (N-m)')
title('Generator Torque')
grid on


figure
subplot(211)
plot(time,Pabs/1e3,time,Pmech/1e3)
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Absorbed vs. Mechanical Power')
legend('P_{abs}','P_{mech}')
grid on
subplot(212)
plot(time, (Pabs-Pmech)/1e3)
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Efficiency Measure')
legend('P_{abs} - P_{mech}')
grid on




