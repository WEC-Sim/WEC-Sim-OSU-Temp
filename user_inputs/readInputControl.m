function [hydro, system] = readInputControl(inpFile, hydro)

% Read Numerical Settings
[system.numerical.dt, system.numerical.maxIt] = parseInputFile_numericalSettings(inpFile);

% Read wave property
[hydro.waves.RegIregCon] = parseInputFile_WavesInput(inpFile);
if strcmp (hydro.waves.RegIregCon, 'Regular')
   [hydro.waves.H, hydro.waves.T]        = parseInputFile_WavesReg(inpFile); 
   hydro.waves.numHeight = length(hydro.waves.H);
   hydro.waves.numPeriod = length(hydro.waves.T);
elseif strcmp ( hydro.waves.RegIregCon,'Irregular')
   [hydro.waves.NPERWaves, hydro.waves.H, hydro.waves.T] = parseInputFile_WavesIrr(inpFile);
   hydro.waves.numHeight = length(hydro.waves.H);
   hydro.waves.numPeriod = length(hydro.waves.T);
end

bodyGeometry;
