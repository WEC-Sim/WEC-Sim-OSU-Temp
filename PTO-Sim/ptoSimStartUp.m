% Add PTO-Sim files to MATLAB path
ptoSimPath = 'Y:\MATLAB\PTO-Sim'; % Set this variable to the location of the PTO-Sim source directory. E.g. in Windows ptoSimPath = 'C:\Users\rso\PTO-Sim', in OSX/Linux ptoSimPath = '/home/rso/PTO-Sim'
fprintf('Adding PTO-Sim to Path\n');
addpath(ptoSimPath);
folderToAdd = 'Source';
addpath(genpath([ptoSimPath filesep folderToAdd]));
clear ptoSimPath folderToAdd