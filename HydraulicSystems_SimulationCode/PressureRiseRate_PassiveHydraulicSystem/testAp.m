clear; close all; clc
% Model for valve opening area
funPath         = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SharedFunctions\';
analysisPath    = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\AnalysisFiles\';
savePath        = 'C:\Users\Sean\Desktop\WaveEnergyResearch\GMREC_conference_git\Models\GMREC_ModelsFinal\SystemAnalysis\Figures\';
savePathPaper   = 'C:\Users\Sean\Desktop\WaveEnergyResearch\Thesis\Template\beavtex\FiguresTables\';
addpath(funPath, savePath, analysisPath);

Amax = 0.001;
Amin = 1e-8;

pmax = 1e5;
pmin = 3/4*pmax;

k = (Amax - Amin)./(pmax-pmin);


x = linspace(pmin - (pmax-pmin)*0.15,pmax + (pmax-pmin)*0.15);
c = atanh((Amin - (Amax - Amin)/2)*2/(Amax - Amin))* 1/(pmin - (pmax+pmin)/2);

% c = 2.5e-4;   % stretch to min/max

A = (Amax - Amin)/2+Amin +(Amax - Amin)/2*tanh(c.*(x-(pmax+pmin)/2));

plot(x,A,'k', 'linewidth', 2); hold on

xlim([pmin - (pmax-pmin)*0.15, pmax + (pmax-pmin)*0.15])
ylim([Amin - (Amax-Amin)*0.15, Amax + (Amax-Amin)*0.15])

xlimits = get(gca, 'Xlim');
ylimits = get(gca, 'Ylim');

% plot(xlimits, [Amin, Amin], 'r--')
% plot(xlimits, [Amax, Amax], 'r--')
%
% plot([x(1), x(end)], [Amin, Amin], 'r')
% plot([x(1), x(end)], [Amax, Amax], 'r')

hx = xlabel('Pressure');
hy = ylabel('Open Valve Area');
ht = title('Valve Area Opening Behavior');
hl = legend('Dummy');

set(gca, 'XTick', [pmin, pmax],...
    'YTick', [Amin, Amax],...
    'XTickLabel', {'p_min', 'p_max'},...
    'YTickLabel', {'A_min', 'A_max'})

prettyPlot(hx, hy,ht,hl)
delete(hl)
grid on
set(gcf, 'Outerposition', [-1220 331  729  713])
p1 = get(gca,'Position');

saveas(gcf, [savePath       'valveOpeningBehaviour'], 'epsc')
saveas(gcf, [savePathPaper  'valveOpeningBehaviour'], 'epsc')