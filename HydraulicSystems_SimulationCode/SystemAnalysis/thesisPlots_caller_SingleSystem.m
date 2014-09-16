%% Hydraulic PTO - GMREC Conference
% Sean Casey
% 3/19/13
% GRA - OSU
%
%   Compare each system - analyze loadings for GMREC paper
%
% Notes:

%% Initialize Workspace
clear;
clc; close all
set(0,'DefaultFigureWindowStyle','normal')
funPath1         = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
funPath2         = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\Functions\';
analysisPath    = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\AnalysisFiles\';
savePath        = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\Figures\';
savePathPaper   = 'C:\Users\Sean\Desktop\WaveEnergyResearch\Thesis\Template\beavtex\FiguresTables\';
addpath(funPath1, funPath2, savePath, analysisPath);

%% Plotting Parameters

% Specify plot colors
col = [255   0       0;
    83     0     156;
    0    118     255;
    252  174     0;
    15   188     0]/256;

load('cmap');

%% Load Data
nameSys   = {'PassiveSystem', 'ActiveSystem'};                          % row
nameWave  = {'wave_reg_Hs3_Te10_10min', 'wave_irr_Hs3_Te10_40min'};     % column
nameParam = {'alpha_3', 'Ap_1'};

for i = 1:length(nameSys)
        
    for j = 1:length(nameWave)
        if j == 2 && i == 1
            c = 1; 
        else c = 2; 
        end
            
        nameFile  = [nameSys{i} '_' nameWave{j} '_' nameParam{c}];
        sys(i, j) = load([analysisPath  nameFile]);
    end
end

clc
% %% PTO FORCE Rainflow
% % Plot Properties
% p.titleStr = {'Piston Force Amplitude','Piston Force Amplitude'};
% p.sysStr   = {'Passive System', 'Active System'}; 
% p.nameSys  = nameSys;
% p.ylimit  = [0,0.5];
% p.sigScale = 1e-3;
% p.nameSig   = {'Fpto', 'Fpto'}; 
% p.xlab    = {'Force [kN]'};
% p.xUpLim  = 1200;
% 
% stats.pto = plot_hist1(nameSys, sys, p)
% 
% saveas(gcf, [savePathPaper 'PistonLoadingFull.eps'], 'epsc')
% 
% %% Generator FORCE Rainflow
% % Plot Properties
% p.titleStr = {'Generator Torque Amplitude','Generator Torque Amplitude'};
% p.sysStr   = {'Passive System', 'Active System'}; 
% p.nameSys  = nameSys;
% p.ylimit  = [0,0.8];
% p.sigScale = 1;
% p.nameSig   = {'T_gen', 'T_gen'}; 
% p.xlab    = {'Torque [N-m]'};           
% p.xUpLim  = 800;    
% 
% stats.gen = plot_hist1(nameSys, sys, p)
% 
% saveas(gcf, [savePathPaper 'GeneratorLoadingFull.eps'], 'epsc')
%% 
waveSrc  = 'reg';       % 'reg' == regular waves; 'irr' == irregular waves
saveName = [waveSrc '.eps']; 

switch waveSrc
    case 'reg' 
        waveType = 1;
    case 'irr'
        waveType = 2; 
end

ti =  400;                              % Start time to plot
tf   = 500;                             % End time to plot 

timeTempP = sys(1,waveType).out.simData.time; 
timeTempA = sys(2,waveType).out.simData.time; 

[timeA, tindA] = getTwindow(timeTempA, ti, tf); 
[timeP, tindP] = getTwindow(timeTempP, ti, tf); 

%% Dynamics 
simDataP = sys(1,waveType).out.simData;
simDataA = sys(2,waveType).out.simData; 

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
set(hl, 'fontsize', 22)

N = findobj(hl, 'type','text');
pos = get(N,'position');
set(N(1), 'position', pos{1,1}(1,:)-[0,0.1,0])

set(gcf, 'Outerposition', [-1220 331  729  713])
% p1 = get(gca,'Position');

saveas(gcf, [savePathPaper 'Dynamics_' saveName], 'epsc')

%% Forcing 
figure
ax1 = subplot(2,1,1);
plotForcing(timeP, simDataP, tindP, col);
hx = xlabel('Time [s]');
hy = ylabel('[MN]');
hl = legend('F_e', 'F_{pto}');
ht = title('Forcing -- Passive System');
xlim([ti, tf])
% ylim([-0.65, 0.65])
grid on 
prettyPlot(hx,hy,ht,hl); 
delete(hl)

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

set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'Forcing_' saveName], 'epsc')

