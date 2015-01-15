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
   %load zDot_regular_wave_fixedStep   
elseif reply == 'b'
    load zDot_irregular_wave
    %load zDot_irregular_wave_fixedStep
else
    error('Invalid choice')
end

%% Start Time for Power Calculation

start = 369945;        %between 200 and 300 seconds for variable step ode45 

%**************************************************************************
% In order to run fixed step and ode4, you need to manually go to 
% Configuration Parameters and change your type and solver.
% I will improve this.
%**************************************************************************

%start = 2000001;          %between 200 and 300 seconds for fixed step ode4 


%% Simulation Parameters

param.stop = 300;


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
% Rt = 10;                            % Transition reynolds number - merrit                                    
% v = 5.5e-5;                         % Kinematic viscosity at 40 degree C
% Av = 0.001;                         % Valve area [m^2]
% Dh = sqrt(4*Av/pi);                 % Valve diameter [m]
omegaInit = 0;                        
omegaGen = 251.3274;                % Rotational speed of the generator

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

pAeq = pDupper_limit;
pBeq = pDupper_limit;
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
tic
sim('PassiveHydraulicPTOSim')
%saveas(get_param('PassiveHydraulicPTOSim/PassiveHydraulicPTO','Handle'),'ptomodel.eps','psc2')
%saveas(gcf,'ptomodel.eps', 'psc2')
toc

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
VdotC = logsout.getElement('VdotC').Values.Data;
VdotD = logsout.getElement('VdotD').Values.Data;
omega = logsout.getElement('omega').Values.Data;
Tgen = logsout.getElement('Tgen').Values.Data;
Pabs = logsout.getElement('Pabs').Values.Data;
Pgen = logsout.getElement('Pgen').Values.Data;
Tpu = logsout.getElement('Tpu').Values.Data;  
omegapu = logsout.getElement('omegapu').Values.Data;
genEff = logsout.getElement('genEff').Values.Data;
Pelec = logsout.getElement('Pelec').Values.Data;

%% Energy Storage Calculation
 
PaccumC = HighPressure.*VdotC;
PaccumD = LowPressure.*VdotD;
Pfric = bf*omega.^2;
Pmotor = (HighPressure - LowPressure).*Vdotm;
Pmech = PaccumC + PaccumD + Pmotor;
Pvalve = Pabs - Pmech;
%% Power Calculation

         
%start = 127568;          % between 200 and 300 seconds for variable step
%start = 2000001;         % between 200 and 300 seconds for fixed step

% avgPabs=mean(Pabs(start:end))/1e3;
% avgPmech = mean(Pmech(start:end))/1e3;
% avgPelec = mean(Pelec(start:end))/1e3;

avgPabs = trapz(time(start:end),Pabs(start:end)/1e3)/time(end-(start-1));
avgPvalve = trapz(time(start:end),Pvalve(start:end)/1e3)/time(end-(start-1));
avgPaccumC = trapz(time(start:end),PaccumC(start:end)/1e3)/time(end-(start-1));
avgPaccumD = trapz(time(start:end),PaccumD(start:end)/1e3)/time(end-(start-1));
avgPmech = trapz(time(start:end),Pmech(start:end)/1e3)/time(end-(start-1));
avgPelec= trapz(time(start:end),Pelec(start:end)/1e3)/time(end-(start-1));

Eff_abs2mech = avgPmech/avgPabs;
Eff_abs2elec = avgPelec/avgPabs;
Eff_mech2elec = avgPelec/avgPmech;

fprintf('Average Absorbed Power is %0.2f kW\n',avgPabs)
fprintf('Average Rectifying Valve Power is %0.2f kW\n',avgPvalve)
fprintf('Average Accumulator C Power is %0.2f kW\n',avgPaccumC)
fprintf('Average Accumulator D Power is %0.2f kW\n',avgPaccumD)
fprintf('Average Mechanical Power is %0.2f kW\n',avgPmech)
fprintf('Average Electrical Power is %0.2f kW\n',avgPelec)
fprintf('Efficiency from Absorbed to Mechanical Power is %0.2f \n',Eff_abs2mech)
fprintf('Efficiency from Absorbed to Electrical Power is %0.2f \n',Eff_abs2elec)
fprintf('Efficiency from Mechanical to Electrical Power is %0.2f \n',Eff_mech2elec)

