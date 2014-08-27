function [IOPTN]= parseInputFile_WAMITfrc(fname)

fid = fopen(fname, 'r');
if fid == -1; error(['ERROR: Could not locate and open file ' fname]); end
readingInput = 'Reading';
while readingInput == 'Reading'
    temp = fgetl(fid);
    if temp == -1;
        break;
    end
    n=strfind(temp, 'IOPTN(1-9)')';
    len=length(n);
    if len~=0;
       A=textscan(temp(1:n), '%f %f %f %f %f %f %f %f %f');
       for ll=1:9
          IOPTN(ll)=A{ll};
       end
     end        
end; fclose(fid);