%% Forcing Velocity
figure
ax1 = subplot(2,1,1);
[ax, h1, h2] = plotyy(timeP, simDataP.Fe(tindP)*1e-6, timeP, simDataP.zDot(tindP));
set(h1, 'linewidth', 2, 'color', col(3,:));
set(h2, 'linewidth', 2, 'color', col(5,:), 'linestyle', '--');
hx = xlabel('Time [s]');
hy = ylabel(ax(1), 'Force [MN]');
hy2 = ylabel(ax(2), 'Velocity [m/s]');
% hl = legend('Excitation Force', 'Velocity');
ht = title('Forcing -- Passive System');
set(ax(2), 'xticklabel')
set(ax, 'xlim', ([ti, tf]))
set(ax(2),'ylim', ([-2,2]),...
          'ytick', (-2:1:2))
grid on 
set(ax                      , ...
    'FontName'   , 'Helvetica' );
set([hx, hy,hy2, ht], ...
    'FontName'   , 'AvantGarde');


set([hl, ax]             , ...
    'FontSize'   , 11           );

set([hx, hy,hy2,  ht]  , ...
    'FontSize'   , 14          );
set( ht                    , ...
    'FontSize'   , 16          , ...
    'FontWeight' , 'bold'      );
set(ax, ...
  'Box'         , 'off'     , ...
  'TickDir'     , 'out'     , ...
  'TickLength'  , [.02 .02] , ...
  'XMinorTick'  , 'on'      , ...
  'YMinorTick'  , 'on'      , ...
  'XColor'      , [.3 .3 .3], ...
  'YColor'      , [.3 .3 .3], ...
  'LineWidth'   , 2         );

ax2 = subplot(2,1,2);
[ax, h1, h2] = plotyy(timeA, simDataA.Fe(tindA)*1e-6, timeA, simDataA.zDot(tindA));
set(h1, 'linewidth', 2, 'color', col(3,:));
set(h2, 'linewidth', 2, 'color', col(5,:), 'linestyle', '--');
hx = xlabel('Time [s]');
hy = ylabel(ax(1), 'Force [MN]');
hy2 = ylabel(ax(2), 'Velocity [m/s]');
hl = legend('Excitation Force', 'Velocity');
ht = title('Forcing -- Active System');
set(ax(2), 'xticklabel', '')
set(ax, 'xlim', ([ti, tf]))
set(ax(2),'ylim', ([-2,2]),...
          'ytick', (-2:1:2))
grid on 
set( ax                       , ...
    'FontName'   , 'Helvetica' );
set([hx, hy,hy2 ht], ...
    'FontName'   , 'AvantGarde');


set([hl, ax]             , ...
    'FontSize'   , 11           );

set([hx, hy,hy2  ht]  , ...
    'FontSize'   , 14          );
set( ht                    , ...
    'FontSize'   , 16          , ...
    'FontWeight' , 'bold'      );
set(ax, ...
  'Box'         , 'off'     , ...
  'TickDir'     , 'out'     , ...
  'TickLength'  , [.02 .02] , ...
  'XMinorTick'  , 'on'      , ...
  'YMinorTick'  , 'on'      , ...
  'XColor'      , [.3 .3 .3], ...
  'YColor'      , [.3 .3 .3], ...
  'LineWidth'   , 2         );
set(hl,'orientation', 'horizontal'...
      ,'location', 'southoutside')


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

set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'ForcingVelocity_' saveName], 'epsc')
%%  Torque  
figure 
T_genP = simDataP.T_gen(tindP); 
plot(timeP, T_genP, 'color', col(3,:), 'linewidth', 2, 'linestyle', '--'); hold on

T_genA = simDataA.T_gen(tindA); 
plot(timeA, T_genA, 'color', col(5,:), 'linewidth', 2); hold on
% plotTorque(timeP, simDataP, tindP, col(3,:)); hold on 
% plotTorque(timeA, simDataA, tindA, col(5,:)); 
hx = xlabel('Time [s]');
hy = ylabel('[N-m]');
ht = title('Generator Torque');
xlim([ti, tf])
% ylim([-1.75, 1.75])
grid on 
prettyPlot(hx,hy,ht,hl); 
legend('Passive System', 'Active System')

% subplot(2,1,1) 
% plotTorque(timeP, simDataP, tindP, col); 
% hx = xlabel('Time [s]');
% hy = ylabel('[N-m]');
% ht = title('Generator Torque -- Passive System');
% xlim([ti, tf])
% % ylim([-1.75, 1.75])
% grid on 
% prettyPlot(hx,hy,ht,hl); 
% 
% subplot(2,1,2) 
% plotTorque(timeA, simDataA, tindA, col); 
% hx = xlabel('Time [s]');
% hy = ylabel('[N-m]');
% ht = title('Generator Torque -- Active System');
% xlim([ti, tf])
% % ylim([-1.75, 1.75])
% grid on 
% prettyPlot(hx,hy,ht,hl); 
set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'Torque2sys_' saveName], 'epsc')

