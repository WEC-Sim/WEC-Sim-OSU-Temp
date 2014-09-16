function plotDynamics(time, simData, tind, col)


z         = simData.z(tind);
zDot      = simData.zDot(tind);
zDotOpt   = simData.zDotOpt(tind); 
eta       = simData.eta(tind,2); 

plot(time, eta,     'k',                'linewidth', 2); hold on 
plot(time, z,       'color', col(3,:),  'linewidth', 2); 
plot(time, zDot,    'color', col(5,:),  'linewidth', 2);
plot(time, zDotOpt, 'color', col(1,:),  'linewidth', 2, 'linestyle', '--');
