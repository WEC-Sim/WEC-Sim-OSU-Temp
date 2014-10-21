% % Run Simulation for Hydraulic PTO
% % This Model has accumulators
% % Kelley Ruehl OSU GRA
% % Modified by Kelley Ruehl 1/21/2011
% % Modified by Bret Bosma 1/12/2011
%% NOTE:
    % Changed T = 13s
    % Electric Generator Control Gain = 0;
    % Omitted Fpto switch
    % Changed Fpto Calc
    
%% Documentation for running file
%  The physical properties of the buoy, plate, mooring, and hydraulic
%  system need to be defined.  
%  See section labeled "Values that need to be defined by the user" to 
%  input these values.  These include physical dimensions, added masses,
%  density, and damping and spring constants as well as mooring and
%  hydraulic specs and initial conditions.
%
%  Five impulse response signals that describe the defined geometry need to
%  be input.  
%  An impulse response with eta input and Force on buoy output
%  An impulse response with eta input and Force on plate output
%  An impulse response with buoy velocity input and Force on buoy output
%  An impulse response with plate velocity input and Force on plate output
%  An impulse response with buoy velocity input and Force on plate from the
%  buoy output
%  The impuse response with plate velocity input and Force on the buoy from
%  the plate output should be the same as the previous input and therefore
%  is not required as an input to this model.
%
%  Once all of the parameters are defined and the impulse response
%  functions have been loaded appropriately it is just a matter of running
%  this m-file.

%% Housekeeping
clc
clear all
close all

%%  Define Constants[metric sys]:

%% Global Values
    rho = 1027;   %% density of salt water [kg/m^3]
    g = 9.81;     %% acceleration of gravity [m/s/s]
    T = 13; %10;      %% Wave Period [s]
    H = 2.5;      %% Wave Height [m] (~8ft)

%% Values that need to be defined by the user follow %%%%%%%%%%%%%%%%%%%%%

% % Hydraulic PTO Specs
% Hyraulic Cylinder Specs
    Dbore = 0.1524;   %% Bore Diameter [m]
    Drod = 0.1016;    %% Rod Diamteter [m]
    D3 = (Dbore+0.1016)/2;  %% Diameter of Piston [m]
    S = 4;      %% Stroke of Piston [m]
    A_bore = pi*Dbore^2/4;  %% Area of Bore [cm^2]
    A_rod = pi*(Dbore^2-Drod^2)/4;  %% Area of Rod [cm^2]
    A_pist =  mean([A_bore,A_rod]);  %% Average Area of Piston [cm^2]
    
% Accumulator Initial Conditions    
    p_atm = 101325;         % Atm Pressure [Pa]
    p_lp(1) = p_atm;     % low pressure accumulator initial pressure [Pa]
    delta_p(1) = 16023415.9;  %Operating Pressure [Pa]<- from report
    p_hp(1) = p_lp(1) + delta_p(1);     % high pressure accumulator initial pressure [Pa]
    
    V_lp(1) = 2;          % low pressure accumulator Ni (tot) volume [m^3]
    V_hp(1) = 50;          % high pressure accumulator Ni (tot) volume [m^3]

% Fixed Displacement Hydraulic Motor Specs (from Model 250 Spec Sheet)
    Vg = 0.00025;      % Fixed Displacement Motor Chamber Volume [m^3]
    Tc = 0.00001393; %3.2/10^5;         % Pressue to Torque Conversion [N-m/Pa] 
    delta_p_min = 160*10^5;     % Min Motor Pressure Difference [Pa]
    Rot_Fric = 2.1; %1.7; %.7;      % Rotary Damping [Nm/(rad/s)]
    Rot_Stiffness = 0; %73100;      % Rotary Stiffness [Nm/rad]
    J = 0.061;           % Motor Moment of Intertia [kg-m^2]<- from data sheet
    hyd_mot_eff = 0.93;   % Hydraulic Motor vol/mech Efficiency <- from report
    hyd_mot_tot = 0.865;   % Hydraulic Motor TOTAL Efficiency <- from report
    pump_vol_eff = 0.97;    %% Pump volumetric efficiency <- from report
    elec_gen_eff = 0.95;   %Electric Generator Efficiency <- from report
    
