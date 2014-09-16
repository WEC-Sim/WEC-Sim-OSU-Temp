function simData = getStats(simData, tspan, pto, wec, wave, con)

% tspan = [simData.time(1) simData.time(end)]; 

P_genMean = trapz(simData.time, simData.P_gen)/tspan(end); 
P_hydMean =     trapz(simData.time, simData.P_hyd)/tspan(end);
P_hydOptMean = trapz(simData.time, simData.P_hydOpt)/tspan(end);
P_excMean = trapz(simData.time, simData.P_exc)/tspan(end);
P_excOptMean = trapz(simData.time, simData.P_excOpt)/tspan(end);

eta       = P_hydMean/P_genMean;
Ploss     = P_hydMean - P_genMean;

% omegaMean = mean(simData.omega);

% fprintf('\nStart time:                  %3.2f s\n', tspan(1))
fprintf('End time:                              %3.2f s\n', tspan(end))
fprintf('Average excitation power:              %3.2f kW\n', P_excMean*1e-3)
fprintf('Average optimum excitation power:      %3.2f kW\n', P_excOptMean*1e-3)
fprintf('Average generator power:               %3.2f kW\n', P_genMean*1e-3)
fprintf('Average hydraulic power:               %3.2f kW\n', P_hydMean*1e-3)
fprintf('Average optimum hydraulic power:       %3.2f kW\n', P_hydOptMean*1e-3)
fprintf('Relative Efficiency:                   %3.2f \n', eta)
fprintf('Power loss (P_hyd - P_gen):            %3.2f kW\n', (P_hydMean - P_genMean)*1e-3)

simData.P_genMean       = P_genMean; 
simData.P_hydMean       = P_hydMean; 
simData.P_hydOptMean    = P_hydOptMean; 
simData.P_excMean       = P_excMean;
simData.P_excOptMean    = P_excOptMean;
% fprintf('Average excitation power:    %3.2f kW\n', P_excMean)


% fprintf('Average speed:     %3.2f rad/s \n', omegaMean)