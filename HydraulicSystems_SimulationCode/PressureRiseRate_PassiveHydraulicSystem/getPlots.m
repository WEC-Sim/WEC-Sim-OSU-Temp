function getPlots(simData, wave, pto)

time = simData.time;
%     u = simData.u;

%%%%%%%%%%%%%%%%%%%%%%
figure
subplot(2,2,1)
plot(time, simData.pA*1e-6, time, simData.pB*1e-6); hold on; 
% plot([time(1) time(end)], [pto.pA1 pto.pA1]*1e-6, 'r:') 
% plot([time(1) time(end)], [pto.pA2 pto.pA2]*1e-6, 'r:') 
% plot([time(1) time(end)], [pto.pB1 pto.pB1]*1e-6, 'g:') 
% plot([time(1) time(end)], [pto.pB2 pto.pB2]*1e-6, 'g:') 
plot([time(1) time(end)], [pto.pAeq pto.pAeq]*1e-6, 'c:')
ylabel('\Delta P [MPa]')
xlabel('Time [s]')
legend('pA', 'pB')
title('Hydraulic Pressure')
grid on

subplot(2,2,3)
plot(time, simData.pC*1e-6, time, simData.pD*1e-6); hold on; 
plot([time(1) time(end)], [pto.pC1 pto.pC1]*1e-6, 'r:') 
plot([time(1) time(end)], [pto.pC2 pto.pC2]*1e-6, 'r:') 
plot([time(1) time(end)], [pto.pD1 pto.pD1]*1e-6, 'g:') 
plot([time(1) time(end)], [pto.pD2 pto.pD2]*1e-6, 'g:') 
plot([time(1) time(end)], [pto.pDeq pto.pDeq]*1e-6, 'c:')
ylabel('\Delta P [MPa]')
xlabel('Time [s]')
legend('pC', 'pD')
grid on

subplot(2,2,2)
plot(time, simData.vA, time, simData.vB); 
ylabel('V [m^3]')
xlabel('Time [s]')
legend('vA', 'vB')
title('Accumulator Volume')
grid on

subplot(2,2,4)
plot(time, simData.vC, time, simData.vD);
ylabel('V [m^3]')
xlabel('Time [s]')
legend('vC', 'vD')
grid on



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
plot(time, simData.Fe, time, simData.Fpto)
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
plot(time, simData.u); hold on
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


%%%%%%%%%%%%%%%%%%%%
figure
subplot(2,1,1)
plot(time, simData.Vdot_p, time, simData.Vdot_m)
grid on
legend('Vdot_{pump}', 'Vdot_{motor}')
title('Flow Rate')
ylabel('m^3/s')
subplot(2,1,2)
plot(time, simData.Vdot_1, time, simData.Vdot_2, time, -simData.Vdot_3, time, -simData.Vdot_4);
grid on
legend('Vdot_{1}', 'Vdot_{2}','Vdot_{3}', 'Vdot_{4}')
ylabel('m^3/s')

