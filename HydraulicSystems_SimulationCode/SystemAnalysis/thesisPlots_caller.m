%% Plotting and Analysis Functions for Thesis
% Sean Casey
% 5/6/13
% GRA - OSU
%
% Notes:

%% Initialize Workspace
clear;
clc; close all
set(0,'DefaultFigureWindowStyle','normal')
funPath         = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
analysisPath    = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\AnalysisFiles\';
savePath        = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\Figures\';
savePathPaper   = 'C:\Users\Sean\Desktop\WaveEnergyResearch\Thesis\Template\beavtex\FiguresTables\';
addpath(funPath, savePath, analysisPath);

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
doLoadData = 1; %input('Load Data? [1 = yes, 0 = no]        ');
doLoadPlots = 1;
doPower2Load = 1;
doLoadTS = 0; 

paramName = {'Ap'}; %{'alpha', 'bg', 'vC0', 'Ap'};
nameSys   = 'PassiveSystem';
nameWave  = 'wave_irr_Hs3_Te10_40min';
varNum    = '*';

if doLoadData == 1
    % clear irrData regData
    
    for i = 1:length(paramName)
        fnames = dir([analysisPath, nameSys '_' nameWave '_' paramName{i} '_' varNum '.mat']);
        
        for j = 1:length(fnames)
            irrData.(paramName{i})(j) = load([analysisPath fnames(j).name]);
           
            %             load([analysisPath fnames(j).name])
            %             irrData.(paramName{i}).(paramName{i})(j) = out.pto.(paramName{i});
            %             irrData.(paramName{i}).time{:,j} = out.simData.time;
            %             irrData.(paramName{i}).Fpto{:,j} = out.simData.Fpto;
            %             irrData.(paramName{i})(j) =
        end
        
    end
    %         irrData = thesisPlots_loadData(analysisPath, paramName, nameSys, nameWave, varNum);
    %
    %     regData = load([analysisPath, nameSys, '_wave_reg_Hs3_Te10_10min_Ap_1.mat']);
end

% irrData.(paramName{i})(1) = [];

%% Plot/Analyze Data

for i = 1:length(paramName)
    close all 
    switch paramName{i}
        case 'bg'
            p.paramStr   = 'Generator Damping [kg/s]';
            p.paramStr2  = 'Generator Damping';
            p.legTitle    = 'Damping [kg/s]';
            irrData.(paramName{i})(1) = [];
        case 'alpha'
            p.paramStr   = 'Motor Displacement Fraction';
            p.paramStr2  = 'Motor Displacement';
            p.legTitle   = sprintf('Motor Displacement\n Fraction');
        case 'Ap'
            p.paramStr   = 'Pump Area Fraction';
            p.paramStr2  = 'Pump Area Fraction';
            p.legTitle   = sprintf('Pump Area\n Fraction');
%                     switch paramName{i}
%             case 'Ap'
                ApTemp = (0.7:0.1:1.3);
                for j = 1:length(irrData.Ap)
                    irrData.Ap(j).out.pto.Ap = ApTemp(j);
                end
%         end
            
        case 'vC0'
            p.paramStr   = 'High Pressure Accumulator Volume [m^3]';
            p.paramStr2  = 'Accumulator Volume';
            p.legTitle   = sprintf('Accumulator\n Volume [m^3]');
    end
    
    
    if doLoadPlots == 1
        % Piston Loading
        p.ti = 600;
        p.tf = [];
        p.paramName = paramName{i};
        p.sigName   = 'Fpto';
        p.paramScale = 1;
        p.sigScale  = 1e-3;
        
        [param, sig, time] = getData2Plot(irrData.(paramName{i}), p);
        
        nBins = 30;
        [x, n] = calcRainflow(sig, nBins, 'ampl');
        
        avgLoad = sum(x.*n);
%         avgLoadMat = ones(size(x,1),1)*avgLoad;
%         x = x./avgLoadMat;
        
        p.titleStr  = 'Piston Amplitude Loading';
        p.cmap      = cmap;
        p.colorStr  = 'Cycle Probability';
        p.sigStr    = 'Force [kN]'; %'$$\frac{F}{{F}_{avg}}$$';
        
        plot_histLoad(param, x, n, p);

        saveas(gcf, [savePath       'loading_pto_' nameSys '_' paramName{i}], 'epsc')
        saveas(gcf, [savePathPaper  'loading_pto_' nameSys '_' paramName{i}], 'epsc')
        
        % Generator Loading
        p.ti = 600;
        p.tf = [];
        p.paramName = paramName{i};
        p.sigName   = 'T_gen';
        p.paramScale = 1;
        p.sigScale  = 1;
        
        [param, sig, time] = getData2Plot(irrData.(paramName{i}), p);
        
        [x, n] = calcRainflow(sig, nBins, 'mean');
        
        avgLoad = sum(x.*n);