%%  Piston force
figure 
FptoP = simDataP.Fpto(tindP); 
plot(timeP, FptoP*1e-3, 'color', col(3,:), 'linewidth', 2, 'linestyle', '--'); hold on

FptoA = simDataA.Fpto(tindA); 
plot(timeA, FptoA*1e-3, 'color', col(5,:), 'linewidth', 2); hold on
% 
% plotTorque(timeP, simDataP, tindP, col(3,:)); hold on 
% plotTorque(timeA, simDataA, tindA, col(5,:)); 
hx = xlabel('Time [s]');
hy = ylabel('[kN]');
ht = title('Piston Force');
xlim([ti, tf])
% ylim([-1.75, 1.75])
grid on 
prettyPlot(hx,hy,ht,hl); 
legend('Passive System', 'Active System')

set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'Force2sys_' saveName], 'epsc')

%% Control Input
figure 
subplot(2,1,2) 
plot(timeA, simDataA.alpha(tindA), 'color', col(3,:), 'linewidth', 2)
hx = xlabel('Time [s]');
hy = ylabel('$\alpha$', 'interpreter', 'latex');
ht = title('Swashplate Angle Ratio -- Active System');
xlim([ti, tf])
% ylim([-1.05, 1.05])
grid on 
prettyPlot(hx,hy,ht,hl); 

subplot(2,1,1)
plot(timeA, simDataA.bg(tindA), 'color', col(5,:), 'linewidth', 2)
hx = xlabel('Time [s]');
hy = ylabel('[kg m^2/s]');
ht = title('Generator Damping -- Active System');
xlim([ti, tf])
% ylim([-1.05, 1.05])
grid on 
prettyPlot(hx,hy,ht,hl); 

set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'Control_' saveName], 'epsc')

%% Pressure 
figure
plot(timeP, simDataP.pA(tindP)*1e-6, 'color', col(3,:), 'linewidth',2); hold on 
plot(timeP, simDataP.pB(tindP)*1e-6, 'color', col(5,:), 'linewidth',2)
plot(timeP, simDataP.pC(tindP)*1e-6, 'color', col(1,:), 'linewidth',2); hold on
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

set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'Pressure_' saveName], 'epsc')

%% Passive System 
figure
plotForcing(timeP, simDataP, tindP, col)
hx = xlabel('Time [s]');
hy = ylabel('[MN]');
hl = legend('F_e', 'F_{pto}');
ht = title('Forcing -- Passive System');
xlim([ti, tf])
% ylim([-0.65, 0.65])
grid on 
prettyPlot(hx,hy,ht,hl); 

p1 = get(gca,'Position'); 
set(gca,'Position',[p1(1) p1(2)+0.02 p1(3) p1(4)-0.04])
pl = get(hl, 'Position');
set(hl, 'Position', [pl(1), pl(2)-0.1, pl(3), pl(4)]) 
set(hl, 'fontsize', 14)

set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'PassiveSys_' saveName], 'epsc')

%% Power 
figure
plot(timeP, simDataP.P_gen(tindP)*1e-3, 'color', col(3,:), 'linewidth',2); hold on
plot(timeA, simDataA.P_gen(tindA)*1e-3, 'color', col(5,:), 'linewidth',2);
hx = xlabel('Time [s]');
hy = ylabel('[kW]');
hl = legend('Passive System', 'Active System');
ht = title('Power Output');
xlim([ti, tf])
% ylim([0, 800])
grid on 
prettyPlot(hx,hy,ht,hl); 


% subplot(2,1,1)
% plot(timeP, simDataP.P_gen(tindP)*1e-3, 'color', col(3,:), 'linewidth',2); 
% hx = xlabel('Time [s]');
% hy = ylabel('[kW]');
% ht = title('Power Output -- Passive System');
% xlim([ti, tf])
% ylim([0, 350])
% grid on 
% prettyPlot(hx,hy,ht,hl); 
% 
% subplot(2,1,2)
% plot(timeA, simDataA.P_gen(tindA)*1e-3, 'color', col(3,:), 'linewidth',2); 
% hx = xlabel('Time [s]');
% hy = ylabel('[kW]');
% ht = title('Power Output -- Active System');
% xlim([ti, tf])
% ylim([0, 350])
% grid on 
% prettyPlot(hx,hy,ht,hl); 
set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'Power_' saveName], 'epsc')

%% Distance -- Piston
% distP = abs(simDataPas.irr.z);
% distA = abs(simDataAct.irr.z); 
% 
% cumDistP = cumsum(abs(simDataPas.irr.z));
% cumDistA = cumsum(abs(simDataAct.irr.z));
% 
% figure
% plot(simDataPas.irr.time, cumDistP*1e-3, 'color', col(3,:), 'linewidth', 2); hold on
% plot(simDataAct.irr.time, cumDistA*1e-3, 'color', col(5,:), 'linewidth', 2); 
% hx = xlabel('Time [s]');
% hy = ylabel('[km]');
% ht = title('Travel Distance -- Piston');
% hl = legend('Passive System', 'Active System', 'location', 'northwest');
% xlim([simDataAct.irr.time(1), simDataAct.irr.time(end)])
% grid on 
% prettyPlot(hx,hy,ht,hl); 
% 
% set(gcf, 'Outerposition', [-1220 331  729  713])

