%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Copyright 2014 the National Renewable Energy Laboratory and Sandia Corporation
% 
% Licensed under the Apache License, Version 2.0 (the "License");
% you may not use this file except in compliance with the License.
% You may obtain a copy of the License at
% 
%     http://www.apache.org/licenses/LICENSE-2.0
% 
% Unless required by applicable law or agreed to in writing, software
% distributed under the License is distributed on an "AS IS" BASIS,
% WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
% See the License for the specific language governing permissions and
% limitations under the License.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

wecSim;                     % Run Simulation


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
Pgen = logsout.getElement('Pgen').Values.Data;
Tpu = logsout.getElement('Tpu').Values.Data;  
omegapu = logsout.getElement('omegapu').Values.Data;
genEff = logsout.getElement('genEff').Values.Data;
Pelec = logsout.getElement('Pelec').Values.Data;

Av1 = logsout.getElement('Av1').Values.Data;
Av2 = logsout.getElement('Av2').Values.Data;
Av3 = logsout.getElement('Av3').Values.Data;
Av4 = logsout.getElement('Av4').Values.Data;

delpApC = logsout.getElement('delpApC').Values.Data;
delpBpC = logsout.getElement('delpBpC').Values.Data;
delpDpB = logsout.getElement('delpDpB').Values.Data;
delpDpA = logsout.getElement('delpDpA').Values.Data;


%plot(time,delpApC,time,delpBpC,time,delpDpB,time,delpDpA)

%% Energy Storage Calculation
 
PaccumC = HighPressure.*VdotC;
PaccumD = LowPressure.*VdotD;
Pfric = bf*omega.^2;
Pmotor = (HighPressure - LowPressure).*Vdotm;
Pmech = PaccumC + PaccumD + Pmotor;
Pvalve = Pabs - Pmech;

% %% Power Calculation
% 
%          
% %start = 127568;          % between 200 and 300 seconds for variable step
% %start = 2000001;         % between 200 and 300 seconds for fixed step
% 
% % avgPabs=mean(Pabs(start:end))/1e3;
% % avgPmech = mean(Pmech(start:end))/1e3;
% % avgPelec = mean(Pelec(start:end))/1e3;
% 
% avgPabs = trapz(time(start:end),Pabs(start:end)/1e3)/time(end-(start-1));
% avgPvalve = trapz(time(start:end),Pvalve(start:end)/1e3)/time(end-(start-1));
% avgPaccumC = trapz(time(start:end),PaccumC(start:end)/1e3)/time(end-(start-1));
% avgPaccumD = trapz(time(start:end),PaccumD(start:end)/1e3)/time(end-(start-1));
% avgPmech = trapz(time(start:end),Pmech(start:end)/1e3)/time(end-(start-1));
% avgPelec= trapz(time(start:end),Pelec(start:end)/1e3)/time(end-(start-1));
% 
% Eff_abs2mech = avgPmech/avgPabs;
% Eff_abs2elec = avgPelec/avgPabs;
% Eff_mech2elec = avgPelec/avgPmech;
% 
% fprintf('Average Absorbed Power is %0.2f kW\n',avgPabs)
% fprintf('Average Rectifying Valve Power is %0.2f kW\n',avgPvalve)
% fprintf('Average Accumulator C Power is %0.2f kW\n',avgPaccumC)
% fprintf('Average Accumulator D Power is %0.2f kW\n',avgPaccumD)
% fprintf('Average Mechanical Power is %0.2f kW\n',avgPmech)
% fprintf('Average Electrical Power is %0.2f kW\n',avgPelec)
% fprintf('Efficiency from Absorbed to Mechanical Power is %0.2f \n',Eff_abs2mech)
% fprintf('Efficiency from Absorbed to Electrical Power is %0.2f \n',Eff_abs2elec)
% fprintf('Efficiency from Mechanical to Electrical Power is %0.2f \n',Eff_mech2elec)

% %% Normalization 
% 
% Fpto_n = Fpto/1e6;
% TopPistonPressure_n = TopPistonPressure/20e6;
% BottomPistonPressure_n = BottomPistonPressure/20e6;
% Vdot1_n = Vdot1*20;
% Vdot2_n = Vdot2*30;
% Vdot3_n = Vdot3*30;
% Vdot4_n = Vdot4*30;
% 
% 
% %% Normalized Power
% 
% maxPabs = max(Pabs(start:end));
% normPabs = Pabs(start:end)/maxPabs;
% normPmech = Pmech(start:end)/maxPabs;
% normPelecHDY = Pelec(start:end)/maxPabs;

