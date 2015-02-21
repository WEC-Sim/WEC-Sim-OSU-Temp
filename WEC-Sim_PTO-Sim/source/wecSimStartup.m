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

% Add WEC-Sim files to MATLAB path
wecSimPath = 'Z:\Windows.Documents\My Documents\MATLAB\WEC-Sim-1.0.1'; % Set this variable to the location of the WEC-Sim source directory. E.g. in Windows wecSimPath = 'C:\Users\mlawson\WEC-Sim', in OSX/Linux wecSimPath = '/home/mlawson/WEC-Sim'
ptoSimPath = 'Z:\Windows.Documents\My Documents\MATLAB\WEC-Sim-1.0.1';
fprintf('Adding WEC-Sim to Path\n');
fprintf('Adding PTO-Sim to Path\n');
addpath(wecSimPath);
addpath(ptoSimPath);
folderToAdd = 'source';
addpath(genpath([wecSimPath filesep folderToAdd]));
addpath(genpath([ptoSimPath filesep folderToAdd]));
clear wecSimPath ptoSimPath folderToAdd