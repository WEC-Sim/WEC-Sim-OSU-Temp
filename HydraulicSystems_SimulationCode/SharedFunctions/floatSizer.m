clear; clc; close all; 
set(0,'DefaultFigureWindowStyle','docked')
simPath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\HydPTO_ClosedCircuit\Functions\';
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\HydPTO_ClosedCircuit\SimulationDataFiles\';
addpath(simPath);
addpath(savePath);

%% Float sizer 
ti = 0; 
tf = 300; 

% Constants 
rho = 1025; 
g   = 9.81; 

% Time
df = 1/tf;

% Wave Data
Ts =  10;                         % Significant wave period
Hs = 3;         

waveRep = makeRepWaves(Ts, Hs, df, 1);

k = waveRep.zComp.k;
sigma = waveRep.zComp.sigma;
L = waveRep.zComp.L;
h = 1000; 
C = sigma/k;

d = 6;              % Diameter of float
A = pi*d^2/4;       % Area of float 

E = 1/8*rho*g*Hs^2              % Energy per unit surface area
E_L = E*waveRep.zComp.L;        % Energy per wave per unit width

E2float = E*A 
E_L2float = E_L*d

% Dean and Dalrymple
Cg = 1/2*(1 + 2*k*h/sinh(2*k*h))*C      % Group velocity
P = E*Cg                                % power available per unit crest length

Pfloat = P*d*1e-3

% pg 35 MJ Tucker and EG Pitt
CgBook = g/4/pi*Ts
Pbook = 1/2*rho*g*(Hs/2)^2*CgBook
