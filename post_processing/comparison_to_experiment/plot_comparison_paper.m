%%
clc; clear all; %close all;

%%
cd .\neutral_mass\CPT
SPE=csvread('SPE.csv');
SPSND=csvread('SPSND.csv');
SPSWD=csvread('SPSWD.csv');
SHE=csvread('SHE.csv');
SHSND=csvread('SHSND.csv');
SHSWD=csvread('SHSWD.csv');
APE=csvread('APE.csv');
APSND=csvread('APSND.csv');
APSWD=csvread('APSWD.csv');
FPE=csvread('FPE.csv');
FPSND=csvread('FPSND.csv');
FPSWD=csvread('FPSWD.csv');
cd ..

Period=5:1:15;
cd .\FS9
rao_a_04=csvread('RAOs_T=5');
rao_a_05=csvread('RAOs_T=5');
rao_a_06=csvread('RAOs_T=6');
rao_a_07=csvread('RAOs_T=7');
rao_a_08=csvread('RAOs_T=8');
rao_a_09=csvread('RAOs_T=9');
rao_a_10=csvread('RAOs_T=10');
rao_a_11=csvread('RAOs_T=11');
rao_a_12=csvread('RAOs_T=12');
rao_a_13=csvread('RAOs_T=13');
rao_a_14=csvread('RAOs_T=14');
rao_a_15=csvread('RAOs_T=15');
rao_a=[rao_a_05; rao_a_06; rao_a_07; rao_a_08; rao_a_09; rao_a_10; rao_a_11; rao_a_12; rao_a_13; rao_a_14; rao_a_15];

%% Plot RAOS
SparHeave = figure(5);
set(SparHeave, 'defaultAxesFontSize', 16);
% legend('Experiment','WEC-Sim','CPT Sim No Drag','Location','North')

% subplot(2,1,1)
scatter(SHE(:,1)/15,SHE(:,2)/max(rao_a(:,1)),'Marker','v','MarkerEdgeColor','g','MarkerFaceColor','g','Linewidth',2)
hold on
scatter(Period/15,rao_a(:,1)/max(rao_a(:,1)),'Marker','d','MarkerEdgeColor','r','MarkerFaceColor','r','Linewidth',2)
hold on
% scatter(SHSND(:,1),SHSND(:,2),'Marker','o','MarkerEdgeColor','b','MarkerFaceColor','b','Linewidth',2)
hold on
% legend('Experiment','WEC-Sim','Location','NorthWest')
title('Spar Heave','FontWeight','bold')
xlabel('Normalized Wave Period (s)','FontWeight','bold')
ylabel('Normalized RAO (m/m)','FontWeight','bold')
set(gca,'XLim',[.25 1])

SparPitch = figure(6);
set(SparPitch, 'defaultAxesFontSize', 16);
scatter(SPE(:,1)/15,SPE(:,2)/max(SPE(:,2)),'Marker','v','MarkerEdgeColor','g','MarkerFaceColor','g','Linewidth',2)
hold on
scatter(Period/15,rao_a(:,2)/max(SPE(:,2)),'Marker','d','MarkerEdgeColor','r','MarkerFaceColor','r','Linewidth',2)
hold on
% scatter(SPSND(:,1),SPSND(:,2),'Marker','o','MarkerEdgeColor','b','MarkerFaceColor','b','Linewidth',2)
hold on
% legend('Experiment','WEC-Sim','Location','NorthWest')
title('Spar Pitch','FontWeight','bold')
xlabel('Normalized Wave Period (s)','FontWeight','bold')
ylabel('Normalized RAO (deg/m)','FontWeight','bold')
set(gca,'XLim',[.25 1])

ForePitch = figure(7);
set(ForePitch, 'defaultAxesFontSize', 16);
% subplot(2,1,1)
scatter(FPE(:,1)/15,FPE(:,2)/max(rao_a(:,3)),'Marker','v','MarkerEdgeColor','g','MarkerFaceColor','g','Linewidth',2)
hold on
scatter(Period/15,rao_a(:,3)/max(rao_a(:,3)),'Marker','d','MarkerEdgeColor','r','MarkerFaceColor','r','Linewidth',2)
hold on
% scatter(FPSND(:,1),FPSND(:,2),'Marker','o','MarkerEdgeColor','b','MarkerFaceColor','b','Linewidth',2)
hold on
% legend('Experiment','WEC-Sim','Location','NorthWest')
title('Forward Float Relative Pitch','FontWeight','bold')
xlabel('Normalized Wave Period (s)','FontWeight','bold')
ylabel('Normalized RAO (deg/m)','FontWeight','bold')
set(gca,'XLim',[.25 1])

AftPitch = figure(8);
set(AftPitch, 'defaultAxesFontSize', 16);
scatter(APE(:,1)/15,APE(:,2)/max(rao_a(:,4)),'Marker','v','MarkerEdgeColor','g','MarkerFaceColor','g','Linewidth',2)
hold on
scatter(Period/15,rao_a(:,4)/max(rao_a(:,4)),'Marker','d','MarkerEdgeColor','r','MarkerFaceColor','r','Linewidth',2)
hold on
% scatter(APSND(:,1),APSND(:,2),'Marker','o','MarkerEdgeColor','b','MarkerFaceColor','b','Linewidth',2)
hold on
% legend('Experiment','WEC-Sim','Location','NorthWest')
title('Aft Float Relative Pitch','FontWeight','bold')
xlabel('Normalized Wave Period (s)','FontWeight','bold')
ylabel('Normalized RAO (deg/m)','FontWeight','bold')
set(gca,'XLim',[.25 1])

% %% Plot Mechanical Power
% powerFig = figure(3);
% set(powerFig, 'defaultAxesFontSize', 14);
% 
% subplot(3,1,1)
% scatter(TmeanIncident,mechPower(:,1),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
% xlabel('Wave Period (s)')
% title('Average Mechanical Power (W)')
% ylabel('Total System')
% set(gca,'YLim',[0 2.0],'XLim',[0.5 2.5])
% legend('Experiment')
% 
% subplot(3,1,2)
% scatter(TmeanIncident,mechPower(:,2),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
% xlabel('Wave Period (s)')
% ylabel('Forward Float')
% set(gca,'YLim',[0 1.5],'XLim',[0.5 2.5])
% legend('Experiment')
% 
% subplot(3,1,3)
% scatter(TmeanIncident,mechPower(:,3),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
% xlabel('Wave Period (s)')
% ylabel('Aft Float')
% set(gca,'YLim',[0 0.5],'XLim',[0.5 2.5])
% legend('Experiment')
