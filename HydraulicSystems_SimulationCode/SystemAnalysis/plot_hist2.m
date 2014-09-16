function stats = plot_hist2(nameSys, sys, p, rfflag)

% xlimit = p.xlimit; 
ylimit = p.ylimit; 
sigScale = p.sigScale;
titleStr = p.titleStr; 
sysStr = p.sysStr; 
nameSig = p.nameSig; 
xlab = p.xlab; 
xUpLim = p.xUpLim; 
nameSys = p.nameSys;

switch rfflag
    case 'mean'
        r = 2; 
        rfType = 'Amplitude Loading';
    case 'ampl'
        r = 1; 
        rfType = 'Mean Loading';
end


for i = 1:length(nameSys)
    
ti = 600; 
tf = sys(i,2).out.simData.time(end); 
timeTemp = sys(i,2).out.simData.time; 
[time, tind] = getTwindow(timeTemp, ti, tf);

% nBins = linspace(0,3.0,120);
sig{i} = sig2ext(sys(i,2).out.simData.(nameSig{i}));
sig{i} = sig{i}*sigScale;
end

nBins = 90;
% Rainflow Counting
for i = 1:length(sig)
    ext = sig2ext(sig{:,i});
    rftemp = rainflow(ext);
    rfmax(:,i) = max(rftemp(r,:));
    rfmin(:,i) = min(rftemp(r,:));
    
    stats.(nameSys{i}).maxLoad = max(rfmax(:,i)); 
% maxSig(:,i) = max(rfmax); 
% bins(:,i) = linspace(0, maxSig(:,i), nBins);
end    

maxSig = max(rfmax); 
minSig = min(rfmax);
bins = linspace(0, maxSig, nBins);



for i = 1:length(sig)
    ext = sig2ext(sig{:,i});
    rf = rainflow(ext);
    [n1(:,i), x1(:,i)] = rfhist(rf, bins, rfflag);
    n(:,i) = n1(:,i); 
    x(:,i) = x1(:,i); 
    nsum = sum(n(:,i)); 
    n(:,i) = n(:,i)/nsum;
    maxN(:,i) = max(n(:,i));
    
    stats.(nameSys{i}).avgLoad = sum(x(:,i).*n(:,i));
    stats.(nameSys{i}).totCycles = nsum;
    stats.(nameSys{i}).peak2avg = stats.(nameSys{i}).maxLoad/stats.(nameSys{i}).avgLoad;
%     avgLoadMat = ones(size(x,1),1)*avgLoad;
%     x(:,i) = x(:,i)/avgLoad;
end

figure
for i = 1:length(sig)
    
subplot(2,1,i)
bar(x(:,i), n(:,i), 'r','Barwidth', 1)
hy = ylabel('Cycle Probability');
% hx = xlabel('$$\frac{F}{F_{avg}}$$', 'interpreter', 'latex','fontsize', 14);
hx = xlabel(xlab);
ht = title([rfType ' -- ' titleStr{i} ' -- ' sysStr{i}]);
hl = legend('dummy'); 
ylim([0, max(maxN)])
% ylim([0,800])
binwidth = -(x(2,1) -x(1,1))/2;
xlim([minSig - binwidth, maxSig + binwidth])
grid on
prettyPlot(hx,hy,ht,hl);
delete(hl);

end

set(gcf, 'Outerposition', [-1220 331  729  713])
p1 = get(gca,'Position');


