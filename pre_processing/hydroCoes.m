% Read Data From WAMIT from *.out file
function [hydro] = hydroCoes(inpFile)

% Read WAMIT file directories and file names
[hydro.WAMIT, hydro.properties.density, hydro.properties.g] = parseInputFile(inpFile);

% Read WAMIT ouput name.out file: to displacement volume
fname=[hydro.WAMIT.fileDir,hydro.WAMIT.fileName,'.out'];
[hydro.model.vol, hydro.model.HGRes] = parseInputFile_WAMITout(fname);
hydro.model.HGRes=hydro.model.HGRes.*(hydro.properties.density*hydro.properties.g);

% Read WAMIT name.cfg file
fname=[hydro.WAMIT.fileDir,hydro.WAMIT.fileName,'.cfg'];
[hydro.WAMIT.NUMHDR] = parseInputFile_WAMITcfg(fname);

% Read WAMIT name.pot file
fname=[hydro.WAMIT.fileDir,hydro.WAMIT.fileName,'.pot'];
[hydro.WAMIT.waterDepth, hydro.WAMIT.NBODY, hydro.model.DOF, hydro.WAMIT.NPER, hydro.WAMIT.meshFile] = parseInputFile_WAMITpot(fname);

% Read WAMIT frc file
fname=[hydro.WAMIT.fileDir,hydro.WAMIT.fileName,'.frc'];
[hydro.WAMIT.IOPTN] = parseInputFile_WAMITfrc(fname);

% Read WAMIT gdf file(s)
[hydro.WAMIT.NPanel, hydro.WAMIT.NVertices, hydro.WAMIT.points, hydro.WAMIT.TotNumV] = parseInputFile_WAMITgdf(hydro);

% Read WAMIT .5p (pressure) file
[hydro]=pressureDistribution(hydro);

% Read WAMIT ouput name.1 file: to obatin added-mass and radiation damping coefficents
fname=[hydro.WAMIT.fileDir,hydro.WAMIT.fileName,'.out'];
[hydro] = parseInputFile_WAMIT_1(fname, hydro);
hydro.WAMIT.frequency=2*pi./hydro.WAMIT.period;
hydro.WAMIT.Fadm    =hydro.WAMIT.Fadm    .*hydro.properties.density;
hydro.WAMIT.Fadm_InP=hydro.WAMIT.Fadm_InP.*hydro.properties.density;
hydro.WAMIT.Fadm_ZoP=hydro.WAMIT.Fadm_ZoP.*hydro.properties.density;
hydro.WAMIT.Fdmp    =hydro.WAMIT.Fdmp    .*hydro.properties.density;
for i=1:hydro.WAMIT.NPER
    hydro.WAMIT.Fdmp(:,:,i)=hydro.WAMIT.Fdmp(:,:,i)*hydro.WAMIT.frequency(i);
end

% Read WAMIT ouput name.3 file: to obatin wave excitaion force
fname=[hydro.WAMIT.fileDir,hydro.WAMIT.fileName,'.out'];
[hydro] = parseInputFile_WAMIT_3(fname, hydro);
hydro.WAMIT.Fext.Re=hydro.WAMIT.Fext.Re.*(hydro.properties.density*hydro.properties.g);
hydro.WAMIT.Fext.Im=hydro.WAMIT.Fext.Im.*(hydro.properties.density*hydro.properties.g);






