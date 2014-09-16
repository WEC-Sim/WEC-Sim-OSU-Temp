function plotTorque(time, simData, tind, col) 

T_gen = simData.T_gen(tind); 

plot(time, T_gen, 'color', col, 'linewidth', 2); hold on