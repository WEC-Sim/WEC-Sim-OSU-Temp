function [waterDepth, NBODY, DOF, NPER, meshFile]= parseInputFile_WAMITpot(fname)

fid = fopen(fname, 'r');
if fid == -1; error(['ERROR: Could not locate and open file ' fname]); end
readingInput = 'Reading';
while readingInput == 'Reading'
    temp = fgetl(fid);
    if temp == -1;
        break;
    end
    n=strfind(temp, 'HBOT')';
    len=length(n);
    if len~=0;
       A=textscan(temp, '%f');
       waterDepth=A{1};
    end    
    n=strfind(temp, 'NPER')';
    len=length(n);
    if len~=0;
      A=textscan(temp, '%f');
      NPER=abs(A{1});
      temp = fgetl(fid);
    end
    n=strfind(temp, 'NBODY')';
    len=length(n);
    if len~=0;
       A=textscan(temp, '%f');
       NBODY=A{1};
       DOF(1:6,1:NBODY)=0;
       for i=1:NBODY
           temp = fgetl(fid);
%            meshFile=textscan(temp, '%s');
           meshFile{i}=strtrim(temp);
           temp = fgetl(fid);
           temp = fgetl(fid); 
           A=textscan(temp, '%f %f %f %f %f %f');
           for ll=1:6
              DOF(ll,i)=A{ll};
           end
%            DOF=DOF+length(find(B));
           temp = fgetl(fid);          
       end
     end   
end; fclose(fid);

