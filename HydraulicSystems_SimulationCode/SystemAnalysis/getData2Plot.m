function [param, sig, time] = getData2Plot(data, p)

% Unwrap parameters
ti = p.ti;
tf = p.tf;
paramName = p.paramName;
sigName = p.sigName;
paramScale = p.paramScale;
sigScale = p.sigScale;

% Get Data
nParams = length(data);
for i = 1:nParams
    out = data(1,i).out;
    
    if isempty(tf)
        tf = out.simData.time(end);
    end
    
    if isempty(ti)
        time = [];
        tind = 1;
    else
        [time{i}, tind] = getTwindow(out.simData.time, ti, tf);
    end
    
    param(i) = out.pto.(paramName)*paramScale;
    sig{:,i} = out.simData.(sigName)(tind)*sigScale;
    
end





