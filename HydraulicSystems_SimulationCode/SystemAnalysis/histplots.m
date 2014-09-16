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
p.col = col; 

load('cmap');

%% Load Data
nameSys   = {'PassiveSystem', 'ActiveSystem'};                          % row
nameWave  = {'wave_irr_Hs3_Te10_40min'};     % column
nameParam = {'Ap_2', 'Ap_1'};

for i = 1:length(nameSys)
    for j = 1:length(nameWave)
        nameFile  = [nameSys{i} '_' nameWave{j} '_' nameParam{i}];
        sys(i, j) = load([analysisPath  nameFile]);
    end
end

clc
%%
% i = 2
doAmpMean = 1; 
c = 1; 
if doAmpMean == 1
for j = 1:2
    if j == 1
        sigName = 'Fpto';
        titleName = 'Piston Forcing Distribution';
        sigScale = 1e-3;
        xlabStr = 'Mean [kN]'; 
        ylabStr = 'Amplitude [kN]';
    else
        sigName = 'T_gen';
        titleName = 'Generator Torque Distribution';
        sigScale = 1;
        xlabStr = 'Mean [N-m]'; 
        ylabStr = 'Amplitude [N-m]';
    end
    
    for i = 1:2
        if i == 1
            sysName = 'Passive System';
            
        else
            sysName = 'Active System';
        end
        
        
        
        ti = 600;
        tf = sys(i,1).out.simData.time(end);
        timeTemp = sys(i,1).out.simData.time;
        [time, tind] = getTwindow(timeTemp, ti, tf);
        
        sig = sys(i,1).out.simData.(sigName)(tind);
        
        [ext, exttime] = sig2ext(sig, time);
        
        rf = rainflow(ext, exttime);
        
        % rfdemo2(ext)
        
%         rfhist(rf, 30, 'mean')
        rf(1,:) = rf(1,:)*sigScale;
        rf(2,:) = rf(2,:)*sigScale;
        % m = rfmatrix(rf,30,30,'mean','ampl');
        % nsum = sum(sum(m));
        nsum = sum(rf(3,:));
        rf(3,:) = rf(3,:)/nsum;
        
        
        fullRF{i,j} = rf; 
        nTot(i,j)  = nsum; 
        
        
        
        % rf(3,:) = rf(3,:)./nsum;
        figure
        rfmatrix(rf,30,30,'mean','ampl')
        view(3)
        % ztick = get(gca, 'ztick');
        % ztick = ztick/nsum;
        % set(gca, 'zticklabel', ztick);
        grid off
        hx = xlabel(xlabStr);
        set(hx, 'Rotation', 27.5 )
        hy = ylabel(ylabStr);
        set(hy, 'Rotation', -37.5)
        hz = zlabel('Cycle Probability');
        ht = title([titleName '--' sysName]);
        hl = legend('dummy');
        zlim([0, 0.1])
        
        set( gca                       , ...
            'FontName'   , 'Helvetica' );
        set([hx, hy, hz, ht], ...
            'FontName'   , 'AvantGarde');
        
        
        set([hl, gca]             , ...
            'FontSize'   , 11           );
        
        set([hx, hy, hz, ht]  , ...
            'FontSize'   , 16          );
        set( ht                    , ...
            'FontSize'   , 16          , ...
            'FontWeight' , 'bold'      );
        set(gca, ...
            'Box'         , 'off'     , ...
            'TickDir'     , 'out'     , ...
            'TickLength'  , [.02 .02] , ...
            'XMinorTick'  , 'on'      , ...
            'YMinorTick'  , 'on'      , ...
            'ZMinorTick'  , 'on'      , ...
            'XColor'      , [.3 .3 .3], ...
            'YColor'      , [.3 .3 .3], ...
            'ZColor'      , [.3 .3 .3], ...
            'LineWidth'   , 2         );
        set(gca, 'ZGrid', 'on')
        
        
        set(gcf, 'Outerposition', [-1220 331  729  713])
        
        delete(hl)
        
        saveas(gcf, [savePathPaper 'Loading_' sigName '_' nameSys{i} '_AmpMean.eps'], 'epsc')
        
        
     
        
    end
