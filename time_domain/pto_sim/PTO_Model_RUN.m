%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Run Simulation for Hydraulic PTO
% This Model has accumulators
% Created by Kelley Ruehl OSU 5/10/2011
% Modified by Kelley Ruehl SNL 5/31/2013
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% NOTE:
    % Omited Generator/Drive subsystem, Generator Modeled as 
    %      rotary damping = 2.1 [Nm/(rad/s)]
    
%% Housekeeping
clc
clear all
close all

%%  Define Constants[metric sys]:
    T = 13;             %% Wave Period [s]
    A = 1;              %% Velocity Amplitude [m/s]

%% PTO Specs

% Hyraulic Cylinder Specs
    Dbore = 0.1524;                 %% Bore Diameter [m]
    Drod = 0.1016;                  %% Rod Diamteter [m]
    A_bore = pi*Dbore^2/4;          %% Area of Bore [cm^2]
    A_rod = pi*(Dbore^2-Drod^2)/4;  %% Area of Rod [cm^2]
    
% Accumulator Initial Conditions    
    p_atm = 101325;             % Atm Pressure [Pa]
    p_lp(1) = p_atm;            % low pressure accumulator initial pressure [Pa]
    delta_p(1) = 16023415.9;    %Operating Pressure [Pa]<- from report
    p_hp(1) = p_lp(1) + delta_p(1);     % high pressure accumulator initial pressure [Pa]
    
    V_lp(1) = 2;                % low pressure accumulator Ni (tot) volume [m^3]
    V_hp(1) = 50;               % high pressure accumulator Ni (tot) volume [m^3]

% Fixed Displacement Hydraulic Motor Specs (from Model 250 Spec Sheet)
    Vg = 0.00025;               % Fixed Displacement Motor Chamber Volume [m^3]
    Jmot = 0.061;               % Motor Moment of Intertia [kg-m^2]<- from data sheet
    hyd_mot_eff = 0.93;         % Hydraulic Motor vol/mech Efficiency <- from report
    hyd_mot_tot = 0.865;        % Hydraulic Motor TOTAL Efficiency <- from report
    pump_vol_eff = 0.97;        % Pump volumetric efficiency <- from report
    
% Electric Generator
    Jgen=3.9;           
    Gen_Damp = 2.1;             % Generator Rotary Damping [Nm/(rad/s)]
    Jtot = Jmot+Jgen;    

% RUN SIMULATION
end_sim = 40;               % specifies how long simulation will run
sim('PTO_Sim_Model.mdl',[0,end_sim]);
   
%% Figures

figure(1)
subplot(3,1,1)
plot(time,logsout.x_dot.Data)
ylabel('Relative Velocity (m/s)')
subplot(3,1,2)
plot(time,logsout.('Hydraulic PTO').Vdot_pist.Data)
ylabel('Piston Volumetric Flow (m^3/s)')
subplot(3,1,3)
plot(time,logsout.('Hydraulic PTO').Vdot_m.Data)
ylabel('Motor Volumetric Flow (m^3/s)')
xlabel('Time [s]')

figure(2)
subplot(3,1,1)
plot(time,logsout.('Hydraulic PTO').('Hydraulic Motor').Tau_com.Data)
title('Torques')
ylabel('Combined Torque (Nm)')
subplot(3,1,2)
plot(time,logsout.('Hydraulic PTO').('Hydraulic Motor').Tau_hm.Data)
ylabel('Torque Input (Nm)')
subplot(3,1,3)
plot(time,logsout.('Hydraulic PTO').('Hydraulic Motor').Tau_gen.Data)
ylabel('Generator Torque (Nm)')
xlabel('Time [s]')

figure(3)
subplot(3,1,1)
plot(time,(logsout.('Hydraulic PTO').delta_p.Data)./10^6)
ylabel('Pressure Difference [MPa]')
title('Hydraulic Motor')
subplot(3,1,2)
plot(time,logsout.('Hydraulic PTO').('Hydraulic Motor').ang_vel.Data)
ylabel('Hydrualic motor speed [rad/s]')
subplot(3,1,3)
plot(time,logsout.('Hydraulic PTO').Fpto.Data)
ylabel('Piston Force (N)')

figure(4)
subplot(2,1,1)
plot(time,logsout.('Hydraulic PTO').p_hp.Data./10^6)
ylabel('Pressure HP [MPa]')
title('Pressures')
subplot(2,1,2)
plot(time,logsout.('Hydraulic PTO').p_lp.Data./10^6)
ylabel('Pressure LP [MPa]')
xlabel('Time [s]')

figure(5)
subplot(2,1,1)
plot(time,Ppto)
title('Power')
ylabel('Power available to PTO (kW)')
subplot(2,1,2)
plot(time,Pout)
ylabel('Power out hydrualic motor(kW)')
xlabel('Time [s]')
