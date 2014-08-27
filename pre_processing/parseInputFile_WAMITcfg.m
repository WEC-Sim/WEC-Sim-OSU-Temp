function [NUMHDR]= parseInputFile_WAMITcfg(fname)

fid = fopen(fname, 'r');
if fid == -1; error(['ERROR: Could not locate and open file ' fname]); end
readingInput = 'Reading';
while readingInput == 'Reading'
    temp = fgetl(fid);
    if temp == -1;
        break;
    end
    n=find(temp=='(')';
    len=length(n);
    if len==0;
        temp=temp;
    else        
        temp=temp(1:n-1);
    end
    n=find(temp=='=')';
    if temp(n-4:n-1) == 'PATH';
    else
      evalc(temp);
    end
end; fclose(fid);

