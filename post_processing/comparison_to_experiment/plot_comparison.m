clc; clear all; %close all;

load('sampleData.mat');

%% Plot RAOS
RAOFig = figure(2);
set(RAOFig, 'defaultAxesFontSize', 14);

subplot(2,2,1)
scatter(TmeanIncident,rao8(:,2),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
xlabel('Wave Period (s)')
ylabel('Spar Heave RAO (m/m)')
set(gca,'YLim',[0 2.0],'XLim',[0.5 2.5])
legend('Experiment')

subplot(2,2,2)
scatter(TmeanIncident,rao8(:,6),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
xlabel('Wave Period (s)')
ylabel('Spar Pitch RAO (rad/m)')
set(gca,'YLim',[0 3.5],'XLim',[0.5 2.5])
legend('Experiment')

subplot(2,2,3)
scatter(TmeanIncident,rao8(:,7),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
xlabel('Wave Period (s)')
ylabel('Forward Float Pitch RAO (rad/m)')
set(gca,'YLim',[0 8.0],'XLim',[0.5 2.5])
legend('Experiment')

subplot(2,2,4)
scatter(TmeanIncident,rao8(:,8),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
xlabel('Wave Period (s)')
ylabel('Aft Float Pitch RAO (rad/m)')
set(gca,'YLim',[0 5.0],'XLim',[0.5 2.5])
legend('Experiment')

%% Plot Mechanical Power
powerFig = figure(3);
set(powerFig, 'defaultAxesFontSize', 14);

subplot(3,1,1)
scatter(TmeanIncident,mechPower(:,1),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
xlabel('Wave Period (s)')
title('Average Mechanical Power (W)')
ylabel('Total System')
set(gca,'YLim',[0 2.0],'XLim',[0.5 2.5])
legend('Experiment')

subplot(3,1,2)
scatter(TmeanIncident,mechPower(:,2),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
xlabel('Wave Period (s)')
ylabel('Forward Float')
set(gca,'YLim',[0 1.5],'XLim',[0.5 2.5])
legend('Experiment')

subplot(3,1,3)
scatter(TmeanIncident,mechPower(:,3),'Marker','v','MarkerEdgeColor','g','Linewidth',3)
xlabel('Wave Period (s)')
ylabel('Aft Float')
set(gca,'YLim',[0 0.5],'XLim',[0.5 2.5])
legend('Experiment')
