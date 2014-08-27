function [vol,HGRes]= parseInputFile_WAMITout(fname)

fid = fopen(fname, 'r');
if fid == -1; error(['ERROR: Could not locate and open file ' fname]); end
readingInput = 'Reading';
k=0;
while readingInput == 'Reading'
    temp = fgetl(fid);
    if temp == -1;
        break;
    end
    n=strfind(temp, 'Volumes (VOLX,VOLY,VOLZ)')';
    len=length(n);
    if len~=0;
       n=find(temp==':')';
       k=k+1;
       A=textscan(temp(n+1:end), '%f %f %f');
       for ll=1:3
          vol(ll,k)=A{ll};
       end
    end
    n=strfind(temp, 'Hydrostatic and gravitational')';
    len=length(n);
    if len~=0;
       HGRes(1:6,1:6,k)=0.0;        
       temp = fgetl(fid);        
       n=find(temp==':')';
       A=textscan(temp(n+1:end), '%f %f %f');
       for ll=1:3
          HGRes(3,2+ll,k)=A{ll};
       end          
       temp = fgetl(fid);
       n=find(temp==':')';
       A=textscan(temp(n+1:end), '%f %f %f');
       for ll=1:3
          HGRes(4,3+ll,k)=A{ll};
       end
       temp = fgetl(fid);        
       n=find(temp==':')';
       A=textscan(temp(n+1:end), '%f %f %f');
       for ll=1:2
          HGRes(5,4+ll,k)=A{ll};
       end       
    end
    
end; fclose(fid);

