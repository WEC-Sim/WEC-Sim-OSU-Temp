function plot_bg(data, ti, tf)


maxSig = 0;
nParams = length(data);
titleStr = 'Passive System PTO Loading';
sigStr   = 'Force PTO [MN]' ;
paramStr = 'Generator Damping' ;
colorStr = 'Number Cycles/Total Number Cycles';
paramName = 'bg'; 

for i = 1:nParams
    out = data(1,i).out; 
    
    if isempty(tf)
        tf = out.simData.time(end);
    end
    
    [time, tind] = getTwindow(out.simData.time, ti, tf);
    
    param(i) = out.pto.(paramName); 
    sig{:,i} = out.simData.Fpto(tind:end)*1e-6;
    
    if max(sig{:,i}) > maxSig
        maxSig = max(sig{:,i});
    end
    
end

nBins = linspace(0, maxSig, 30);

% Rainflow Counting
for i = 1:nParams
    ext = sig2ext(sig{:,i});
    rf = rainflow(ext);
    [n(:,i), x(:,i)] = rfhist(rf, nBins);
    nsum = sum(n(:,i)); 
    n(:,i) = n(:,i)/nsum;
end

% nmax = max(n);
% n = n./nmax; 

%%
[X, Y] = meshgrid(param, x(1:end,1)');
Y = Y;
Z = n(1:end,:);
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


