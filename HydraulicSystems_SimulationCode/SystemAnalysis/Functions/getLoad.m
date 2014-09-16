function  p = getLoad(simData, ti, tf)

timeTemp = simData.time; 
[time, tind] = getTwindow(timeTemp, ti, tf);

p.F       = simData.Fpto(tind); 
p.F_avg   = mean(abs(p.F)); 

p.T       = simData.T_gen(tind); 
p.T_avg   = mean(abs(p.T)); 

