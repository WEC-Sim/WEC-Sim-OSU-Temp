function getData2Plot(data, p)

ti = p.ti; 
tf = p.tf;
paramName = p.paramName; 
sigName = p.sigName;
begInd  = p.begInd; 
paramScale = p.paramScale; 
sigScale = p.sigScale; 


maxSig = 0;
nParams = length(data);

for i = 1:nParams
    out = data(1,i).out; 
    
    if isempty(tf)
        tf = out.simData.time(end);
    end
    
    [time, tind] = getTwindow(out.simData.time, ti, tf);
    
    param(i) = out.pto.(paramName)*paramScale; 
    sig{:,i} = out.simData.(sigName)(tind:end)*sigScale;
    
%     if max(sig{:,i}) > maxSig
%         maxSig = max(sig{:,i});
%     end
    
end


function calcRainflow()
% Rainflow Counting
for i = 1:nParams
    ext = sig2ext(sig{:,i});
    rftemp = rainflow(ext);
    rfmax(:,i) = max(rftemp(1,:));
end    

maxSig = max(rfmax); 
nBins = linspace(0, maxSig, 30);

for i = 1:nParams
    ext = sig2ext(sig{:,i});
    rf = rainflow(ext);
    [n1(:,i), x1(:,i)] = rfhist(rf, nBins);
    n(:,i) = n1(begInd:end,i); 
    x(:,i) = x1(begInd:end,i); 
    nsum = sum(n(:,i)); 
    n(:,i) = n(:,i)/nsum;
end




