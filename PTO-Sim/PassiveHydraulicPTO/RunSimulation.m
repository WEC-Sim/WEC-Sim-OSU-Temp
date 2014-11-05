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

reply = input('Regular Wave (a) or Irregular Wave (b)?: ','s');
if reply == 'a'
    load zDot_regular_wave
elseif reply == 'b'
    load zDot_irregular_wave
else
    error('Invalid choice')
end



%% Simulation Parameters

param.stop = 400;


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


%% Generator

load motorEff
TgenBase = 1387;
omegaBase = 863;
driveEff = 0.98;

%% Simulation

sim('PassiveHydraulicPTOSim')

time = logsout.getElement('zDot').Values.time;
zDot = logsout.getElement('zDot').Values.Data;
Fpto = logsout.getElement('Fpto').Values.Data;
HighPressure = logsout.getElement('HighPressure').Values.Data;
LowPressure = logsout.getElement('LowPressure').Values.Data;
TopPistonPressure = logsout.getElement('TopPistonPressure').Values.Data; 
BottomPistonPressure = logsout.getElement('BottomPistonPressure').Values.Data;              
Vdotp = logsout.getElement('Vdotp').Values.Data;
Vdot1 = logsout.getElement('Vdot1').Values.Data;
Vdot2 = logsout.getElement('Vdot2').Values.Data;
Vdot3 = logsout.getElement('Vdot3').Values.Data;
Vdot4 = logsout.getElement('Vdot4').Values.Data;
Vdotm = logsout.getElement('Vdotm').Values.Data;
omega = logsout.getElement('omega').Values.Data;
Tgen = logsout.getElement('Tgen').Values.Data;
Pabs = logsout.getElement('Pabs').Values.Data;
Pmech = logsout.getElement('Pmech').Values.Data;
Tpu = logsout.getElement('Tpu').Values.Data;  
omegapu = logsout.getElement('omegapu').Values.Data;
genEff = logsout.getElement('genEff').Values.Data;
Pelec = logsout.getElement('Pelec').Values.Data;


%% Power Calculation

start = 12180;  % Steady-state for irregular wave.

avgPabs = trapz(time(start:end),Pabs(start:end)/1e3)/time(end-(start-1));
avgPelec= trapz(time(start:end),Pelec(start:end)/1e3)/time(end-(start-1));
Eff = avgPelec/avgPabs;

fprintf('Average Absorbed Power is %0.2f kW\n',avgPabs)
fprintf('Average Electrical Power is %0.2f kW\n',avgPelec)
fprintf('Efficiency is %0.2f \n',Eff)


%% Plots

set(0,'DefaultFigureWindowStyle','docked')

figure
plot(time,zDot);
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Velocity (m/s)')
title('Buoy Velocity')
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
grid on

figure
plot(time,Vdotp,time,Vdotm)
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Volumetric Flow (m^3/s)')
title('Pump and Motor Volumetric Flow')
legend('Vdot_{pump}','Vdot_{motor}')
grid on

figure
plot(time,Vdot1,time,Vdot2,time,-Vdot3,time,-Vdot4)
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Volumetric Flow (m^3/s)')
title('Valve Volumetric Flow')
legend('Vdot_1','Vdot_2','Vdot_3','Vdot_4')
grid on

figure
subplot(211)
plot(time,omegaGen*ones(length(time),1),time,omega)
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Speed (rad/s)')
title('Generator Speed')
legend('Operational','Actual')
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

figure
plot(time,genEff)
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Efficiency')
title('Generator Efficiency')
grid on

figure
plot(time,Pmech/1e3,time,Pelec/1e3)
set(findall(gcf,'type','axes'),'fontsize',18)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Mechanical vs. Electrical Power')
legend('P_{mech}','P_{elec}')
grid on