%% Plots

omegaRated = 251.327*ones(length(time),1);
tauRated = 1989.44*ones(length(time),1);
PowerRated = 0.5e6*ones(length(time),1);

set(0,'DefaultFigureWindowStyle','docked')

f = figure;
plot(time,zRel,time,zDotRel);
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Position (m), Velocity (m/s)')
title('Relative Position, Relative Velocity')
legend('z','zDot')
%axis([200 300 -2 2]) 
grid on

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
plot(time,delpApC,time,delpBpC,time,delpDpB,time,delpDpA)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (sec)')
title('Pressure Differences')
legend('pApC','pBpC','pDpB','pDpA')
grid on

f = figure;
plot(time,VC,time,VD)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (sec)')
ylabel('Volume (m^3)')
title('High and Low Pressure Accumulator Volumes')
legend('High Accumulator','Low Accumulator')
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
%axis([200 300 -0.5 0.5]) 
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','ptoForce.eps') 


f = figure;
plot(time,Vdotp,time,Vdotm)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Volumetric Flow (m^3/s)')
title('Piston and Motor Volumetric Flows')
legend('Vdot_{piston}','Vdot_{motor}')
%axis([200 300 -0.05 0.05]) 
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','PistonAndMotorVolumetricFlow.eps') 

f = figure;
plot(time,Vdot1,time,Vdot2,time,-Vdot3,time,-Vdot4)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Volumetric Flow (m^3/s)')
title('Valves Volumetric Flows')
legend('Vdot_1','Vdot_2','Vdot_3','Vdot_4')
%axis([200 300 -0.05 0.05])  
grid on
% set(f,'PaperPosition',[0 0 3.8 3.0])
% print(f,'-depsc','ValvesVolumetricFlow.eps') 

f = figure;
plot(time,Av1,time,Av2,time,-Av3,time,-Av4)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (sec)')
title('Valve Area')
legend('Av1','Av2','Av3','Av4')
grid on

f = figure;
subplot(211)
plot(time,omegaRated,time,omega)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Speed (rad/s)')
title('Generator Speed')
legend('RatedSpeed','ActualSpeed')
%axis([200 300 150 250]) 
grid on
subplot(212)
plot(time,tauRated,time,Tgen)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Generator Torque (N-m)')
title('Generator Torque')
legend('RatedTorque','ActualTorque')
%axis([200 300 350 600]) 
grid on

f = figure;
plot(time,PaccumC/1e3,time,PaccumD/1e3)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Accumulators Power')
legend('HighPressureAccum','LowPressureAccum')
grid on

f = figure;
plot(time,Pmotor/1e3,time,Pmech/1e3)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Motor and Mechanical Power')
legend('Pmotor','Pmech')
grid on

f = figure;
subplot(211)
plot(time,Pabs/1e3,time,Pvalve/1e3,time,Pmech/1e3)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Pabs = Pvalve + Pmech')
legend('Pabs','Pvalve','Pmech')
grid on
subplot(212)
plot(time,Pabs/1e3,time,(Pvalve+Pmech)/1e3)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (kW)')
legend('Pabs','P_{mech+valve}')
grid on

f = figure;
plot(time,Pabs/1e3,time,PowerRated/1e3,time,Pmotor/1e3,time,Pelec/1e3)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (s)')
ylabel('Power (kW)')
title('Absorbed Power, Rated Power, Motor Power, and Electrical Power')
legend('Pabs','Prated','Pmotor','Pelec')
grid on

f = figure;
plot(time,output.bodies(1).forceExcitation(:,3)/1e6,'b',time,output.bodies(2).forceExcitation(:,3)/1e6,'r',time,Fpto/1e6,'k')
set(findall(gcf,'type','axes'),'fontsize',16)
title('Float Excitation Force, Spar Excitation Force, and PTO Force')
ylabel('Force (MN)') 
xlabel('Time (sec)')
legend('FloatF_e','SparF_e','PTO')
grid on

f = figure;
plot(time,output.bodies(1).forceExcitation(:,3)/1e6-output.bodies(2).forceExcitation(:,3)/1e6,time,Fpto/1e6)
set(findall(gcf,'type','axes'),'fontsize',16)
title('Relative Excitation Force vs. PTO Force')
ylabel('Force (MN)') 
xlabel('Time (sec)')
legend('Fe_{rel}','Fpto')
grid on

