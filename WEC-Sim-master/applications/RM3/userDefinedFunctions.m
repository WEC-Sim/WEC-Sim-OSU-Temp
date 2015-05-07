%Example of user input MATLAB file for post processing

%Plot heave response for body 1
output.plotResponse(1,3);

%Plot heave response for body 2
output.plotResponse(2,3);

%Plot heave forces for body 1
output.plotForces(1,3);

%Plot pitch moments for body 2
output.plotForces(2,5);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% PTO-Sim Plots
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

time = output.ptos.time;
zRel = logsout.getElement('zRel').Values.Data;
zDotRel = logsout.getElement('zDotRel').Values.Data;
Fpto = logsout.getElement('Fpto_w_ramp').Values.Data;
HighPressure = logsout.getElement('HighPressure').Values.Data;
LowPressure = logsout.getElement('LowPressure').Values.Data;
TopPistonPressure = logsout.getElement('TopPistonPressure').Values.Data; 
BottomPistonPressure = logsout.getElement('BottomPistonPressure').Values.Data;
Vdotp = logsout.getElement('Vdotp').Values.Data;
Vdot1 = logsout.getElement('Vdot1').Values.Data;
Vdot2 = logsout.getElement('Vdot2').Values.Data;
Vdot3 = logsout.getElement('Vdot3').Values.Data;
Vdot4 = logsout.getElement('Vdot4').Values.Data;
Vdotm = logsout.getElement('Vdotm').Values.Data;
VdotC = logsout.getElement('VdotC').Values.Data;
VC = logsout.getElement('VC').Values.Data;
VdotD = logsout.getElement('VdotD').Values.Data;
VD = logsout.getElement('VD').Values.Data;
omega = logsout.getElement('omega').Values.Data;
Tgen = logsout.getElement('Tgen').Values.Data;
Pabs = logsout.getElement('Pabs').Values.Data;
Pabs = -Pabs;
Pgen = logsout.getElement('Pgen').Values.Data;
Pgen = -Pgen;
Tpu = logsout.getElement('Tpu').Values.Data;  
omegapu = logsout.getElement('omegapu').Values.Data;
genEff = logsout.getElement('genEff').Values.Data;
Pelec = logsout.getElement('Pelec').Values.Data;
Av1 = logsout.getElement('Av1').Values.Data;
Av2 = logsout.getElement('Av2').Values.Data;
Av3 = logsout.getElement('Av3').Values.Data;
Av4 = logsout.getElement('Av4').Values.Data;

PaccumC = HighPressure.*VdotC;
PaccumD = LowPressure.*VdotD;
Pfric = bf*omega.^2;
Pmotor = (HighPressure - LowPressure).*Vdotm;
Pmech = PaccumC + PaccumD + Pmotor;
Pvalve = Pabs - Pmech;

set(0,'DefaultFigureWindowStyle','docked')

f = figure;
plot(time,zRel,time,zDotRel);
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Position (m), Velocity (m/s)')
title('Relative Position and Velocity')
legend('zRel','zDotRel')
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','zRelzDotRel.eps')

f = figure;
plot(time,TopPistonPressure/1e6,time,BottomPistonPressure/1e6,time,HighPressure/1e6,time,LowPressure/1e6);
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Pressure (MPa)')
title('Piston Pump and Accumulators Pressures')
legend('TopPistonPressure','BottomPistonPressure','HighPressure','LowPressure');
%axis([200 300 5 35]) 
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','Pressures.eps')

f = figure;
plot(time,VC,time,VD)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Volume (m^3)')
title('Fluid Volume Inside Each Accumulator')
legend('High Pressure Accumulator','Low Pressure Accumulator')
grid on

f = figure;
plot(time,Vdot1.*(TopPistonPressure-HighPressure)/1e6+Vdot2.*(BottomPistonPressure-HighPressure)/1e6+Vdot3.*(LowPressure-BottomPistonPressure)/1e6+Vdot4.*(LowPressure-TopPistonPressure)/1e6)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (MW)')
title('Valves Power')
grid on

f = figure;
plot(time,Fpto/1e6);
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Force (MN)')
title('PTO Force')
grid on

f = figure;
plot(time,Vdotp,time,Vdotm)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Volumetric Flow (m^3/s)')
title('Piston and Motor Volumetric Flows')
legend('Vdot_{piston}','Vdot_{motor}')
grid on

f = figure;
plot(time,Vdot1,time,Vdot2,time,-Vdot3,time,-Vdot4)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Volumetric Flow (m^3/s)')
title('Valves Volumetric Flows')
legend('Vdot_1','Vdot_2','Vdot_3','Vdot_4')  
grid on
 
f = figure;
plot(time,Av1,time,Av2,time,-Av3,time,-Av4)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
title('Valve Area')
legend('Av1','Av2','Av3','Av4')
grid on

f = figure;
subplot(211)
plot(time,omega)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Speed (rad/s)')
title('Generator Speed') 
grid on
subplot(212)
plot(time,Tgen)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Generator Torque (N-m)')
title('Generator Torque')
grid on

f = figure;
plot(time,Pabs/1e3,time,Pmotor/1e3,time,Pelec/1e3)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Absorbed Power, Motor Power, and Electrical Power')
legend('Pabs','Pmotor','Pelec')
grid on

f = figure;
plot(time,zDotRel,time,Fpto/1e6)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Speed (m/s), Force (MN)')
title('Relative Velocity and PTO Force')
legend('zDotRel','F_{pto}')
grid on