%% Electric motor and drive constants
% Taken from ABB datasheet part num M3BJ315SMC
load motor_eff
Tgenbase=1387;
wgenbase=863;
Jgen=3.9;

% Drive Efficiency from data sheet ACS800-17-0210-5+C129 at nominal power
drive_eff=.98;

% RUN SIMULATION
end_sim = 40;   % specifies how long simulation will run
sim('PTO_Model_KelleyFinal.mdl',[0,end_sim]);
   
% % check to make sure PV^1.4 = constant for HP and LP
%  for i=1:length(p_hp)
%      c_hp(i) = p_hp(i)*V_hp_Ni(i)^1.4;
%      c_lp(i) = p_lp(i)*V_lp_Ni(i)^1.4;
%  end
% c_hp(1)
% c_lp(1)
% % % ------------------------------------- %%


figure(1)
subplot(2,1,1)
plot(time,logsout.('Hydraulic PTO').Vdot_pist.Data)
title('Volumetric Flow')
ylabel('Piston Volumetric Flow (m^3/s)')
subplot(2,1,2)
plot(time,logsout.('Hydraulic PTO').Vdot_m.Data)
ylabel('Motor Volumetric Flow (m^3/s)')
xlabel('time (s)')

figure(2)
subplot(4,1,1)
plot(time,logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.Tau_com.Data)
title('Torques')
ylabel('Combined Torque (Nm)')
subplot(4,1,2)
plot(time,logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.Tau_hm.Data)
ylabel('Torque Input (Nm)')
subplot(4,1,3)
plot(time,logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.Tau_hm_loss.Data)
ylabel('Torque Mot Loss (Nm)')
subplot(4,1,4)
plot(time,logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.Tau_gen_loss.Data)
ylabel('Torque Gen Loss (Nm)')
xlabel('time (s)')

figure(3)
subplot(3,1,1)
plot(time,logsout.('Hydraulic PTO').delta_p.Data)
ylabel('Pressure Difference (Pa)')
title('Hydraulic Motor')
subplot(3,1,2)
plot(time,logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.ang_vel.Data)
ylabel('Hydrualic motor speed [rad/s]')
subplot(3,1,3)
plot(time,logsout.('Hydraulic PTO').Fpto.Data)
ylabel('Piston Force (N)')
xlabel('time (s)')

figure(4)
subplot(2,1,1)
plot(time,logsout.('Hydraulic PTO').p_hp.Data)
ylabel('Pressure HP (Pa)')
title('Pressures')
subplot(2,1,2)
plot(time,logsout.('Hydraulic PTO').p_lp.Data)
ylabel('Pressure LP (Pa)')
xlabel('time (s)')

figure(5)
subplot(2,1,1)
plot(time,logsout.('Hydraulic PTO').Ppto.Data)
title('Power')
ylabel('Power available to PTO (kW)')
subplot(2,1,2)
plot(time,Pout)
ylabel('Power out hydrualic motor(kW)')
xlabel('time (s)')

figure(6)
subplot(211),plot(time,logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.P_elec.Data)
ylabel('Delivered electric power')
subplot(212),plot(time,logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.Gen_Drive_Efficiency.gen_eff.Data)
xlabel('time(sec)'),ylabel('Generator Efficiency')
% 
% figure(7)
% subplot(211),mesh(tot.wpu(1,:),tot.Tpu,tot.eff)
% xlabel('w(pu)'),ylabel('T(pu)')
% view(2)
% % wpulen=length(logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.Gen_Drive_Efficiency.w_pu.Data);
% % Tpulen=length(logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.Gen_Drive_Efficiency.T_pu.Data);
% subplot(212),plot(logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.Gen_Drive_Efficiency.w_pu.Data,logsout.('Hydraulic PTO').Hydr_Mot_Gen_Drive.Gen_Drive_Efficiency.T_pu.Data,'.')
% xlabel('w(pu)'),ylabel('T(pu)')
% grid on
% 
% 
