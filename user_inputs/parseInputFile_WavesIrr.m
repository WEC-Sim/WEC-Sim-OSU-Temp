function [NPERWaves, Hs, Tp] = parseInputFile_WavesIrr(inpFile)
fid = fopen(inpFile, 'r');
if fid == -1; error(['ERROR: Could not locate and open file ' inpFile]); end
readingInput = 'Reading';
while readingInput == 'Reading'
    temp = fgetl(fid);
    if temp == -1;
        break;
    end
    evalc(temp);    
end; fclose(fid);
