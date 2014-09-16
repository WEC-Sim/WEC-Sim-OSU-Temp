%% Hydraulic PTO - GMREC Conference
% Sean Casey
% 3/19/13
% GRA - OSU
%
%   Compare each system - analyze loadings for GMREC paper
%
% Notes:

%% Initialize Workspace
clear; clc; close all
set(0,'DefaultFigureWindowStyle','docked')
funPath1 = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\Functions\';
funPath2 = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\AnalysisFiles\';
savePathPaper = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\GMREC_Paper\GMREC_Paper\template\mets_latex.tar\mets-latex\FiguresTables\';
addpath(funPath1);
addpath(funPath2);
addpath(savePath);

%% Load Data
pathActive  = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\ActiveHydraulicSystem\';
pathPassive = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\PressureRiseRate_PassiveHydraulicSystem\';

nameActiveReg  = 'ActiveSystem_wave_reg_Hs3_Ts10_500_4x2'; 
outActiveReg   = load([pathActive  nameActiveReg]); 

namePassiveReg = 'PassiveSystem_wave_reg_Hs3_Ts10_500_4x2'; 
outPassiveReg  = load([pathPassive namePassiveReg]); 

nameActiveIrr  = 'ActiveSystem_wave_irr_Hs3_Ts10_1800_4x2'; 
outActiveIrr   = load([pathActive  nameActiveIrr]); 

namePassiveIrr = 'PassiveSystem_wave_irr_Hs3_Ts10_1800_4x2'; 
outPassiveIrr  = load([pathPassive namePassiveIrr]); 
clc
%% Begin Analysis

% Data
simDataAct.reg = outActiveReg.out.simData; 
simDataAct.irr = outActiveIrr.out.simData; 
simDataPas.reg = outPassiveReg.out.simData;
simDataPas.irr = outPassiveIrr.out.simData;

% Time 
tiReg = 200;                            % Regular 
tfReg = simDataAct.reg.time(end);
tiIrr = 200;                            % Irregular
tfIrr = simDataAct.irr.time(end); 

% Active 
fActReg = getLoad(simDataAct.reg, tiReg, tfReg);
fActIrr = getLoad(simDataAct.irr, tiIrr, tfIrr);

% Passive
fPasReg = getLoad(simDataPas.reg, tiReg, tfReg);
fPasIrr = getLoad(simDataPas.irr, tiIrr, tfIrr);


%% PTO FORCE Rainflow  
nBins = linspace(0,3.0,120);

[nAct, xAct, rfAct] = doRainflow(fActIrr.F, fActIrr.F_avg, nBins);
[nPas, xPas, rfPas] = doRainflow(fPasIrr.F, fPasIrr.F_avg, nBins);

% nAct = nAct*48; %sum(nAct); 
% nPas = nPas*48; %sum(nPas);

figure
subplot(2,1,2)
bar(xAct, nAct, 'r','Barwidth', 1)
hy = ylabel('# Cycles');
hx = xlabel('$$\frac{F_{irr}}{\overline{F}_{reg}}$$', 'interpreter', 'latex','fontsize', 14);
ht = title('Piston Loading Distribution -- Active System');
hl = legend('dummy'); 
ylim([0,20])
% ylim([0,0.1])
xlim([0, 3.0])
grid on
prettyPlot(hx,hy,ht,hl);
delete(hl);

subplot(2,1,1) 
bar(xPas, nPas, 'r', 'Barwidth', 1); %hold on 
hy = ylabel('# Cycles');
hx = xlabel('$$\frac{F_{irr}}{\overline{F}_{reg}}$$', 'interpreter', 'latex','fontsize', 14);
ht = title('Piston Loading Distribution -- Passive System');
hl = legend('dummy');
ylim([0,50])
% % ylim([0,0.1])
xlim([0, 3.0])
grid on
prettyPlot(hx,hy,ht,hl);
delete(hl);

saveas(gcf, [savePathPaper 'PistonLoading.eps'], 'epsc')
%% TORQUE Rainflow 
nBins = linspace(0,2,120);

[nAct, xAct, rfAct] = doRainflow(fActIrr.T, fActIrr.T_avg, nBins);
[nPas, xPas, rfPas] = doRainflow(fPasIrr.T, fPasIrr.T_avg, nBins);
 