end
end 

%%
%% PTO FORCE Rainflow
% Plot Properties
p.titleStr = {'Piston','Piston'};
p.sysStr   = {'Passive System', 'Active System'}; 
p.nameSys  = nameSys;
p.ylimit  = [0,0.1];
p.sigScale = 1e-3;
p.nameSig   = {'Fpto', 'Fpto'}; 
p.xlab    = {'Force [kN]'};
p.xUpLim  = 1200;

stats.pto.ampl = plot_hist1(nameSys, sys, p, 'ampl');

for i = 1:2
fprintf(['\n' p.sysStr{i} ' -- PTO AMPLITUDE\n'])
fprintf('---------------------\n')
fprintf('Avg. Load   =  %3.2f\n', stats.pto.ampl.(nameSys{i}).avgLoad)
fprintf('Var. Load   =  %3.2f\n', stats.pto.ampl.(nameSys{i}).var)
fprintf('STD. Load   =  %3.2f\n', stats.pto.ampl.(nameSys{i}).std)
fprintf('Min. Load   =  %3.2f\n', stats.pto.ampl.(nameSys{i}).minLoad)
fprintf('Max. Load   =  %3.2f\n', stats.pto.ampl.(nameSys{i}).maxLoad)
fprintf('Max. Range  =  %3.2f\n', stats.pto.ampl.(nameSys{i}).maxRange)
fprintf('Tot. Cycle  =  %3.2f\n', stats.pto.ampl.(nameSys{i}).totCycles)
end
saveas(gcf, [savePathPaper 'PistonLoadingAmpl.eps'], 'epsc')

%% Generator FORCE Rainflow
% Plot Properties
p.titleStr = {'Generator','Generator'};
p.sysStr   = {'Passive System', 'Active System'}; 
p.nameSys  = nameSys;
p.ylimit  = [0,0.1];
p.sigScale = 1;
p.nameSig   = {'T_gen', 'T_gen'}; 
p.xlab    = {'Torque [N-m]'};           
p.xUpLim  = 800;    

stats.gen.ampl = plot_hist1(nameSys, sys, p, 'ampl');

for i = 1:2
fprintf(['\n' p.sysStr{i} ' -- GEN AMPLITUDE\n'])
fprintf('---------------------\n')
fprintf('Avg. Load   =  %3.2f\n', stats.gen.ampl.(nameSys{i}).avgLoad)
fprintf('Var. Load   =  %3.2f\n', stats.gen.ampl.(nameSys{i}).var)
fprintf('STD. Load   =  %3.2f\n', stats.gen.ampl.(nameSys{i}).std)
fprintf('Min. Load   =  %3.2f\n', stats.gen.ampl.(nameSys{i}).minLoad)
fprintf('Max. Load   =  %3.2f\n', stats.gen.ampl.(nameSys{i}).maxLoad)
fprintf('Max. Range  =  %3.2f\n', stats.gen.ampl.(nameSys{i}).maxRange)
fprintf('Tot. Cycle  =  %3.2f\n', stats.gen.ampl.(nameSys{i}).totCycles)
end

saveas(gcf, [savePathPaper 'GeneratorLoadingAmpl.eps'], 'epsc')

%% PTO FORCE Rainflow
% Plot Properties
p.titleStr = {'Piston','Piston'};
p.sysStr   = {'Passive System', 'Active System'}; 
p.nameSys  = nameSys;
p.ylimit  = [0,0.1];
p.sigScale = 1e-3;
p.nameSig   = {'Fpto', 'Fpto'}; 
p.xlab    = {'Force [kN]'};
p.xUpLim  = 1200;

stats.pto.mean = plot_hist1(nameSys, sys, p, 'mean');

