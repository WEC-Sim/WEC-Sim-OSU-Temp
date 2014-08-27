%wavePhysics.m
g =9.81; %gravitational constant, m/s^2
density_w = 1000; %kg/m^3

WaveHeight = .0541; %cm
Amp = WaveHeight/2;
T = 1.4;            %s
w = 2*pi/T;         %rad/s
L = .01;            %cm, characteristic length input to WAMIT

PeakPeriod = 10;
numSin = 100;