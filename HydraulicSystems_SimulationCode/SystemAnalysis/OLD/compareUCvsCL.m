%% Hydraulic PTO - GMREC Conference
% Sean Casey
% 3/19/13
% GRA - OSU
%
%   Compare each controlled and uncontrolled active system
%
% Notes:

%% Initialize Workspace
clear; clc; close all
set(0,'DefaultFigureWindowStyle','docked')
funPath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\Functions\';
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\AnalysisFiles\';
savePathPaper = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\GMREC_Paper\GMREC_Paper\template\mets_latex.tar\mets-latex\FiguresTables\';
addpath(funPath);
addpath(savePath);

%% Load Data
pathActive  = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\ActiveHydraulicSystem\';

nameActiveUC  = 'ActiveSystem_wave_irr_Hs3_Ts10_uncontrolled_4x2'; 
outActiveUC   = load([pathActive  nameActiveUC]); 

nameActiveCL  = 'ActiveSystem_wave_irr_Hs3_Ts10_controlled_4x2'; 
outActiveCL   = load([pathActive  nameActiveCL]); 

simDataUC = outActiveUC.out.simData; 
simDataCL = outActiveCL.out.simData; 

%%

col = [255    0       0; 
       83     0     156; 
       0    118     255;
       252  174       0;
       15   188       0]/256;         % Plot Colors 

saveName = 'irr.eps'; 

ti =  160;   % Start time to plot
tf   = 200; % End time to plot 

[timeUC, tindUC] = getTwindow(simDataUC.time, ti, tf); 
[timeCL, tindCL] = getTwindow(simDataCL.time, ti, tf); 

figure
ax1 = subplot(2,1,1); 
plotDynamics(timeUC, simDataUC, tindUC, col); 
hx = xlabel('Time [s]');
hy = ylabel('[m] -- [m/s]');
% hl = legend('$\eta$', '$z$', '$\dot{z}$', '$\dot{z}_{opt}$');
ht = title('Kinematics -- Uncontrolled');
xlim([ti, tf])
ylim([-2.5, 2.5])
grid on 
hl = legend('dummy');
prettyPlot(hx,hy,ht,hl); 
delete(hl)
% set(hl,'interpreter','latex'... 
%     ,'fontsize', 20)

ax2 = subplot(2,1,2);
plotDynamics(timeCL, simDataCL, tindCL, col); 
hx = xlabel('Time [s]');
hy = ylabel('[m] -- [m/s]');
hl = legend('$\eta$', '$z$', '$\dot{z}$', '$\dot{z}_{opt}$');
ht = title('Kinematics -- Tracking Control');
xlim([ti, tf])
ylim([-2.5, 2.5])
grid on 
prettyPlot(hx,hy,ht,hl); 
set(hl,'interpreter','latex' ... 
      ,'fontsize', 20 ...
      ,'orientation', 'horizontal'...
      ,'location', 'southoutside')

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
% set(N(2), 'position', pos{2,1}(1,:)-[0,0.1,0])
% set(N(3), 'position', pos{3,1}(1,:)-[0,0.1,0])
% set(N(4), 'position', pos{4,1}(1,:)-[0,0.1,0])
saveas(gcf, [savePathPaper 'DynamicsUCvsCL_' saveName], 'epsc')
