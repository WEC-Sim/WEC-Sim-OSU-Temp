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

ksys = 2;
out = sys(ksys,2).out;  % system to animate 

switch ksys
    case 1
        strSys = 'Passive System';
    case 2 
        strSys = 'Active System' ;
end

%% Use dispersion relationship to show simulate sea state over a time interval

t0 = 400;              % start time
t_f = 440;           % end time
inc = 1/12; %0.05;          % time increment
ym = 2.5;
% 
L_max   = 75;% max(L);                   % longest wave
% L_min   = min(L);                         % shortest wave
% dx      = L_min/100;                       % spatial step size
% x       = 0 : dx : L_max;                       % spatial grid

dx = min(out.wave.zComp.L)/100; 
x = -L_max : dx : L_max; 

eta_comp = out.wave.zComp.z; 
sigma = out.wave.zComp.sigma;
phi = out.wave.zComp.phase; 
k = out.wave.zComp.k;
z = interp1(out.simData.time, out.simData.z, t0:inc:t_f); 


eta_x = zeros(1, length(x));
for i = 1:length(sigma)
    eta_x = eta_x + eta_comp(i)*cos(k(i)*x - sigma(i)*t0 - phi(i));     % calculate component wave heights with random phase given x and t
end

Hs = out.wave.Hs; 
Te = round(out.wave.Te);

ramWidth = 0.5;
ramHeight = 10;
pumpWidth = 3; 
pumpHeight = 5; 

max_eta = sum(eta_comp);    % find largest possible component
plotYN_spatial = 1; 
% plot sum of components
if plotYN_spatial
    figure
    p_x = plot(x, eta_x,'linewidth', 2); hold on
    
%                 p_rec6 = rectangle('Position', [0-pumpWidth/2, z(c)-ramHeight, pumpWidth, (pumpHeight/2-z(c))], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'b', 'facecolor', 'b');
%                 p_rec7 = rectangle('Position', [0-pumpWidth/2, z(c)-ramHeight-pumpHeight, pumpWidth, (z(c))], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'r', 'facecolor', 'r');
                
                p_rec2 = rectangle('Position', [0-ramWidth/2, z(c)-ramHeight, ramWidth, ramHeight], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'k', 'facecolor', 'k');  % ram
                p_rec3 = rectangle('Position', [0-pumpWidth/2, 0-pumpHeight/2-ramHeight, pumpWidth, pumpHeight], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'k'); %pump
                p_rec4 = rectangle('Position', [0-pumpWidth/2, z(c)-ramHeight-pumpHeight/8, pumpWidth, pumpHeight/8], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'k', 'facecolor', 'k');% pressurized area
                p_rec5 = rectangle('Position', [0-ramWidth/2, z(c)-ramHeight-pumpHeight, ramWidth, ramHeight], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'k', 'facecolor', 'k');
                

                p_rec1 = rectangle('Position', [0-4, z(c)-4, 8, 8], 'curvature', [0.1], 'linewidth', 2, 'edgecolor', col(4,:), 'facecolor', col(4,:)); % float
                p_z = plot(0, z(c), 'kx',0, z(c), 'ko');
                
                t1 = text(L_max*0.3, Hs*ym*0.9, sprintf(['Time:  %3.2f s'],t0), 'fontsize', 14);
    
    ax_x = gca;
    hx = xlabel('Position [m]');
    hy = ylabel('Wave Height [m]');
    ylimits = ([-pumpHeight/2-ramHeight,ym*Hs]);%([-1.1*max_eta, 1.1*max_eta]);
    xlimits = ([-L_max, L_max]);
    set(gca, 'ylim', ylimits, 'xlim', xlimits)
    ht = title([strSys '  Hs = 3, Te = 10']);
    hl = legend('dummy');
    prettyPlot(hx, hy, ht, hl); 
    delete(hl);
    
    
    set(gcf, 'Outerposition', [164    40   713   621])

    set(gcf, 'color','w')
% axis('equal')
end
% axis('equal')
%% PLOTTING
plotYN_animate = 1;

f = 1./out.wave.zComp.T;

% ANIMATE PLOT - SPATIO-TEMPORAL
n = 1;
eta2save(n,:) = eta_x;
t2save(n,:) = t0;
c = 0;
d = 15;
if plotYN_animate == 1
    
    while t0 < t_f
        c = c+1;
        t0 = t0+inc;                      % Increment time step
        eta_xt = zeros(1, length(x));
        for i = 1:length(f)
            eta_xt = eta_xt + eta_comp(i)*cos(k(i)*x - sigma(i)*t0 - phi(i));    % calculate new components
        end
        
%         if c == n*d
%             n = n+1;
%             eta2save(n,:) = eta_xt;
%             t2save(n,:) = t0;
%             
%         end
        
                delete(p_x, p_z, p_rec1, p_rec2, p_rec3, p_rec4, p_rec5, t1);                         % Delete previous curve
                p_x = plot(ax_x, x, eta_xt, 'linewidth', 2);       % Plot new curve
                
                p_rec2 = rectangle('Position', [0-ramWidth/2, z(c)-ramHeight, ramWidth, ramHeight], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'k', 'facecolor', 'k');  % ram
                p_rec3 = rectangle('Position', [0-pumpWidth/2, 0-pumpHeight/2-ramHeight, pumpWidth, pumpHeight], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'k'); %pump
                p_rec4 = rectangle('Position', [0-pumpWidth/2, z(c)-ramHeight-pumpHeight/8, pumpWidth, pumpHeight/8], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'k', 'facecolor', 'k');% pressurized area
                p_rec5 = rectangle('Position', [0-ramWidth/2, z(c)-ramHeight-pumpHeight, ramWidth, ramHeight], 'curvature', [0], 'linewidth', 2, 'edgecolor', 'k', 'facecolor', 'k');
                p_rec1 = rectangle('Position', [0-4, z(c)-4, 8, 8], 'curvature', [0.1], 'linewidth', 2, 'edgecolor', col(4,:), 'facecolor', col(4,:)); % float
                p_z = plot(0, z(c), 'kx',0, z(c), 'ko');
                t1 = text(L_max*0.3, Hs*ym*0.9, sprintf(['Time:  %3.2f s'],t0), 'fontsize', 14);
                
                ylimits = ([-ym*Hs,ym*Hs]);%([-1.1*max_eta, 1.1*max_eta]);
                xlimits = ([-L_max, L_max]);
                
%                 pause(inc)                      % Pause for time increase
        
                mov(c) = getframe(gcf);
    end
end

%%
% [h, w, p] = size(mov(1).cdata);
% hf = figure; 
% % resize figure based on frame's w x h, and place at (150, 150)
% set(hf,'Position', [150 150 w h]);
% axis off

% figure
% set(gcf, 'Outerposition', [164    40   713   621])
% movie(hf, mov, 1, 12,[0 0 0 0])
savePath = 'C:\Users\Sean\Desktop\WaveEnergyResearch\Thesis\Presentation\';
writeObj = VideoWriter([savePath nameSys{ksys}, '.avi']);
set(writeObj, 'FrameRate', 12, 'Quality', 100)
open(writeObj);
writeVideo(writeObj,mov(2:end));
close(writeObj); 
% winopen('movie1')