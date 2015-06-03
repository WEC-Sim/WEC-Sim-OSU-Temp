% wecSimStartup.m
% Copy the code in this file and place it in you 'startup.m' file

% Set the wecSimPath variable to the location of the WEC-Sim source directory
wecSimPath = 'C:\Controls\WEC-Sim-master'; % Make sure you add the correct path
ptoSimPath = 'C:\Controls\WEC-Sim-master'; % Make sure you add the correct path
% Add the source folder to the MATLAB path
folderToAdd = 'source';
addpath(genpath([wecSimPath filesep folderToAdd]));
addpath(genpath([ptoSimPath filesep folderToAdd]));
% Clear unneeded variables
clear wecSimPath ptoSimPath folderToAdd