for i = 1:2
fprintf(['\n' p.sysStr{i} ' -- PTO MEAN\n'])
fprintf('---------------------\n')
fprintf('Avg. Load   =  %3.2f\n', stats.pto.mean.(nameSys{i}).avgLoad)
fprintf('Var. Load   =  %3.2f\n', stats.pto.ampl.(nameSys{i}).var)
fprintf('STD. Load   =  %3.2f\n', stats.pto.ampl.(nameSys{i}).std)
fprintf('Min. Load   =  %3.2f\n', stats.pto.mean.(nameSys{i}).minLoad)
fprintf('Max. Load   =  %3.2f\n', stats.pto.mean.(nameSys{i}).maxLoad)
fprintf('Max. Range  =  %3.2f\n', stats.pto.mean.(nameSys{i}).maxRange)
fprintf('Tot. Cycle  =  %3.2f\n', stats.pto.mean.(nameSys{i}).totCycles)
end

saveas(gcf, [savePathPaper 'PistonLoadingMean.eps'], 'epsc')

%% Generator FORCE Rainflow
% Plot Properties
p.titleStr = {'Generator','Generator'};
p.sysStr   = {'Passive System', 'Active System'}; 
p.nameSys  = nameSys;
p.ylimit  = [0,0.1];
p.sigScale = 1;
p.nameSig   = {'T_gen', 'T_gen'}; 
p.xlab    = {'Torque [N-m]'};           
p.xUpLim  = 800;    

stats.gen.mean = plot_hist1(nameSys, sys, p, 'mean');


for i = 1:2
fprintf(['\n' p.sysStr{i} ' -- GEN MEAN\n'])
fprintf('---------------------\n')
fprintf('Avg. Load   =  %3.2f\n', stats.gen.mean.(nameSys{i}).avgLoad)
fprintf('Var. Load   =  %3.2f\n', stats.gen.ampl.(nameSys{i}).var)
fprintf('STD. Load   =  %3.2f\n', stats.gen.ampl.(nameSys{i}).std)
fprintf('Min. Load   =  %3.2f\n', stats.gen.mean.(nameSys{i}).minLoad)
fprintf('Max. Load   =  %3.2f\n', stats.gen.mean.(nameSys{i}).maxLoad)
fprintf('Max. Range  =  %3.2f\n', stats.gen.mean.(nameSys{i}).maxRange)
fprintf('Tot. Cycle  =  %3.2f\n', stats.gen.mean.(nameSys{i}).totCycles)
end

saveas(gcf, [savePathPaper 'GeneratorLoadingMean.eps'], 'epsc')


% %% PTO FORCE Rainflow 
% % Plot Properties
% p.titleStr = {'Piston','Piston'};
% p.sysStr   = {'Passive System', 'Active System'}; 
% p.nameSys  = nameSys;
% p.ylimit  = [0,1];
% p.sigScale = 1e-3;
% p.nameSig   = {'Fpto', 'Fpto'}; 
% p.xlab    = {'Force [kN]'};
% p.xUpLim  = 1200;
% 
% stats.pto = plot_hist1(nameSys, sys, p, 'ampl');
% 
% saveas(gcf, [savePathPaper 'PistonLoadingAmpl.eps'], 'epsc')
% 
% %% Generator FORCE Rainflow
% % Plot Properties
% p.titleStr = {'Generator','Generator'};
% p.sysStr   = {'Passive System', 'Active System'}; 
% p.nameSys  = nameSys;
% p.ylimit  = [0,1];
% p.sigScale = 1;
% p.nameSig   = {'T_gen', 'T_gen'}; 
% p.xlab    = {'Torque [N-m]'};           
% p.xUpLim  = 800;    
% 
% stats.gen = plot_hist1(nameSys, sys, p, 'ampl');
% 
% saveas(gcf, [savePathPaper 'GeneratorLoadingAmpl.eps'], 'epsc')
% 
% %% MEAN LOADING
% 
% %% PTO FORCE Rainflow 
% % Plot Properties
% p.titleStr = {'Piston','Piston'};
% p.sysStr   = {'Passive System', 'Active System'}; 
% p.nameSys  = nameSys;
% p.ylimit  = [0,1];
% p.sigScale = 1e-3;
% p.nameSig   = {'Fpto', 'Fpto'}; 
% p.xlab    = {'Force [kN]'};
% p.xUpLim  = 1200;
% 
% stats.pto = plot_hist1(nameSys, sys, p, 'mean');
% 
% saveas(gcf, [savePathPaper 'PistonLoadingMean.eps'], 'epsc')
% 
% %% Generator FORCE Rainflow
% % Plot Properties
% p.titleStr = {'Generator','Generator'};
% p.sysStr   = {'Passive System', 'Active System'}; 
% p.nameSys  = nameSys;
% p.ylimit  = [0,1];
% p.sigScale = 1;
% p.nameSig   = {'T_gen', 'T_gen'}; 
% p.xlab    = {'Torque [N-m]'};           
% p.xUpLim  = 800;    
% 
% stats.gen = plot_hist1(nameSys, sys, p, 'mean');
% 
% saveas(gcf, [savePathPaper 'GeneratorLoadingMean.eps'], 'epsc')



