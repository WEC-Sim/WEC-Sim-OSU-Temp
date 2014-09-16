function plotForcing(time, simData, tind, col)

Fe      = simData.Fe(tind); 
Fpto    = simData.Fpto(tind); 

plot(time, Fe*1e-6,      'color', col(3,:), 'linewidth', 2); hold on 
plot(time, -Fpto*1e-6,    'color', col(5,:), 'linewidth', 2);