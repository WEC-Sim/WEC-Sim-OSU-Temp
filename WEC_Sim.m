clc; clear all; close all;

initwafo

addpath('functions')
addpath(genpath('./user_inputs'))
addpath(genpath('./pre_processing'))
addpath(genpath('./time_domain'))
addpath(genpath('./post_processing'))

% read_sim_params;
% readInSTL;
[hydro] = hydroCoes('FDWEC_Control.inp');

% Read Input Control
[hydro, system] = readInputControl('FDWEC_Control.inp',hydro);
StartTime=0;
EndTime=system.numerical.dt*system.numerical.maxIt;
deltaT=system.numerical.dt;
maxIt=system.numerical.maxIt;

% Interpolate the hydrodynamic coefficients based on the given sea states
[hydro, hydroForce, system] = hydroForce(hydro.waves.H(1), hydro.waves.T(1), hydro, system);

% Mooring Values
mooring_c = zeros(6,6);
mooring_k = zeros(6,6); mooring_k(2,2) = 1e6;

% Joint Type
VSS_Linear = Simulink.Variant('vss_joint==1');
VSS_Rotation = Simulink.Variant('vss_joint==2');

vss_joint = 1;

PTOData

NonlinearSetup    %Input data required for quasi- and fully-nonlinear calcs

A_c_F=pi*10^2;      %m^2, cross-sectional area of float for restoring stiffness
A_c_P=pi*3^2;       %m^2, cross-sectional area of plate column for restoring stiffness
sim('WEC_Sim_Driver');
post_processing_script;