%% AMPLITUDE LOADING


% nBins = 31; 
% % 
% % for j = 1:2
% %     for i = 1:2
% %         fullRF{i,j}(3,
% %         
% %     end
% % end
% 
% for i = 1:2
%         if i == 1
%             sysName = 'Passive System';
%             
%         else
%             sysName = 'Active System';
%         end
% figure 
% set(gcf, 'Outerposition', [-1319         413        1030         633])
% 
% ax1 = subplot(2,2,1);
% [n1,x1] = rfhist(fullRF{i,1}, nBins, 'ampl');
% n1 = n1/sum(n1);
% bar(x1,n1,1)
% hx = xlabel('Amplitude [kN]');
% hy = ylabel('Cycle Probability');
% ht = title('Piston');
% hl = legend('dummy');
% prettyPlot(hx, hy, ht, hl); 
% p1 = get(ax1,'Position'); 
% set(ax1,'Position',[p1(1)-0.05 p1(2)-0.035 p1(3)+0.05 p1(4)])
% 
% ax2 = subplot(2,2,2);
% [n2,x2] = rfhist(fullRF{i,2}, nBins, 'ampl');
% n2 = n2/sum(n2);
% bar(x2,n2,1)
% hx = xlabel('Amplitude [kN]');
% hy = ylabel('Cycle Probability');
% ht = title('Generator');
% prettyPlot(hx, hy, ht, hl); 
% p2 = get(ax2,'Position'); 
% set(ax2,'Position',[p2(1)+0.005 p2(2)-0.035 p2(3)+0.05 p2(4)])
% 
% ax3 = subplot(2,2,3);
% [n3,x3] = rfhist(fullRF{i,1}, nBins, 'mean');
% n3 = n3/sum(n3);
% bar(x3,n3,1)
% hx = xlabel('Mean [kN]');
% hy = ylabel('Cycle Probability');
% prettyPlot(hx, hy, ht, hl); 
% p3 = get(ax3,'Position'); 
% set(ax3,'Position',[p3(1)-0.05 p3(2)-0.01 p3(3)+0.05 p3(4)])
% 
% ax4 = subplot(2,2,4);
% [n4,x4] = rfhist(fullRF{i,2}, nBins, 'mean');
% n4 = n4/sum(n4);
% bar(x4,n4,1)
% hx = xlabel('Mean [kN]');
% hy = ylabel('Cycle Probability');
% prettyPlot(hx, hy, ht, hl); 
% p4 = get(ax4,'Position'); 
% set(ax4,'Position',[p4(1)+0.005 p4(2)-0.01 p4(3)+0.05 p4(4)])
% 
% delete(hl)
% 
% annotation(gcf,'textbox',...
%     [0.43 0.94 0.17 0.05],...
%     'String',{'Passive System'},...
%     'HorizontalAlignment','center',...
%     'FontWeight','demi',...
%     'FontSize',16,...
%     'FontName','AvantGarde',...
%     'LineStyle','none');
% 
% 
% 
% saveas(gcf, [savePathPaper 'Loading_' nameSys{i} '_AmpMeanFullRange.eps'], 'epsc')
% end
% set(gcf, 'Outerposition', [-1220 331  729  713])