% nAct = nAct*48; %sum(nAct); 
% nPas = nPas*48; %sum(nPas);

figure
subplot(2,1,2)
bar(xAct, nAct, 'r','Barwidth', 1)
hy = ylabel('# Cycles');
hx = xlabel('$$\frac{T_{irr}}{\overline{T}_{reg}}$$', 'interpreter', 'latex','fontsize', 14);
ht = title('Generator Loading Distribution -- Active System');
hl = legend('dummy'); 
ylim([0,40])
xlim([0, 2])
grid on
prettyPlot(hx,hy,ht,hl);
delete(hl);

subplot(2,1,1) 
bar(xPas, nPas, 'r', 'Barwidth', 1); %hold on 
hy = ylabel('# Cycles');
hx = xlabel('$$\frac{T_{irr}}{\overline{T}_{reg}}$$', 'interpreter', 'latex','fontsize', 14);
ht = title('Generator Loading Distribution -- Passive System');
hl = legend('dummy');
ylim([0,15])
xlim([0, 2])
grid on
prettyPlot(hx,hy,ht,hl);
delete(hl);

saveas(gcf, [savePathPaper 'GeneratorLoading.eps'], 'epsc')

%% Get Data to Plot

col = [255   0       0; 
       83     0     156; 
       0    118     255;
       252  174     0;
       15   188     0]/256;         % Plot Colors 

saveName = 'irr.eps'; 
   
% Active System
simDataA    = outActiveIrr.out.simData;
timeTempA   = simDataA.time;                

% Passive System 
simDataP    = outPassiveIrr.out.simData;
timeTempP   = simDataP.time; 

ti =  400;   % Start time to plot
tf   = 460; % End time to plot 

[timeA, tindA] = getTwindow(timeTempA, ti, tf); 
[timeP, tindP] = getTwindow(timeTempP, ti, tf); 

%% show cycles extracted 
sigAct = simDataAct.irr.Fpto(tindA);
ext = sig2ext(sigAct); 

figure
subplot(2,1,1) 
plot(timeA, sigAct, 'color', col(3,:), 'linewidth', 2) 
% xlim([timeA(1), timeA(end)])

