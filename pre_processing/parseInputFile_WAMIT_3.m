function [hydro]= parseInputFile_WAMIT_3(fname, hydro)

fid = fopen(fname, 'r');
if fid == -1; error(['ERROR: Could not locate and open file ' fname]); end
readingInput = 'Reading';
size=hydro.WAMIT.NBODY*6;
k=0;
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

% DIFFRACTION EXCITING FORCES AND MOMENTS
    if len0~=0 && len1==0 && len2==0;   
       n=find(temp=='=')';
       A=textscan(temp(n+1:end), '%f');
       k=k+1; kd=0;
       hydro.WAMIT.period(k) = A{1};
       readingData = 'Reading';
       while strcmp(readingData, 'Reading')
             temp = fgetl(fid); 
             n=strfind(temp, 'DIFFRACTION EXCITING FORCES AND MOMENTS')';
             if length(n)~=0
                temp = fgetl(fid);   
                temp = fgetl(fid);   
                n1=strfind(temp, 'Wave Heading (deg)')'; 
                if length(n1)~=0
                   n=find(temp==':')';
                   A=textscan(temp(n+1:end), '%f');
                   kd=kd+1;
                   hydro.WAMIT.WaveDirection(kd) = A{1};         
                   temp = fgetl(fid);   
                   temp = fgetl(fid);
                   temp = fgetl(fid);
                   readingDiffractionExcitation = 'Reading';
                   while strcmp(readingDiffractionExcitation, 'Reading')             
                         temp = fgetl(fid);
                         A=textscan(temp(1:end), '%f %f %f');  
                         if A{1}>=1 && A{1}<=size
                            hydro.WAMIT.Fext.Mag(A{1},k,kd)= A{2};
                            hydro.WAMIT.Fext.Pha(A{1},k,kd)= A{3};
                            hydro.WAMIT.Fext.Re(A{1},k,kd)= hydro.WAMIT.Fext.Mag(A{1},k,kd) ...
                            *cos(hydro.WAMIT.Fext.Pha(A{1},k,kd)*pi/180);
                            hydro.WAMIT.Fext.Im(A{1},k,kd)= hydro.WAMIT.Fext.Mag(A{1},k,kd) ...
                            *sin(hydro.WAMIT.Fext.Pha(A{1},k,kd)*pi/180);
                         end
                         if A{1}==size
                            readingDiffractionExcitation = 'StopLoop';   
                            readingData = 'StopLoop';        
                         end
                   end
                end
             end             
       end
    end 
    
end; fclose(fid);

