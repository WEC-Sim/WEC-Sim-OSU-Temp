figure

load clown
colormap(map)

subplot(2,2,1)
% imagesc(X)
box on
title('Box on')

subplot(2,2,2)
% imagesc(X)
box off
title('Box off')

subplot(2,2,3);
% imagesc(X)
hold on
x=xlim;
y=ylim;
line([x(1) x(2)],[y(2) y(2)],'color',get(gca,'xcolor'))
line([x(2) x(2)],[y(1) y(2)],'color',get(gca,'ycolor'))
box off
title('Box off + Lines')

s=subplot(2,2,4);
ax=copyobj(gca,gcf);
set(ax,'xtick',[],'ytick',[], ...
    'handlevisibility','off','hittest','off', ...
    'box','on','color','none')
axes(s);
% imagesc(X)
box off
title('Box off + a second axes')
uistack(s,'bottom')
