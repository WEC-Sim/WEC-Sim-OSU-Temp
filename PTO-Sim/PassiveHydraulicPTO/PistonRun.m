clear all
close all
clc


%% Load Relative Velocity



    load zDot_regular_wave
    load zInput
    load VdotInput
    load VdotPInput
    load VAInput
    load VBInput
    
    %load zDot_regular_wave_fixedStep

%% Constants
Ap = 1.5*0.015667;
%Ap = 2.35e-2;                       % Piston area [m^2]
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

%% Simulation
tic
sim('Piston1')
%saveas(get_param('PassiveHydraulicPTOSim/PassiveHydraulicPTO','Handle'),'ptomodel.eps','psc2')
%saveas(gcf,'ptomodel.eps', 'psc2')
toc

time = logsout.getElement('zDot').Values.time;
zDot = logsout.getElement('zDot').Values.Data;
pAdot = logsout.getElement('pAdot').Values.Data;
pBdot = logsout.getElement('pBdot').Values.Data;
pA= logsout.getElement('pA').Values.Data; 
pB = logsout.getElement('pB').Values.Data;
Vdot1 = logsout.getElement('Vdot1').Values.Data;
Vdot2 = logsout.getElement('Vdot2').Values.Data;
Vdot3 = logsout.getElement('Vdot3').Values.Data;
Vdot4 = logsout.getElement('Vdot4').Values.Data;
VdotPP = logsout.getElement('VdotPP').Values.Data;
VDP = logsout.getElement('VDP').Values.Data;

VAInput= logsout.getElement('VAInput').Values.Data; 
VBInput= logsout.getElement('VBInput').Values.Data; 
vA= logsout.getElement('vA').Values.Data; 
vB= logsout.getElement('vB').Values.Data; 


%% Plot

set(0,'DefaultFigureWindowStyle','docked')

f=figure
plot(time,zDot)
legend('zDot')
grid on

f=figure
plot(time,Vdot1,time,Vdot2,time,-Vdot3,time,-Vdot4)
legend('Vdot1','Vdot2','Vdot3','Vdot4');
grid on

f=figure
plot(time,pAdot,time,pBdot)
legend('pAdot','pBdot')
grid on

f=figure
plot(time,pA,time,pB)
legend('pA','pB');
grid on



f=figure
plot(time,VdotPP,time,VDP)
legend('VdotPP','VDP')
grid on

f=figure
subplot(211)
plot(time,VAInput,time,vA)
legend('VAInput','vA')
subplot(212)
plot(time,VBInput,time,vB)
legend('VBInput','vB')