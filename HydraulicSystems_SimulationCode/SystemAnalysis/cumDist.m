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
clc; 
close all
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

load('stats'); 

%% 
nameCom = {'pto', 'gen'}; 
nameMet = {'ampl', 'mean'}; 
nameSys = {'PassiveSystem', 'ActiveSystem'};

strCom = {'Piston', 'Generator'}; 
strMet = {'Amplitude', 'Mean'}; 
strSys = {'Passive System', 'Active System'}; 

i = 1; 
j = 1; 
k = 1;

if i == 1
    xlab = 'Force [kN]'; 
else
    xlab = 'Torque [N-m]';
end


figure
for k = 1:2
n1 = stats.(nameCom{i}).(nameMet{j}).(nameSys{k}).n1; 
x1 = stats.(nameCom{i}).(nameMet{j}).(nameSys{k}).x1; 

n1Sum = sum(n1); 
n = n1/n1Sum;


x = x1;  
binwidth = (x(2,1) -x(1,1))/2;
% minSig = 
xmin = min(x); 
xmax = max(x); 

csum = 1-cumsum(n);
maxN(k) = max(csum);

ax(k) = subplot(2,1,k);
bar(x, csum, 1, 'facecolor', col(3,:))
hy = ylabel('Exceedance Probability');
hx = xlabel(xlab); 
hl = legend('dummy');
ht = title([strSys{k} ' -- ' strCom{i}, ' ' , strMet{j}]); 

grid on
% ylim([0, max(maxN)]*(1.1))
xlim([xmin-binwidth, xmax+binwidth]); 

prettyPlot(hx,hy,ht,hl); 


delete(hl)

end

set(ax, 'ylim', [0,1]); % max(maxN)]*1.1)
set(gcf, 'Outerposition', [-1220 331  729  713])


saveas(gcf, [savePath       'Exceedance_' nameCom{i}], 'epsc')
saveas(gcf, [savePathPaper  'Exceedance_' nameCom{i}], 'epsc')
