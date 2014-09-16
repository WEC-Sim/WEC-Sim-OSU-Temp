%% Initialize Workspace
clear; %clc; %close all
set(0,'DefaultFigureWindowStyle','docked')
funPath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\PressureRiseRate_PassiveHydraulicSystem\SimulationDataFiles\';
addpath(funPath);
addpath(savePath);

T = 10

con.rho = 1025;     % Density of saltwater [kg/m^3]
con.g   = 9.81;     % acceleration due to gravity [m/s^2]

%% WEC Buoy Parameters
wec.h           = 12;                       % See pg. 185 Falnes
wec.d           = wec.h*2;                  % Float radius [m]
wec.V           = pi*wec.d^2/4*wec.h;       % displaced volume 
wec.m           = wec.V*con.rho;            % mass required for equilibrium
% T = 10;                                     % wave period
[wec.B, wec.A]  = getHydroParams(wec.d, wec.h, T);  % assumes 10s waves 
% wec.B = wec.B;
wec.K           = pi*con.rho*con.g*wec.d^2/4;

wec.omega_0 = sqrt(wec.K/(wec.m+wec.A)); 
wec.T_0 = 2*pi/wec.omega_0