%% Wave 
tspan = [100, 300];
figure
subplot(2,1,1)
plot(sys(1,1).out.simData.time, sys(1,1).out.simData.eta(:,2), 'color', 'k', 'linewidth', 2); 
ylim([-2.5,2.5])
xlim(tspan)
hx = xlabel('Time [s]');
hy = ylabel('[m]');
ht = title('Regular Waves');
hl = legend('dummy');
grid on 
prettyPlot(hx,hy,ht,hl)
delete(hl)

subplot(2,1,2)
plot(sys(1,2).out.simData.time, sys(1,2).out.simData.eta(:,2), 'color', 'k', 'linewidth', 2)
ylim([-2.5,2.5])
xlim(tspan)
hx = xlabel('Time [s]');
hy = ylabel('[m]');
ht = title('Irregular Waves');
hl = legend('dummy');
grid on 
prettyPlot(hx,hy,ht,hl)
delete(hl)

set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'WaveElevation.eps'], 'epsc')

%% Spectrum 
figure
plot(sys(1,2).out.wave.spectrum.f, sys(1,2).out.wave.spectrum.s, 'color', 'k', 'linewidth', 2); 
% ylim([-2.5,2.5])
% xlim([100, 300])
hx = xlabel('Frequency [Hz]');
hy = ylabel('Spectral Density [m^2-s]');
ht = title('Bretschneider-Mitsuyasu Spectrum');
hl = legend('dummy');
grid on 
prettyPlot(hx,hy,ht,hl)
delete(hl)

set(gcf, 'Outerposition', [-1220 331  729  713])

saveas(gcf, [savePathPaper 'Spectrum.eps'], 'epsc')

%% Damage 
% Damage Curve
% Ap = [0.10:0.05:0.5]*outPassiveIrr.out.pto.Ap; 
% sigma_pto = simDataAct.irr.Fpto/Ap(1); 
% dam = calcDamage(sigma_pto, 120, 0);
% 
% figure
% semilogx([dam.x1 dam.x2], [dam.Sf dam.Se]*1e-6, 'color', 'k', 'linewidth', 2); hold on 
% semilogx([dam.x2 10^8], [dam.Se dam.Se]*1e-6, 'color', 'k', 'linewidth', 2)
% hx = xlabel('Number of Stress Cycles')
% hy = ylabel('Fatigue Strength [MPa]')
% hl = legend('dummy');
% ylim([0, dam.Sut]*1e-6)
% grid on
% ht = title('S-N Diagram for Piston Rod - 316 Stainless Steel')
% prettyPlot(hx,hy,ht,hl)
% delete(hl)
% 
% set(gcf, 'Outerposition', [-1220 331  729  713])
% 
% saveas(gcf, [savePathPaper 'DamageCurve.eps'], 'epsc')

% % Fatigue Damage
% for i = 1:length(Ap)
% sigmaAct_pto(i,:) = simDataAct.irr.Fpto/Ap(i); 
% sigmaPas_pto(i,:) = simDataPas.irr.Fpto/Ap(i); 
% 
% damActirr(i).dam = calcDamage(sigmaAct_pto(i,:), 120, 1); 
% damPasirr(i).dam = calcDamage(sigmaPas_pto(i,:), 120, 1); 
% end
% 
% %%
% figure
% c=0;
% for i = 5:length(damActirr)
%     c=c+1;
%     plot(simDataAct.irr.time(damActirr(i).dam.cumInd), damActirr(i).dam.cumDam, 'color', col(c,:), 'linewidth', 2); hold on
%     
% end
% 

%% Statistics 

% % Regular 
% epsAreg =  simDataAct.reg.P_hydMean./simDataAct.reg.P_genMean;
% epsPreg =  simDataPas.reg.P_hydMean./simDataPas.reg.P_genMean;
% % Irregular
% epsAirr = simDataAct.irr.P_hydMean./simDataAct.irr.P_genMean;  
% epsPirr = simDataPas.irr.P_hydMean./simDataPas.irr.P_genMean;
% 
% fprintf('\nEff. Reg. Passive:     %3.2f\n', epsPreg)
% fprintf('Eff. Irr. Passive:     %3.2f\n', epsPirr)
% 
% fprintf('\nEff. Reg. Active:     %3.2f\n', epsAreg)
% fprintf('Eff. Irr. Active:     %3.2f\n', epsAirr)



%% Close out
% rmpath(funPath)
% rmpath(savePath)




