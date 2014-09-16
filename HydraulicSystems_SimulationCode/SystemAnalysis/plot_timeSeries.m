function hl = plot_timeSeries(time, sig, param, p)

ti = p.ti;
tf = p.tf;
paramName = p.paramName;
paramScale= p.paramScale;
sigName   = p.sigName;
sigStr    = p.sigStr;
sigScale  = p.sigScale;
titleStr  = p.titleStr;
cmap      = p.cmap;
legTitle  = p.legTitle;

coldist = distinguishable_colors(20);
legStr = {};

tempLeg = 0.7:0.1:1.3;
for i = 1:length(sig)
    
    ph(i) = plot(time{i}, sig{i}, 'linewidth', 2, 'color', coldist(i,:));  hold on
    
    %     legStr{end+1} =  num2str(1e2*sqrt(4*param(i)/pi)); % Area in cm
    switch paramName
        case 'Ap'
            legStr{end+1} = num2str(tempLeg(i));
        otherwise
            legStr{end+1} = num2str(param(i)); %  %; % Area in cm;
    end
end
hl = legend(ph, legStr , 'location', 'best');
v = get(hl,'title');
set(v,'string',legTitle);
xlim([time{1}(1), time{1}(end)])
hx = xlabel('Time [s]');
hy = ylabel(sigStr);
ht = title(titleStr);
grid on

prettyPlot(hx, hy, ht, hl);
% set(gcf, 'Outerposition', [-1220 331  729  713])