%         avgLoadMat = ones(size(x,1),1)*avgLoad;
%         x = x./avgLoadMat;
        
        p.titleStr  = 'Generator Mean Loading';
        p.cmap      = cmap;
        p.colorStr  = 'Cycle Probability';
        p.sigStr    = 'Torque [N-m]'; %$$\frac{T}{{T}_{avg}}$$';
        
        plot_histLoad(param, x, n, p);
        
        
        saveas(gcf, [savePath       'loading_gen_' nameSys '_' paramName{i}], 'epsc')
        saveas(gcf, [savePathPaper  'loading_gen_' nameSys '_' paramName{i}], 'epsc')
        
        
        
        
    end
    
    if doPower2Load == 1
        %% Power to loading
        p.paramName = paramName{i};
        p.paramScale = 1;
        data = irrData.(paramName{i});
        

        
        [ax1, ax2] = plotPowerLoad(data, p);
       
        
%         pause
        saveas(gcf, [savePath       'power2load_' nameSys '_' paramName{i}], 'epsc')
        saveas(gcf, [savePathPaper  'power2load_' nameSys '_' paramName{i}], 'epsc')
        %
    end
    if doLoadTS == 1
    %% Time Series
    %         close all
    % Accumulator Volume
    p.ti = 700;
    p.tf = [800];
    p.paramName = paramName{i};
    p.paramScale = 1; %4e6;
    p.sigName   = 'P_gen' ;%'P_gen';
    p.sigStr    = 'Power [kW]';
    p.sigScale  = 1e-3;
    p.titleStr  = ['Power Output with Varied '  p.paramStr2];
    p.cmap      = cmap;
  
    
%     p.legTitle  = 'Motor Displacement Fraction';
    %         p.colorStr  = 'Number Cycles/Total Cycles';
    
    [param, sig, time] = getData2Plot(irrData.(paramName{i}), p);
    
    figure
    plot_timeSeries(time, sig, param, p)
    xlim([p.ti p.tf])
    ylim([80, 210])
    set(gcf, 'Outerposition', [-1220 331  729  713])
    
    
    saveas(gcf, [savePath       'ts_' p.sigName '_' nameSys '_' paramName{i}], 'epsc')
    saveas(gcf, [savePathPaper  'ts_' p.sigName '_' nameSys '_' paramName{i}], 'epsc')
    
    %%
    %%%%%%%%%%%%%%%%%%%
    
    p.ti = 700;
    p.tf = [800];
    p.sigName   = 'Fpto' ;%'P_gen';
    p.sigStr    = 'Force [kN]';
    p.sigScale  = 1e-3;
    p.titleStr  = ['Piston Force with Varied '  p.paramStr2];
    
    %         p.colorStr  = 'Number Cycles/Total Cycles';
    
    [param, sig, time] = getData2Plot(irrData.(paramName{i}), p);
    
    figure
    ax1 = subplot(2,1,1);
    hl = plot_timeSeries(time, sig, param, p);
    delete(hl)
    xlim([p.ti p.tf])
    ylim([-1000, 1000]);
    
    
    p.sigName   = 'T_gen' ;%'P_gen';
    p.sigStr    = 'Torque [N-m]';
    p.sigScale  = 1;
    p.titleStr  = ['Generator Torque with Varied '  p.paramStr2];
    
    [param, sig, time] = getData2Plot(irrData.(paramName{i}), p);
    
    ax2 = subplot(2,1,2);
    hl = plot_timeSeries(time, sig, param, p);
    xlim([p.ti p.tf])
    ylim([200, 800])
    set(hl, 'Orientation', 'horizontal', 'location', 'southoutside')
    p1 = get(ax1,'Position');
    p2 = get(ax2,'Position');
    set(ax1,'Position',[p1(1) p1(2)+0.06 p1(3) p2(4)+0.04])
    set(ax2,'Position',[p2(1) p2(2)-0.01 p1(3) p2(4)+0.04])
   
    pl = get(hl, 'Position');
    
    set(hl, 'Position', [pl(1), pl(2)-0.08, pl(3), pl(4)])
    set(gcf, 'Outerposition', [-1220 331  729  713])
    saveas(gcf, [savePath       'tsLoads_'  nameSys '_' paramName{i}], 'epsc')
    saveas(gcf, [savePathPaper  'tsLoads_'  nameSys '_' paramName{i}], 'epsc')
    end
    
    
    
end

















