close all;
latest1=load('post_processing/WEC_Sim_Driver/aft_disp.mat');
latest2=load('post_processing/WEC_Sim_Driver/spar_disp.mat');
latest3=load('post_processing/WEC_Sim_Driver/fwd_disp.mat');
Tues8Jun1=load('post_processing/WEC_Sim_Driver_625/aft_disp.mat');
Tues8Jun2=load('post_processing/WEC_Sim_Driver_625/spar_disp.mat');
Tues8Jun3=load('post_processing/WEC_Sim_Driver_625/fwd_disp.mat');

figure(1); hold on
subplot(3,1,1)
plot(latest1.aft_disp.time,latest1.aft_disp.data(:,7),'k',Tues8Jun1.aft_disp.time, Tues8Jun1.aft_disp.data(:,7),'bx')
legend('AF New',' AF Tues25Jun') 
subplot(3,1,2)
plot(latest2.spar_disp.time,latest2.spar_disp.data(:,7),'r',Tues8Jun2.spar_disp.time, Tues8Jun2.spar_disp.data(:,7),'mx')
legend('S New',' S Tues25Jun') 
subplot(3,1,3)
plot(latest3.fwd_disp.time,latest3.fwd_disp.data(:,7),'g',Tues8Jun3.fwd_disp.time, Tues8Jun3.fwd_disp.data(:,7),'yx')
legend('FF New',' FF Tues25Jun') 