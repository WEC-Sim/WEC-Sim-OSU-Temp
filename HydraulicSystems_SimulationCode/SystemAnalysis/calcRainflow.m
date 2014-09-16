function [x, n] = calcRainflow(sig, nBins, rfflag)

switch rfflag
    case 'mean'
        r = 2; 
        rfType = 'Mean Loading';
    case 'ampl'
        r = 1; 
        rfType = 'Amplitude Loading';
end


% Rainflow Counting
for i = 1:length(sig)
    ext = sig2ext(sig{:,i});
    rftemp = rainflow(ext);
    rfmax(:,i) = max(rftemp(r,:));
    rfmin(:,i) = min(rftemp(r,:));
end    

maxSig = max(rfmax); 
switch rfflag
    case 'mean'
        minSig = min(rfmin);
    case 'ampl'
        minSig = 0; 
end

bins = linspace(minSig, maxSig, nBins);

% maxSig = max(rfmax); 
% bins = linspace(0, maxSig, nBins);

for i = 1:length(sig)
    ext = sig2ext(sig{:,i});
    rf = rainflow(ext);
    [n1(:,i), x1(:,i)] = rfhist(rf, bins, rfflag);
    n(:,i) = n1(:,i); 
    x(:,i) = x1(:,i); 
    nsum = sum(n(:,i)); 
    n(:,i) = n(:,i)/nsum;
end