%         case 'alpha'
%             p.ti = 600;
%             p.tf = [];
%             p.titleStr  = 'Passive System Piston Loading';
%             p.sigStr    = 'Piston Force [MN]';
%             p.paramStr  = 'Swashplate Angle Ratio' ;
%             p.colorStr  = 'Number Cycles/Total Cycles';
%             p.paramName = 'alpha';
%             p.sigName   = 'Fpto';
%             p.begInd    = 1;
%             p.paramScale = 1;
%             p.sigScale  = 1e-6;
%             p.cmap      = cmap;
%
%             plot_loading(irrData.(paramName{i}), p)
%
%             saveas(gcf, [savePath       'loading_pto_' nameSys '_' paramName{i}], 'epsc')
%             saveas(gcf, [savePathPaper  'loading_pto_' nameSys '_' paramName{i}], 'epsc')
%
%             % Generator Loading
%             p.ti = 600;
%             p.tf = [];
%             p.titleStr  = 'Passive System Generator Loading';
%             p.sigStr    = 'Generator Torque [N-m]' ;
%             p.paramStr  = 'Swashplate Angle Ratio' ;
%             p.colorStr  = 'Number Cycles/Total Cycles';
%             p.paramName = 'alpha';
%             p.sigName   = 'T_gen';
%             p.begInd    = 1;
%             p.paramScale = 1;
%             p.sigScale  = 1;
%             p.cmap      = cmap;
%
%             plot_loading(irrData.(paramName{i}), p)
%
%             saveas(gcf, [savePath       'loading_gen_' nameSys '_' paramName{i}], 'epsc')
%             saveas(gcf, [savePathPaper  'loading_gen_' nameSys '_' paramName{i}], 'epsc')
%
%         case 'Ap'
%             p.ti = 600;
%             p.tf = [];
%             p.titleStr  = 'Passive System Piston Loading';
%             p.sigStr    = 'Piston Force [MN]';
%             p.paramStr  = 'Piston Area [m^2]' ;
%             p.colorStr  = 'Number Cycles/Total Cycles';
%             p.paramName = 'Ap';
%             p.sigName   = 'Fpto';
%             p.begInd    = 1;
%             p.paramScale = 1;
%             p.sigScale  = 1e-6;
%             p.cmap      = cmap;
%
%             plot_loading(irrData.(paramName{i}), p)
%
%             saveas(gcf, [savePath       'loading_pto_' nameSys '_' paramName{i}], 'epsc')
%             saveas(gcf, [savePathPaper  'loading_pto_' nameSys '_' paramName{i}], 'epsc')
%
%             % Generator Loading
%             p.ti = 600;
%             p.tf = [];
%             p.titleStr  = 'Passive System Generator Loading';
%             p.sigStr    = 'Generator Torque [N-m]' ;
%             p.paramStr  = 'Piston Area [m^2]' ;
%             p.colorStr  = 'Number Cycles/Total Cycles';
%             p.paramName = 'Ap';
%             p.sigName   = 'T_gen';
%             p.begInd    = 1;
%             p.paramScale = 1;
%             p.sigScale  = 1;
%             p.cmap      = cmap;
%
%             plot_loading(irrData.(paramName{i}), p)
%
%             saveas(gcf, [savePath       'loading_gen_' nameSys '_' paramName{i}], 'epsc')
%             saveas(gcf, [savePathPaper  'loading_gen_' nameSys '_' paramName{i}], 'epsc')
%
%         case 'vC0'
%             p.ti = 600;
%             p.tf = [];
%             p.titleStr  = 'Passive System PTO Loading';
%             p.sigStr    = 'Force PTO [MN]' ;
%             p.paramStr  = 'High Pressure Accumulator Size [m^3]' ;
%             p.colorStr  = 'Number Cycles/Total Cycles';
%             p.paramName = 'vC0';
%             p.sigName   = 'Fpto';
%             p.begInd    = 1;
%             p.paramScale = 1;
%             p.sigScale  = 1e-6;
%             p.cmap      = cmap;
%
%             plot_loading(irrData.(paramName{i}), p)
%
%             saveas(gcf, [savePath       'loading_pto_' nameSys '_' paramName{i}], 'epsc')
%             saveas(gcf, [savePathPaper  'loading_pto_' nameSys '_' paramName{i}], 'epsc')
%
%             % Generator Loading
%             p.ti = 600;
%             p.tf = [];
%             p.titleStr  = 'Passive System Generator Loading';
%             p.sigStr    = 'Generator Torque [N-m]' ;
%             p.paramStr  = 'High Pressure Accumulator Size [m^3]' ;
%             p.colorStr  = 'Number Cycles/Total Cycles';
%             p.paramName = 'vC0';
%             p.sigName   = 'T_gen';
%             p.begInd    = 1;
%             p.paramScale = 1;
%             p.sigScale  = 1;
%             p.cmap      = cmap;
%
%             plot_loading(irrData.(paramName{i}), p)
%
%             saveas(gcf, [savePath       'loading_gen_' nameSys '_' paramName{i}], 'epsc')
%             saveas(gcf, [savePathPaper  'loading_gen_' nameSys '_' paramName{i}], 'epsc')
%     end
%
% end
