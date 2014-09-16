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
   
figure

coldist = distinguishable_colors(20); 
legStr = {}; 
for i = 1:9
    
    load(['PassiveSystem_wave_irr_Hs4_Te12_testvC0_' num2str(i+1)]);
    
    ti = 300;
    tf = out.simData.time(end); 
    [time, tind] = getTwindow(out.simData.time, ti, tf);
    
    vC0(i) = out.pto.vC0/2;
    P_genMean(i) = out.simData.P_genMean;
    P_hydMean(i) = out.simData.P_hydMean;
    
    P_gen{:,i} = out.simData.P_gen(tind)*1e-3;
    
    p(i) = plot(time, P_gen{:,i}, 'linewidth', 2, 'color', coldist(i,:)); hold on
    
    legStr{end+1} =  num2str(vC0(i));
    
    
end
hl = legend(p, legStr )
xlim([time(1), time(end)])
hx = xlabel('Time [s]')
hy = ylabel('Power [kW]')
ht = title('Generator Power with Varying Accumulator Volume Ratio')

prettyPlot(hx, hy, ht, hl)
set(gcf, 'Outerposition', [-1220 331  729  713])