f = figure;
subplot(211)
plot(time,output.bodies(1).velocity(:,3),time,output.bodies(2).velocity(:,3),time,Fpto/1e6)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (sec)')
legend('V_{float}','V_{spar}','F_{pto}')
grid on
subplot(212)
plot(time,zDotRel,time,output.bodies(1).velocity(:,3)-output.bodies(2).velocity(:,3),time,Fpto/1e6)
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (sec)')
legend('zDot','V_{rel}','F_{pto}')
grid on

f = figure;
plot(time,output.bodies(1).acceleration(:,3),time,output.bodies(2).acceleration(:,3),time,output.bodies(1).acceleration(:,3)-output.bodies(2).acceleration(:,3))
set(findall(gcf,'type','axes'),'fontsize',16)
xlabel('Time (sec)')
legend('Acc_{float}','Acc_{spar}','Acc_{rel}')
grid on



% % Run the WEC-Sim RM3 Test Case for 1DOF w/PTO
% This script will run the RM3 in WEC-Sim for regular waves with Hs=2.5[m] 
% and Tp=8[s]. The RM3 WEC models has 2 bodies, restricted to heave motion
% only, and has PTO damping=1200[kN-s/m]. This script compares results from
% the latest WEC-Sim run, to a previous compile of WEC-Sim. 
% For more info reference Ruehl OMAE 2014.

