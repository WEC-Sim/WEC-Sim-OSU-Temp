%% Non-Linear Hydraulic PTO - GMREC Conference
% Sean Casey
% 2/10/13
% GRA - OSU
%
%   ODE calls are programmatic - NO simulink
%
% Notes:

%% Initialize Workspace
clear; clc; close all
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
   


coldist = distinguishable_colors(20); 
legStr = {}; 
for i = 1:6
    
    load(['PassiveSystem_wave_irr_Hs4_Te12_testalpha_' num2str(i)]);
    
    ti = 300;
    tf = out.simData.time(end); 
    [t, tind] = getTwindow(out.simData.time, ti, tf);
    time{:,i} = t;
    
    alpha(i) = out.pto.alpha;
    P_genMean(i) = out.simData.P_genMean;
    P_hydMean(i) = out.simData.P_hydMean;
    
    P_gen{:,i} = out.simData.P_gen(tind)*1e-3;
    pA{:,i} = out.simData.pA(tind)*1e-6;

    
    legStr{end+1} =  num2str(alpha(i));
    
    
end

figure
for i = 1:6
   p1(i) = plot(time{:,i}, P_gen{:,i}, 'linewidth', 2, 'color', coldist(i,:)); hold on 
end
hl = legend(p1, legStr );
xlim([time{:,i}(1), time{:,i}(end)]);
hx = xlabel('Time [s]');
hy = ylabel('Power [kW]');
ht = title('Generator Power with Varying Motor Displacement');
prettyPlot(hx, hy, ht, hl)
set(gcf, 'Outerposition', [-1220 331  729  713])

figure
for i = 1:6
    p2(i) = plot(time{:,i}, pA{:,i}, 'linewidth', 2, 'color', coldist(i,:)); hold on
end
hl = legend(p2, legStr );
xlim([time{:,i}(1), time{:,i}(end)]);
hx = xlabel('Time [s]');
hy = ylabel('Pressure [MPa]');
ht = title('Generator Power with Varying Motor Displacement');
prettyPlot(hx, hy, ht, hl)
set(gcf, 'Outerposition', [-1220 331  729  713])