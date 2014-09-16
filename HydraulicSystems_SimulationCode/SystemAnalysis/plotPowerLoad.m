function [ax1, ax2] = plotPowerLoad(data, p)

% Get Power Data
p.ti = [];
p.tf = [];
p.sigScale  = 1e-3;
p.sigName   = 'P_genMean';
[param, P_genMean, time] = getData2Plot(data, p);
p.sigName   = 'P_hydMean';
[param, P_hydMean, time] = getData2Plot(data, p);

% Get Loading Data
p.ti = 600;
p.tf = [];
p.sigName   = 'Fpto';
p.sigScale  = 1e-3;
[param, Fpto, time] = getData2Plot(data, p);
nBins = 30;
[x, n] = calcRainflow(Fpto, nBins, 'ampl');
avgLoad_Fpto = sum(x.*n);


% Get Loading Data
p.sigName   = 'T_gen';
p.sigScale  = 1;
[param, Tgen, time] = getData2Plot(data, p);
nBins = 30;
[x, n] = calcRainflow(Tgen, nBins, 'mean');
avgLoad_Tgen = sum(x.*n);


% Plot Data
for i = 1:length(param)
    P_gMean(i) = P_genMean{i};
    P_hMean(i) = P_hydMean{i};
end

figure
ax1 = subplot(2,1,1)
plot(param,  P_gMean, 'linewidth', 2); 
% text(param(2)+0.5,avgLoad_Fpto(2)-0.005,' \uparrow Mean Load','FontSize',14, 'color','b')
% col2 = get(H2, 'color');
% text(param(2)-0.5,avgLoad_Fpto(2)+0.025,' \uparrow Mean Power','FontSize',14, 'color',col2)
% hl = legend([H1 H2], 'Avg. Power', ['Avg. Force ' rfType], 'location', 'best');
hl = legend('dummy');
hy = ylabel('Power [kW]');
% hy(2) = ylabel(ax2(2), 'Force [kN]');
set(gca, 'Ylim', [70 90]...
         , 'YTick', [70:5:90])
     set(gca, 'Xlim', [param(1), param(end)])
% set(gca, 'Ylim', [80 120]...
%     , 'YTick', [80:10:120])
% set(ax2(2), 'Ylim', [60 85])

% set(gca, 'xtick',  param,...
%          'xticklabel', [0.8:0.1:1.3],...
%          'xlim', [param(1) param(end)]);  %% Turn me on or off
        

hx = xlabel(p.paramStr);
grid on
ht = title('Average Power');
% set(gca, 'XTickLabel', {}, 'XTick', [])
set(gca, ...
  'Box'         , 'off'     , ...
  'TickDir'     , 'out'     , ...
  'TickLength'  , [.02 .02] , ...
  'XMinorTick'  , 'on'      , ...
  'YMinorTick'  , 'on'      , ...
  'LineWidth'   , 2      );


set( gca                       , ...
    'FontName'   , 'Helvetica' );
set([hx, hy, ht], ...
    'FontName'   , 'AvantGarde');
set([hl, gca]             , ...
    'FontSize'   , 11           );
set([hx, hy,  ht]  , ...
    'FontSize'   , 14          );
set( ht                    , ...
    'FontSize'   , 16          , ...
    'FontWeight' , 'bold'      );
set(gca, ...
  'Box'         , 'off'     , ...
  'TickDir'     , 'out'     , ...
  'TickLength'  , [.02 .02] , ...
  'XMinorTick'  , 'on'      , ...
  'YMinorTick'  , 'on'      , ...
  'LineWidth'   , 2         );

delete(hl)

subplot(2,1,2)
[ax2,H1,H2] = plotyy(param,  avgLoad_Fpto, param, avgLoad_Tgen);
% text(param(2)+0.5,avgLoad_Tgen(2)-0.005,' \uparrow Mean Load','FontSize',14, 'color','b')
% col2 = get(H2, 'color');
% text(param(2)-0.5,avgLoad_Tgen(2)+0.025,' \uparrow Mean Power','FontSize',14, 'color',col2)
set(H1, 'linewidth', 2)
set(H2, 'linewidth', 2, 'linestyle', '--')
% hl = legend('dummy');
hl = legend([H1 H2], 'Piston Force Amplitude', 'Generator Torque Mean', 'location', 'best');
hy(1) = ylabel(ax2(1), 'Force [kN]');
hy(2) = ylabel(ax2(2), 'Torque [N-m]');
set(ax2(1), 'Ylim', [80 120]...
         ,'YTick', [80:10:120]);
set(ax2, 'Xlim', [param(1), param(end)]);
set(ax2(2), 'Ylim', [200 600]...
    , 'YTick', [200:100:600])


% set(ax2, 'xtick',  param,...
%          'xticklabel', [0.8:0.1:1.3],...
%          'xlim', [param(1) param(end)]);  %% Turn me on or off
        
hx = xlabel(ax2(1), p.paramStr);
grid on
ht = title('Average Load');
set(ax2(2), 'XTickLabel', {}, 'XTick', [])
set(ax2(2), ...
  'Box'         , 'off'     , ...
  'TickDir'     , 'out'     , ...
  'TickLength'  , [.02 .02] , ...
  'XMinorTick'  , 'on'      , ...
  'YMinorTick'  , 'on'      , ...
  'LineWidth'   , 2       );

set( gca                       , ...
    'FontName'   , 'Helvetica' );
set([hx, hy, ht], ...
    'FontName'   , 'AvantGarde');
set([hl, gca]             , ...
    'FontSize'   , 11           );
set([hx, hy,  ht]  , ...
    'FontSize'   , 14          );
set( ht                    , ...
    'FontSize'   , 16          , ...
    'FontWeight' , 'bold'      );
set(gca, ...
  'Box'         , 'off'     , ...
  'TickDir'     , 'out'     , ...
  'TickLength'  , [.02 .02] , ...
  'XMinorTick'  , 'on'      , ...
  'YMinorTick'  , 'on'      , ...
  'LineWidth'   , 2         );
% delete(hl);

set(gcf, 'Outerposition', [-1220 331  729  713])