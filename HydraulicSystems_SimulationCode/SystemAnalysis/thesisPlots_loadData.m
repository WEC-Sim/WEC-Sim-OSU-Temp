function data = thesisPlots_loadData(analysisPath, paramName, nameSys, nameWave, varNum)


%% Load Data
for i = 1:length(paramName)
    
    fnames = dir([analysisPath, nameSys '_' nameWave '_' paramName{i} '_' varNum '.mat']); 
    
    for j = 1:length(fnames)
        
        data.(paramName{i})(j) = load([analysisPath fnames(j).name], varName);
        
    end
    
end