subplot(2,1,2)
rfdemo1(ext);
% xlim(


%% Dynamics 
figure
ax2 = subplot(2,1,2);
plotDynamics(timeA, simDataA, tindA, col); 
hx = xlabel('Time [s]');
hy = ylabel('[m] -- [m/s]');
hl = legend('$\eta$', '$z$', '$\dot{z}$', '$\dot{z}_{opt}$');
ht = title('Kinematics -- Active System');
xlim([ti, tf])
% ylim([-1.75, 1.75])
grid on 
prettyPlot(hx,hy,ht,hl); 
set(hl,'interpreter','latex' ... 
      ,'fontsize', 20 ...
      ,'orientation', 'horizontal'...
      ,'location', 'southoutside')

ax1 = subplot(2,1,1);
plotDynamics(timeP, simDataP, tindP, col); 
hx = xlabel('Time [s]');
hy = ylabel('[m] -- [m/s]');
% hl = legend('$\eta$', '$z$', '$\dot{z}$', '$\dot{z}_{opt}$');
ht = title('Kinematics -- Passive System');
xlim([ti, tf])
% ylim([-1.75, 1.75])
grid on 
prettyPlot(hx,hy,ht,hl); 

p1 = get(ax1,'Position'); 
p2 = get(ax2,'Position'); 
set(ax1,'Position',[p1(1) p1(2)+0.06 p1(3) p2(4)+0.04])
set(ax2,'Position',[p2(1) p2(2)-0.01 p1(3) p2(4)+0.04])
pl = get(hl, 'Position');
set(hl, 'Position', [pl(1), pl(2)-0.08, pl(3), pl(4)]) 
set(hl, 'fontsize', 20)

N = findobj(hl, 'type','text');
pos = get(N,'position');
set(N(1), 'position', pos{1,1}(1,:)-[0,0.1,0])

saveas(gcf, [savePathPaper 'Dynamics_' saveName], 'epsc')

%% Forcing 
figure
ax2 = subplot(2,1,2);
plotForcing(timeA, simDataA, tindA, col); 
hx = xlabel('Time [s]');
hy = ylabel('[MN]');
hl = legend('F_e', 'F_{pto}');
ht = title('Forcing -- Active System');
xlim([ti, tf])
% ylim([-0.65, 0.65])
grid on 
prettyPlot(hx,hy,ht,hl); 
set(hl,'orientation', 'horizontal'...
      ,'location', 'southoutside')

ax1 = subplot(2,1,1);
plotForcing(timeP, simDataP, tindP, col);
hx = xlabel('Time [s]');
hy = ylabel('[MN]');
% hl = legend('F_e', 'F_{pto}');
ht = title('Forcing -- Passive System');
xlim([ti, tf])
% ylim([-0.65, 0.65])
grid on 
prettyPlot(hx,hy,ht,hl); 

p1 = get(ax1,'Position'); 
p2 = get(ax2,'Position'); 
set(ax1,'Position',[p1(1) p1(2)+0.06 p1(3) p2(4)+0.04])
set(ax2,'Position',[p2(1) p2(2)-0.01 p1(3) p2(4)+0.04])
pl = get(hl, 'Position');
set(hl, 'Position', [pl(1), pl(2)-0.08, pl(3), pl(4)]) 
% set(hl, 'fontsize', 20)
N = findobj(hl, 'type','text');
pos = get(N,'position');
set(N(1), 'position', pos{1,1}(1,:)-[0,0.1,0])
set(hl, 'fontsize', 14)

saveas(gcf, [savePathPaper 'Forcing_' saveName], 'epsc')
%%  Torque  
figure 
subplot(2,1,2) 
plotTorque(timeA, simDataA, tindA, col); 
hx = xlabel('Time [s]');
hy = ylabel('[N-m]');
% hl = legend('F_e', 'F_{pto}');
ht = title('Generator Torque -- Active System');
xlim([ti, tf])
% ylim([-1.75, 1.75])
grid on 
prettyPlot(hx,hy,ht,hl); 
% set(hl,'interpreter','latex'... 
%     ,'fontsize', 20)

subplot(2,1,1) 
plotTorque(timeP, simDataP, tindP, col); 
hx = xlabel('Time [s]');
hy = ylabel('[N-m]');
% hl = legend('F_e', 'F_{pto}');
ht = title('Generator Torque -- Passive System');
xlim([ti, tf])
% ylim([-1.75, 1.75])
grid on 
prettyPlot(hx,hy,ht,hl); 
% set(hl,'interpreter','latex'... 
%     ,'fontsize', 20)
saveas(gcf, [savePathPaper 'Torque_' saveName], 'epsc')
%% Control Input
figure 
subplot(2,1,2) 
plot(timeA, simDataA.alpha(tindA), 'color', col(3,:), 'linewidth', 2)
hx = xlabel('Time [s]');
hy = ylabel('$\alpha$', 'interpreter', 'latex');
% hl = legend('F_e', 'F_{pto}');
ht = title('Swashplate Angle Ratio -- Active System');
xlim([ti, tf])
% ylim([-1.05, 1.05])
grid on 
prettyPlot(hx,hy,ht,hl); 

subplot(2,1,1)
plot(timeA, simDataA.bg(tindA), 'color', col(5,:), 'linewidth', 2)
hx = xlabel('Time [s]');
hy = ylabel('[kg m^2/s]');
% hl = legend('F_e', 'F_{pto}');
ht = title('Generator Damping -- Active System');
xlim([ti, tf])
% ylim([-1.05, 1.05])
grid on 
prettyPlot(hx,hy,ht,hl); 


saveas(gcf, [savePathPaper 'Control_' saveName], 'epsc')

%% Pressure 
figure
% subplot(2,1,1)
plot(timeP, simDataP.pA(tindP)*1e-6, 'color', col(3,:), 'linewidth',2); hold on 
plot(timeP, simDataP.pB(tindP)*1e-6, 'color', col(5,:), 'linewidth',2)
plot(timeP, simDataP.pC(tindP)*1e-6 , 'color', col(1,:), 'linewidth',2); hold on
plot(timeP, simDataP.pD(tindP)*1e-6, 'color', col(4,:), 'linewidth',2)
hx = xlabel('Time [s]');
hy = ylabel('[MPa]');
hl = legend('p_A', 'p_B','p_C', 'p_D' , 'orientation', 'horizontal', 'location', 'southoutside');
ht = title('System Pressure -- Passive System');
xlim([ti, tf])
ylim([10, 28])
grid on 
prettyPlot(hx,hy,ht,hl); 

p1 = get(gca,'Position'); 
set(gca,'Position',[p1(1) p1(2)+0.02 p1(3) p1(4)-0.04])
pl = get(hl, 'Position');
set(hl, 'Position', [pl(1), pl(2)-0.1, pl(3), pl(4)]) 
set(hl, 'fontsize', 14)


saveas(gcf, [savePathPaper 'Pressure_' saveName], 'epsc')
%% Power 

figure
subplot(2,1,1)
plot(timeP, simDataP.P_gen(tindP)*1e-3, 'color', col(3,:), 'linewidth',2); 
hx = xlabel('Time [s]');
hy = ylabel('[kW]');
ht = title('Power Output -- Passive System');
xlim([ti, tf])
% ylim([-1.05, 1.05])
grid on 
prettyPlot(hx,hy,ht,hl); 

subplot(2,1,2)
plot(timeA, simDataA.P_gen(tindA)*1e-3, 'color', col(3,:), 'linewidth',2); 
hx = xlabel('Time [s]');
hy = ylabel('[kW]');
ht = title('Power Output -- Active System');
xlim([ti, tf])
% ylim([-1.05, 1.05])
grid on 
prettyPlot(hx,hy,ht,hl); 

saveas(gcf, [savePathPaper 'Power_' saveName], 'epsc')
%% Wave

% figure 
% plot(timeA, simDataA.eta(tindA,2), 'color', col(3,:), 'linewidth',2)
% ylim([-2.3, 2.3])
% xlim([90, 230])

%% Distance -- Piston
distP = abs(simDataPas.irr.z);
distA = abs(simDataAct.irr.z); 

cumDistP = cumsum(abs(simDataPas.irr.z));
cumDistA = cumsum(abs(simDataAct.irr.z));

figure
plot(simDataPas.irr.time, cumDistP*1e-3, 'color', col(3,:), 'linewidth', 2); hold on
plot(simDataAct.irr.time, cumDistA*1e-3, 'color', col(5,:), 'linewidth', 2); 
hx = xlabel('Time [s]');
hy = ylabel('[km]');
ht = title('Travel Distance -- Piston');
hl = legend('Passive System', 'Active System', 'location', 'northwest');
xlim([simDataAct.irr.time(1), simDataAct.irr.time(end)])
grid on 
prettyPlot(hx,hy,ht,hl); 
% 
% %% Distance -- Motor
% % dispP = trapz(simDataPas.irr.omega);
% % dispA = trapz(simDataAct.irr.omega);
% % distP = sum(abs());
% % distA = sum(abs()); 
% 
% cumDistP = cumtrapz(simDataPas.irr.time, abs(simDataPas.irr.omega));
% cumDistA = cumtrapz(simDataAct.irr.time, abs(simDataAct.irr.omega));
% 
% figure
% plot(simDataPas.irr.time, cumDistP, 'color', col(3,:), 'linewidth', 2); hold on
% plot(simDataAct.irr.time, cumDistA, 'color', col(5,:), 'linewidth', 2); 
% hx = xlabel('Time [s]');
% hy = ylabel('[rad]');
% ht = title('Travel Distance -- Generator Shaft');
% hl = legend('Passive System', 'Active System', 'location', 'northwest');
% xlim([simDataAct.irr.time(1), simDataAct.irr.time(end)])
% grid on 
% prettyPlot(hx,hy,ht,hl); 

%% Statistics 

% Regular 
epsAreg =  simDataAct.reg.P_hydMean./simDataAct.reg.P_genMean;
epsPreg =  simDataPas.reg.P_hydMean./simDataPas.reg.P_genMean;
% Irregular
epsAirr = simDataAct.irr.P_hydMean./simDataAct.irr.P_genMean;  
epsPirr = simDataPas.irr.P_hydMean./simDataPas.irr.P_genMean;

fprintf('\nEff. Reg. Passive:     %3.2f\n', epsPreg)
fprintf('Eff. Irr. Passive:     %3.2f\n', epsPirr)

fprintf('\nEff. Reg. Active:     %3.2f\n', epsAreg)
fprintf('Eff. Irr. Active:     %3.2f\n', epsAirr)



%% Close out
% rmpath(funPath)
% rmpath(savePath)

