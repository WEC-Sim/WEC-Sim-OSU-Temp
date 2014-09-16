function getPlots_Active(simData, wave, pto)

time = simData.time;
%     u = simData.u;

%%%%%%%%%%%%%%%%%%%%%%
figure
plot(time, simData.pA*1e-6); hold on
plot([0 time(end)],  [30 30], 'r')
plot([0 time(end)], -[30 30], 'r')
grid on
ylabel('\Delta P [MPa]')
xlabel('Time [s]')
title('Hydraulic Pressure')

%%%%%%%%%%%%%%%%%%%%%%
figure
subplot(2,1,1)
plot(time, simData.z, time, simData.zDot, time,interp1(wave.sig.eta(:,1), wave.zDotOpt, time) , time, interp1(wave.sig.eta(:,1), wave.sig.eta(:,2), time))
grid on
ylabel('m | m/s')
title('Kinematics')
xlabel('Time [s]')
legend('z','zDot', 'zDotOpt', 'eta')

% figure
subplot(2,1,2)
plot(time, simData.Fe, time, -simData.Fpto)
grid on
legend('F_e', 'F_{pto}')
ylabel('N')
title('System Forcing')

%%%%%%%%%%%%%%%%%%%%%%
figure
subplot(2,2,1)
plot(time, simData.omega); hold on
plot([0 time(end)], [pto.omega_r pto.omega_r], 'r')
grid on
ylabel('rad/s')
title('Gen. Speed')
subplot(2,2,2)
plot(time, simData.T_gen); hold on
plot([0 time(end)], [700,700],'r')
grid on
title('Gen. Torque')
ylabel('N-m')
subplot(2,2,3)
plot(time, simData.alpha); hold on
plot([0 time(end)], [1 1], 'r')
plot([0 time(end)], -[1 1], 'r')
xlabel('Time [s]')
ylim([-1.2, 1.2])
grid on
title('Swashplate Ratio')
subplot(2,2,4)
plot(time, simData.bg)
ylabel('kg-m^2/s')
xlabel('Time [s]')
title('Gen. Damping')


%%%%%%%%%%%%%%%%%%%%%
figure
subplot(2,1,1)
plot(time, simData.P_exc*1e-3, time, simData.P_hyd*1e-3, time, simData.P_gen*1e-3); hold on
plot([0 time(end)], [simData.P_genMean simData.P_genMean]*1e-3, 'g--')
grid on
title('System Power')
legend('Power Excitation', 'Power Hydraulic', 'Power Generator', 'Pmean_{gen}')
ylabel('kW')
subplot(2,1,2)
plot(time, (simData.P_hyd - simData.P_gen)*1e-3); hold on
plot([0, time(end)], [0 0], 'r')
grid on
%     ylim([-1, 1])
ylabel('kW')
title('Efficiency Measure')
legend( 'P_{hyd}-P_{gen}')

%%%%%%%%%%%%%%%%%%%%%


% subplot(2,1,2) 
% plot(time, simData.P_hyd*1e-3, time, simData.P_gen*1e-3) 
% legend('P_{hyd}', 'P_{gen}')



%%%%%%%%%%%%%%%%%%%%
figure
subplot(2,1,1)
plot(time, simData.Vdot_p, time, simData.Vdot_m)
grid on
legend('Vdot_{pump}', 'Vdot_{motor}')
title('Flow Rate')
ylabel('m^3/s')
subplot(2,1,2)
plot(time, simData.Vdot_leakageA, time, simData.Vdot_bp);
grid on
legend('Vdot_{leakA}', 'Vdot_{charge}')
ylabel('m^3/s')