%% Normalization 

Fpto_n = Fpto/1e6;
TopPistonPressure_n = TopPistonPressure/20e6;
BottomPistonPressure_n = BottomPistonPressure/20e6;
Vdot1_n = Vdot1*20;
Vdot2_n = Vdot2*30;
Vdot3_n = Vdot3*30;
Vdot4_n = Vdot4*30;


%% Normalized Power

maxPabs = max(Pabs(start:end));
normPabs = Pabs(start:end)/maxPabs;
normPmech = Pmech(start:end)/maxPabs;
normPelecHDY = Pelec(start:end)/maxPabs;


%% Plots

set(0,'DefaultFigureWindowStyle','docked')

% fontsize 16 vs. 8

f = figure;
plot(time,zDot,'b',time,Fpto_n,'k',time,TopPistonPressure_n,'--go',time,BottomPistonPressure_n,':r*',time,Vdot1_n,':',time,Vdot2_n,':',time,-Vdot3_n,':',time,-Vdot4_n,':')
set(findall(gcf,'type','axes'),'fontsize',16)
set(findall(gcf,'Type','line'),'LineWidth',2)
xlabel('Time (s)')
legend('zDot','Fpto_n','pA_n','pB_n','Vdot1_n','Vdot2_n','Vdot3_n','Vdot4_n')
grid on
%axis([292 296 -1 1.5])


f = figure;
plot(time,zDot);
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Velocity (m/s)')
title('Piston Velocity')
%axis([200 300 -2 2]) 
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','zDot.eps') 

f = figure;
plot(time,TopPistonPressure/1e6,time,BottomPistonPressure/1e6,time,HighPressure/1e6,time,LowPressure/1e6);
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Pressure (MPa)')
title('Piston Pump and Accumulators Pressures')
legend('TopPistonPressure','BottomPistonPressure','HighPressure','LowPressure');
%axis([200 300 5 35]) 
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','Pressures.eps') 

f = figure;
plot(time,Fpto/1e6);
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Force (MN)')
title('PTO Force')
%axis([200 300 -0.5 0.5]) 
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','ptoForce.eps') 


f = figure;
plot(time,Vdotp,time,Vdotm)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Volumetric Flow (m^3/s)')
title('Piston and Motor Volumetric Flows')
legend('Vdot_{piston}','Vdot_{motor}')
%axis([200 300 -0.05 0.05]) 
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','PistonAndMotorVolumetricFlow.eps') 

f = figure;
plot(time,Vdot1,time,Vdot2,time,-Vdot3,time,-Vdot4)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Volumetric Flow (m^3/s)')
title('Valves Volumetric Flows')
legend('Vdot_1','Vdot_2','Vdot_3','Vdot_4')
%axis([200 300 -0.05 0.05])  
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','ValvesVolumetricFlow.eps') 

f = figure;
subplot(211)
plot(time,omega)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Speed (rad/s)')
title('Generator Speed')
%axis([200 300 150 250]) 
grid on
subplot(212)
plot(time,Tgen)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Generator Torque (N-m)')
title('Generator Torque')
%axis([200 300 350 600]) 
grid on

f = figure;
plot(time,PaccumC/1e3,time,PaccumD/1e3,time,Pmotor/1e3,time,Pmech/1e3)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Pmech = PaccumC + Pmotor + PaccumD')
legend('PaccumC','PaccumD','Pmotor','Pmech')
grid on

f = figure;
subplot(211)
plot(time,Pabs/1e3,time,Pvalve/1e3,time,Pmech/1e3)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Pabs = Pvalve + Pmech')
legend('Pabs','Pvalve','Pmech')
grid on
subplot(212)
plot(time,Pabs/1e3,time,(Pvalve+Pmech)/1e3)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (kW)')
legend('Pabs','P_{mech+valve}')
grid on




