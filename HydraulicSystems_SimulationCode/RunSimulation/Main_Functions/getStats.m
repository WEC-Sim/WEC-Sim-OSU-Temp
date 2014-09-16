function simData = getStats(simData, tspan, pto, wec, wave, con)

% Generate Statistics from wave run

P_genMean       = trapz(simData.time, simData.P_gen)/tspan(end); 
P_hydMean       = trapz(simData.time, simData.P_hyd)/tspan(end);
P_irrMean       = con.rho*con.g^2/64/pi*wave.Hs^2*wave.Te; 

eta       = P_genMean/P_hydMean;
Ploss     = P_hydMean - P_genMean;

fprintf('End time:                              %3.2f s\n', tspan(end))
fprintf('Average wave power:                    %3.2f s\n', P_irrMean*1e-3)
fprintf('Average generator power:               %3.2f kW\n', P_genMean*1e-3)
fprintf('Average hydraulic power:               %3.2f kW\n', P_hydMean*1e-3)
fprintf('Relative Efficiency:                   %3.2f \n', eta)
fprintf('Power loss (P_hyd - P_gen):            %3.2f kW\n', (P_hydMean - P_genMean)*1e-3)

simData.P_irrMean = P_irrMean; 
simData.P_genMean = P_genMean; 
simData.P_hydMean = P_hydMean;
% simData.eta = eta; 