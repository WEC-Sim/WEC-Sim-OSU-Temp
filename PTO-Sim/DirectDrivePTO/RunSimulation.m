%% Housekeeping

clear all
close all
clc

%% Load zDot Data

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

%% Simulation Parameters

param.stop = 300;
%% Constants

Rs = 4.58;
%Rload = -200;        
Rload = -200/1.7;       % Van = 200 Vpeak, Ia = 1.7 A
tau_p = 0.072;          % Magnet pole pitch is 72 mm
%lambda_fd = 1300/(pi/2*2.95*sqrt(2)*3/2*sqrt(2/3));
%lambda_fd = 5;         % Dr. Brekken used lambda_fd = 5 for Rload = -200
lambda_fd = 8;          % Rload = -200/1.7 Van = 200V 1.7A at 0.7m/s
%lambda_fd = 17;        % Rload = -200/1.7 but Van = 90V at 0.15m/s
Lsinglephase = 0.190;
Ls = 3/2*Lsinglephase;
theta_d_0 =0;
lambda_sq_0=0;
lambda_sd_0 =0;

sim('DirectDrivePTO')
%saveas(get_param('nak_TB/DirectDrive','Handle'),'directdriveSimulink.eps','psc2')

%% Average Power

%start = 2000001;       % between 200 and 300 seconds for fixed step ode4

start = 118181;         % between 200 and 300 seconds for variable step ode45
avgPabs = trapz(Pabs.time(start:end),Pabs.signals.values(start:end)/1e3)/Pabs.time(end-(start-1));
avgPelec = trapz(Pelec.time(start:end),Pelec.signals.values(start:end)/1e3)/Pelec.time(end-(start-1));

eff = avgPelec/avgPabs;
fprintf('Average Absorbed Power is %0.2f kW\n',avgPabs)
fprintf('Average Electrical Power is %0.2f kW\n',avgPelec)
fprintf('Efficiency is %0.2f \n',eff)

%% Normalized Power

maxPabs = max(Pabs.signals.values(start:end));
normPabs = Pabs.signals.values(start:end)/maxPabs;
normPelec = Pelec.signals.values(start:end)/maxPabs;


%% Plots

set(0,'DefaultFigureWindowStyle','docked')

f = figure;
plot(zDot.time,zDot.signals.values)
set(findall(gcf,'type','axes'),'fontsize',8)
xlabel('Time (s)')
ylabel('Velocity (m/s)')
title('Buoy Velocity')
axis([ 200 300 -2 2])
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','DDzDot.eps') 

f = figure;
plot(zDot.time,zDot.signals.values)
set(findall(gcf,'type','axes'),'fontsize',8)
xlabel('Time (s)')
ylabel('Velocity (m/s)')
title('Buoy Velocity (Zoom In)')
axis([ 281 286 -2 2])
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','DDzDotZoomIn.eps') 

f = figure;
subplot(211)
plot(Va.time,Va.signals.values)
set(findall(gcf,'type','axes'),'fontsize',8)
xlabel('Time (s)')
ylabel('Voltage (V)')
title('A Phase Line to Neutral Load Voltage')
axis([ 281 286 -400 400])
subplot(212)
plot(Vabc.time,Vabc.signals.values)
set(findall(gcf,'type','axes'),'fontsize',8)
xlabel('Time (s)')
ylabel('Voltage (V)')
title('3-Phase Line to Neutral Load Voltage (Zoom In)')
legend('V_a','V_b','V_c')
axis([ 281 286 -400 400])
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','DDVabc.eps') 

f = figure;
subplot(211)
plot(Ia.time,Ia.signals.values)
set(findall(gcf,'type','axes'),'fontsize',8)
xlabel('Time (s)')
ylabel('Current (A)')
title('A Phase Line Current')
axis([ 281 286 -4 4])
subplot(212)
plot(Iabc.time,Iabc.signals.values)
set(findall(gcf,'type','axes'),'fontsize',8)
xlabel('Time (sec)')
ylabel('Current (A)')
title('3-Phase Line Current (Zoom In)')
legend('I_a','I_b','I_c')
axis([ 281 286 -4 4])
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','DDIabcZoom.eps') 

f = figure;
plot(Fpto.time,Fpto.signals.values/1e3)
set(findall(gcf,'type','axes'),'fontsize',8)
xlabel('Time (s)')
ylabel('Force (kN)')
title('PTO Force')
axis([ 200 300 -1.5 2])
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','DDFpto.eps') 

f = figure;
plot(Pabs.time,Pabs.signals.values/1e3,'b',Pelec.time,Pelec.signals.values/1e3,'r')
xlabel('Time (s)')
ylabel('Power (kW)')
title('Absorbed and Electrical Power')
legend('P_{abs}','P_{elec}')
axis([ 200 300 0 3.5])
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','DDPabsPelec.eps') 

f = figure;
plot(Pabs.time(start:end),normPabs,'b',Pelec.time(start:end),normPelec,'r')
set(findall(gcf,'type','axes'),'fontsize',8)
xlabel('Time (s)')
ylabel('Normalized Power')
title('Normalized Absorbed and Electrical Power')
legend('Pnorm_{abs}','Pnorm_{elec}')
axis([ 200 300 0 1])
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','normDDPabsPelec.eps') 

