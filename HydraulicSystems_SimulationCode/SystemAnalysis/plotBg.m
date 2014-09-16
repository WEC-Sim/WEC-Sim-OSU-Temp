%% Non-Linear Hydraulic PTO - GMREC Conference
% Sean Casey
% 2/10/13
% GRA - OSU
%
%   ODE calls are programmatic - NO simulink
%
% Notes:

%% Initialize Workspace
clear; clc; %close all
set(0,'DefaultFigureWindowStyle','normal')
funPath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\PressureRiseRate_PassiveHydraulicSystem\SimulationDataFiles\';
addpath(funPath);
addpath(savePath);

%%
% Specify plot colors 
col = [255   0       0; 
       83     0     156; 
       0    118     255;
       252  174     0;
       15   188     0]/256;   
   


for i = 1:8
    
    load(['PassiveSystem_wave_irr_Hs4_Te12_testbg_' num2str(i)]);
    
    bg(i) = out.pto.bg;
    P_genMean(i) = out.simData.P_genMean;
    P_hydMean(i) = out.simData.P_hydMean;
    
    
end

eff = P_genMean./P_hydMean; 

% figure 
% [AX,H1,H2] = plotyy([bg; bg]', [P_genMean*1e-3; P_hydMean*1e-3]', bg, eff)
% set(H1, 'linewidth', 2)
% set(H2, 'linewidth', 2, 'linestyle', '--')
% hl = legend([H1' H2], 'Generator Power', 'Hydraulic Power','Efficiency', 'location', 'best')
% % legend(H2, 'Efficiency')
% hy(1) = ylabel(AX(1), 'Power [kW]')
% hy(2) = ylabel(AX(2), 'Efficiency')
% hx = xlabel(AX(1), 'Generator Damping')
% grid on
% ht = title('Generator Damping Sweep')
% set(AX(2), 'XTickLabel', {}, 'XTick', [])
% 
% set(AX(2), ...
%   'Box'         , 'off'     , ...
%   'TickDir'     , 'out'     , ...
%   'TickLength'  , [.02 .02] , ...
%   'XMinorTick'  , 'on'      , ...
%   'YMinorTick'  , 'on'      , ...
%   'LineWidth'   , 2.25       );
% 
% prettyPlot(hx,hy,ht,hl); 
% set(gcf, 'Outerposition', [-1220 331  729  713])
% 



figure   
subplot(2,1,1)
plot(bg, P_genMean*1e-3, 'linewidth', 2, 'color', col(3,:)); hold on
plot(bg, P_hydMean*1e-3, 'linewidth', 2, 'color', col(5,:));
hx = xlabel('Generator Damping')
hy = ylabel('Mean Power [kW]')
ht = title('Generator Damping Sweep')
hl = legend('Generator Power', 'Hydraulic Power', 'location', 'best')
ylim([50 100])
grid on 
prettyPlot(hx,hy,ht,hl); 
delete(hx)

subplot(2,1,2)
plot(bg, eff,  'linewidth', 2, 'color', col(1,:));
hx = xlabel('Generator Damping')
hy = ylabel('Efficiency')
ylim([0.6, 0.8])
% ht = title('Generator Damping Sweep')
% hl = legend('Generator Power', 'Hydraulic Power', 'location', 'southeast')
grid on 
prettyPlot(hx,hy,ht,hl); 
set(gcf, 'Outerposition', [-1220 331  729  713])