% % Load Data and Run Simulation
% wecSim;                     % Run Simulation
% load('output_org.mat')    % Load Previous WEC-Sim Data
% 
% %% Post-Process Data
% Tshift=-2;
% % Body 1
% B1.WEC_Sim_new.time=output.bodies(1).time-Tshift;
% Hshift1=output.bodies(1).position(1,3);
% B1.WEC_Sim_new.heave=output.bodies(1).position(:,3)-Hshift1;
% %Body 2
% B2.WEC_Sim_new.time=output.bodies(2).time-Tshift;
% Hshift2=output.bodies(2).position(1,3);
% B2.WEC_Sim_new.heave=output.bodies(2).position(:,3)-Hshift2;
% % Relative Motion
% Rel.WEC_Sim_new.time=B1.WEC_Sim_new.time;
% Rel.WEC_Sim_new.heave=B1.WEC_Sim_new.heave-B2.WEC_Sim_new.heave;
% 
% clear h Tshift Hshift1 Hshift2 ans
% 
% %% Quantify Maximum Difference Between Saved and Current WEC-Sim Runs
% [B1_H_max,B1_H_I]=max(abs(B1.WEC_Sim_org.heave-B1.WEC_Sim_new.heave));
% [B2_H_max,B2_H_I]=max(abs(B2.WEC_Sim_org.heave-B2.WEC_Sim_new.heave));
% [Rel_H_max,Rel_H_I]=max(abs(Rel.WEC_Sim_org.heave-Rel.WEC_Sim_new.heave));
% 
% fprintf(['\nBody1_Heave Max Diff = ' num2str(B1_H_max) ...
%     ' m at time = ' num2str(B1.WEC_Sim_org.time(B1_H_I)) 's\n'])
% fprintf(['Body2_Heave Max Diff = ' num2str(B2_H_max) ...
%     ' m at time = ' num2str(B2.WEC_Sim_org.time(B2_H_I)) 's\n'])
% fprintf(['Relative_Heave Max Diff = ' num2str(Rel_H_max) ...
%     ' m at time = ' num2str(Rel.WEC_Sim_org.time(Rel_H_I)) 's\n'])
% 
% %% Plot Heave Comparisons
% h=figure('units','normalized','outerposition',[0 0 1 1]);
% % First Row = All simulations, all times
% % Second Row = All simulations, t=350-400s
% % Third Row = Original and New WEC-Sim runs only, t=350-400s
% 
% %First Column: Body 1 Heave
% subplot(2,3,1)
% plot(B1.WEC_Sim_org.time,B1.WEC_Sim_org.heave,'r-',...
%     B1.WEC_Sim_new.time,B1.WEC_Sim_new.heave,'k-')
% xlabel('time(s)')
% ylabel('Heave(m)')
% title('Float 1DOF 1200PTO')
% str1=['Max Diff = ' num2str(B1_H_max) ' m'];
% str2=['at time = ' num2str(B1.WEC_Sim_org.time(B1_H_I)) 's'];
% a=text(10,1.5,str1);set(a,'FontSize',12)
% a=text(10,1.2,str2);set(a,'FontSize',12)
% xlim([0 400])
% ylim([-2 2])
% 
% subplot(2,3,4)
% m=plot(B1.WEC_Sim_org.time(find(B1.WEC_Sim_org.time==350):end),...
%     B1.WEC_Sim_org.heave(find(B1.WEC_Sim_org.time==350):end),'r-',...
%     B1.WEC_Sim_new.time(find(B1.WEC_Sim_new.time==350):end),...
%     B1.WEC_Sim_new.heave(find(B1.WEC_Sim_new.time==350):end),'k-');
% a=get(m(1),'LineWidth')+1;
% set(m(1),'LineWidth',a)
% xlabel('time(s)')
% ylabel('Heave(m)')
% xlim([350 400])
% ylim([-2 2])
% 
% %Second Column: Body 2 Heave
% subplot(2,3,2)
% plot(B2.WEC_Sim_org.time,B2.WEC_Sim_org.heave,'r-',...
%     B2.WEC_Sim_new.time,B2.WEC_Sim_new.heave,'k-')
% xlabel('time(s)')
% ylabel('Heave(m)')
% title('Spar/Plate 1DOF 1200PTO')
% str1=['Max Diff = ' num2str(B2_H_max) ' m'];
% str2=['at time = ' num2str(B1.WEC_Sim_org.time(B2_H_I)) 's'];
% a=text(10,0.18,str1);set(a,'FontSize',12)
% a=text(10,0.15,str2);set(a,'FontSize',12)
% xlim([0 400])
% ylim([-0.2 0.2])
% 
% subplot(2,3,5)
% m=plot(B2.WEC_Sim_org.time(find(B2.WEC_Sim_org.time==350):end),...
%     B2.WEC_Sim_org.heave(find(B2.WEC_Sim_org.time==350):end),'r-',...
%     B2.WEC_Sim_new.time(find(B2.WEC_Sim_new.time==350):end),...
%     B2.WEC_Sim_new.heave(find(B2.WEC_Sim_new.time==350):end),'k-');
% a=get(m(1),'LineWidth')+1;
% set(m(1),'LineWidth',a)
% xlabel('time(s)')
% ylabel('Heave(m)')
% xlim([350 400])
% ylim([-0.2 0.2])
% 
% %Third Column: Relative Heave
% subplot(2,3,3)
% plot(Rel.WEC_Sim_org.time,Rel.WEC_Sim_org.heave,'r-',...
%     Rel.WEC_Sim_new.time,Rel.WEC_Sim_new.heave,'k-')
% xlabel('time(s)')
% ylabel('Heave(m)')
% title('Relative Motion 1DOF 1200PTO')
% str1=['Max Diff = ' num2str(Rel_H_max) ' m'];
% str2=['at time = ' num2str(Rel.WEC_Sim_org.time(Rel_H_I)) 's'];
% a=text(10,1.5,str1);set(a,'FontSize',12)
% a=text(10,1.2,str2);set(a,'FontSize',12)
% xlim([0 400])
% ylim([-2 2])
% l=legend('WEC-Sim Org','WEC-Sim New');
% set(l,'Position',[0.90 0.90 0.07 0.07],'Units','normalized',...
%     'FontSize',12);
% 
% subplot(2,3,6)
%     m=plot(Rel.WEC_Sim_org.time(find(Rel.WEC_Sim_org.time==350):end),...
%     Rel.WEC_Sim_org.heave(find(Rel.WEC_Sim_org.time==350):end),'r-',...
%     Rel.WEC_Sim_new.time(find(Rel.WEC_Sim_new.time==350):end),...
%     Rel.WEC_Sim_new.heave(find(Rel.WEC_Sim_new.time==350):end),'k-');
% a=get(m(1),'LineWidth')+1;
% set(m(1),'LineWidth',a)
% xlabel('time(s)')
% ylabel('Heave(m)')
% xlim([350 400])
% ylim([-2 2])
% 
% saveas(h,['.' filesep 'output' filesep 'test'],'fig')
% 
% %%
% test.B1=B1;
% test.B2=B2;
% test.Rel=Rel;
% clear h l m B1_H_Tolerance B2_H_Tolerance Rel_H_Tolerance str1 str2 ...
%     B1_H_max B1_H_I B2_H_max B2_H_I Rel_H_max Rel_H_I pf a B1 B2 Rel
