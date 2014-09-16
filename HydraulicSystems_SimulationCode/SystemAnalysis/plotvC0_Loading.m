%% Non-Linear Hydraulic PTO - GMREC Conference
% Sean Casey
% 4/30/13
% GRA - OSU
%
%   Create Plot for loading cycles with parameter change
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

maxSig = 0;
nParams = 9;
titleStr = 'Passive System PTO Loading';
sigStr   = 'Force PTO [MN]' ;
paramStr = 'Accumulator Volume Ratio';%'Generator Damping' ;
colorStr = 'Number Cycles';



for i = 1:nParams
    
    load(['PassiveSystem_wave_irr_Hs4_Te12_testvC0_' num2str(i+1)]);
    ti = 300;
    tf = out.simData.time(end); 
    [time, tind] = getTwindow(out.simData.time, ti, tf);
    
    param(i) = out.pto.vC0/2;
    sig{:,i} = out.simData.Fpto(tind:end)*1e-6;
    
    if max(sig{:,i}) > maxSig
        maxSig = max(sig{:,i});
    end
    
end

nBins = linspace(0, maxSig, 60);

for i = 1:nParams
    ext = sig2ext(sig{:,i});
    rf = rainflow(ext);
    [n(:,i), x(:,i)] = rfhist(rf, nBins);
end

%%
[X, Y] = meshgrid(param, x(2:end,1)');
Y = Y;
Z = n(2:end,:);
ywidth = Y(2,1) - Y(1,1);
xwidth = param(2) - param(1);

figure
set(gcf,'renderer','zbuffer')
scatterbar3(X, Y, Z, xwidth, ywidth);
view(2)
cb = colorbar('location', 'southoutside');
hxc = xlabel(cb, colorStr);


hx = xlabel(paramStr);
hy = ylabel(sigStr);
ht = title(titleStr);
hl = legend('dummy');


set( gca                       , ...
    'FontName'   , 'Helvetica' );
set([hx, hy, ht, hxc], ...
    'FontName'   , 'AvantGarde');


set([hl, gca]             , ...
    'FontSize'   , 11           );

set([hx, hy,  ht]  , ...
    'FontSize'   , 14          );
set( ht                    , ...
    'FontSize'   , 16          , ...
    'FontWeight' , 'bold'      );
set([gca], ...
    'Box'         , 'off'     , ...
    'TickDir'     , 'out'     , ...
    'TickLength'  , [.02 .02] , ...
    'XMinorTick'  , 'off'      , ...
    'YMinorTick'  , 'off'      , ...
    'XColor'      , [.3 .3 .3], ...
    'YColor'      , [.3 .3 .3], ...
    'LineWidth'   , 2         );

set([cb], ...
    'Box'         , 'on'     , ...
    'TickDir'     , 'in'     , ...
    'TickLength'  , [.01 .01] , ...
    'XMinorTick'  , 'off'      , ...
    'YMinorTick'  , 'off'      , ...
    'XColor'      , [.3 .3 .3], ...
    'YColor'      , [.3 .3 .3], ...
    'LineWidth'   , 2         );
set([hxc]  , ...
    'FontSize'   , 12          );

delete(hl)

%%
% set(0,'Units','normalized')
% ss = get(0,'ScreenSize')
set(gcf, 'Outerposition', [-1220 331  729  713])
p1 = get(gca,'Position');
set(gca,'Position',[p1(1) p1(2)+0.01 p1(3) p1(4)]);
p2 = get(cb, 'Position');
set(cb,'Position',[p2(1) p2(2)-0.06 p2(3) p2(4)]);
