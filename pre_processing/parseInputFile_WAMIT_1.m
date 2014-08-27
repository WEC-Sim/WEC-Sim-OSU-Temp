function [hydro]= parseInputFile_WAMIT_1(fname, hydro)

fid = fopen(fname, 'r');
if fid == -1; error(['ERROR: Could not locate and open file ' fname]); end
readingInput = 'Reading';
size=hydro.WAMIT.NBODY*6;
k=0;
hydro.WAMIT.Fadm_InP(1:size,1:size) = 0.0;
hydro.WAMIT.Fdmp_InP(1:size,1:size) = 0.0;
hydro.WAMIT.Fadm_ZoP(1:size,1:size) = 0.0;
hydro.WAMIT.Fdmp_ZoP(1:size,1:size) = 0.0;
while strcmp(readingInput, 'Reading')
    temp = fgetl(fid);
    if temp == -1;
        break;
    end
    n0=strfind(temp, 'Wave period')';    
    n1=strfind(temp, 'Wave period = infinite')';
    n2=strfind(temp, 'Wave period = zero')';
    len0=length(n0);
    len1=length(n1);
    len2=length(n2);

% Added-mass for Wave period at infinity
    if len0~=0 && len1~=0;   
       readingData = 'Reading';
       while strcmp(readingData, 'Reading')
             temp = fgetl(fid); 
             n=strfind(temp, 'ADDED-MASS COEFFICIENTS')';
             if length(n)~=0
                temp = fgetl(fid);
                temp = fgetl(fid);
                readingAddedMass = 'Reading';
                while strcmp(readingAddedMass, 'Reading')             
                     temp = fgetl(fid);
                      A=textscan(temp(1:end), '%f %f %f');  
                      if A{1}>=1 && A{1}<=size
                         hydro.WAMIT.Fadm_InP(A{1},A{2})= A{3};
                         hydro.WAMIT.Fdmp_InP(A{1},A{2})= 0;
                      end
                      if A{1}==size && A{2}==size
                         readingAddedMass = 'StopLoop';   
                         readingData = 'StopLoop';        
                      end
                end
             end             
       end
    end

% Added-mass for Wave period at zero
    if len0~=0 && len2~=0;   
       readingData = 'Reading';
       while strcmp(readingData, 'Reading')
             temp = fgetl(fid); 
             n=strfind(temp, 'ADDED-MASS COEFFICIENTS')';
             if length(n)~=0
                temp = fgetl(fid);
                temp = fgetl(fid);
                readingAddedMass = 'Reading';
                while strcmp(readingAddedMass, 'Reading')             
                     temp = fgetl(fid);
                      A=textscan(temp(1:end), '%f %f %f');  
                      if A{1}>=1 && A{1}<=size
                         hydro.WAMIT.Fadm_ZoP(A{1},A{2})= A{3};
                         hydro.WAMIT.Fdmp_ZoP(A{1},A{2})= 0;
                      end
                      if A{1}==size && A{2}==size
                         readingAddedMass = 'StopLoop';   
                         readingData = 'StopLoop';        
                      end
                end
             end             
       end
    end    

% Added-mass and radiation damping for other cases   
    if len0~=0 && len1==0 && len2==0;   
       n=find(temp=='=')';
       A=textscan(temp(n+1:end), '%f');
       k=k+1;
       hydro.WAMIT.period(k) = A{1};
       readingData = 'Reading';
       while strcmp(readingData, 'Reading')
             temp = fgetl(fid); 
             n=strfind(temp, 'ADDED-MASS AND DAMPING COEFFICIENTS')';
             if length(n)~=0
                temp = fgetl(fid);
                temp = fgetl(fid);
                readingAddedMassDamping = 'Reading';
                while strcmp(readingAddedMassDamping, 'Reading')             
                     temp = fgetl(fid);
                      A=textscan(temp(1:end), '%f %f %f %f');  
                      if A{1}>=1 && A{1}<=size
                         hydro.WAMIT.Fadm(A{1},A{2},k)= A{3};
                         hydro.WAMIT.Fdmp(A{1},A{2},k)= A{4};
                      end
                      if A{1}==size && A{2}==size
                         readingAddedMassDamping = 'StopLoop';   
                         readingData = 'StopLoop';        
                      end
                end
             end             
       end
    end  
    
end; fclose(fid);
hydro.WAMIT.NPER=k;
