function plot_histLoad(param, x, n, p) 

% Unwrap plot parameters
titleStr = p.titleStr;
cmap     = p.cmap; 
colorStr = p.colorStr;
sigStr   = p.sigStr;
paramStr = p.paramStr;


% Create grid 
[X, Y] = meshgrid(param, x(:,1)');
Z = n(:,:);
ywidth = Y(2,1) - Y(1,1);
xwidth = param(2) - param(1);

% Create figure
figure
set(gcf,'renderer','zbuffer')
scatterbar3(X, Y, Z, xwidth, ywidth);
view(2)
cb = colorbar('location', 'southoutside');
hxc = xlabel(cb, colorStr);
clim = get(gca, 'clim');
sp = -clim(end)/64;             % Find width of individual color

set(gca, 'clim', [sp, clim(end)]); 


hx = xlabel(paramStr);
hy = ylabel(sigStr); %, 'interpreter', 'latex','fontsize', 18, 'rotation', 0);
ht = title(titleStr);
hl = legend('dummy');

% Set position of axes
set(gcf, 'Outerposition', [-1220 331  729  713])
p1 = get(gca,'Position');
set(gca,'Position',[p1(1) p1(2)+0.01 p1(3) p1(4)]);
p2 = get(cb, 'Position');
set(cb,'Position',[p2(1) p2(2)-0.07 p2(3) p2(4)]);
% p3 = get(hy, 'Position'); 
% set(hy, 'Position', [p3(1)-0.4 p3(2) p3(3)]);

% Set axes properties
set(gca, 'XTick', param); 

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

s = gca; 
ax=copyobj(gca,gcf);
xlab = get(ax, 'xlabel');
ylab = get(ax, 'ylabel');
delete(xlab);
delete(ylab);
set(ax,'xtick',[],'ytick',[], ...
    'handlevisibility','off','hittest','off', ...
    'box','on','color','none')
axes(s);
box off
uistack(s,'bottom')

set(gcf, 'Colormap', cmap);

%%
% set(0,'Units','normalized')
% ss = get(0,'ScreenSize')