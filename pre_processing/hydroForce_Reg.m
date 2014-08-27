function [hydro, hydroForce] = hydroForce_Reg(HH, TT, hydro, system)

w=2*pi/TT;
waveAmp=HH/2;

% Calulate wave history
for i=1:system.numerical.maxIt+1;
    t = (i-1)*system.numerical.dt;
    hydroForce.waveAmpTime(i) = waveAmp*cos(w*t);
end

% Interpolate the hydrodynamic coefficients based on the given wave period
for i=1:hydro.WAMIT.NBODY
    for kd=1:6
        num=kd+(i-1)*6;

        tmp(1:hydro.WAMIT.NPER)=hydro.WAMIT.Fadm   (num,num,1:hydro.WAMIT.NPER);
        hydro.intp.Fadm(kd) = interp1(hydro.WAMIT.frequency,tmp,w,'spline');
        
        tmp(1:hydro.WAMIT.NPER)=hydro.WAMIT.Fdmp   (num,num,1:hydro.WAMIT.NPER);
        hydro.intp.Fdmp(kd) = interp1(hydro.WAMIT.frequency,tmp,w,'spline');
        
        tmp(1:hydro.WAMIT.NPER)=hydro.WAMIT.Fext.Re(num,1:hydro.WAMIT.NPER,1);
        hydro.intp.Fext.Re(num) = interp1(hydro.WAMIT.frequency,tmp,w,'spline');
        
        tmp(1:hydro.WAMIT.NPER)=hydro.WAMIT.Fext.Im(num,1:hydro.WAMIT.NPER,1);
        hydro.intp.Fext.Im(num) = interp1(hydro.WAMIT.frequency,tmp,w,'spline');        
    end
    hydro.intp.Fadm=hydro.intp.Fadm';
    hydro.intp.Fdmp=hydro.intp.Fdmp';
    evalc(['hydroForce.Fadm_' num2str(i) '=  hydro.intp.Fadm']);
    evalc(['hydroForce.Fdmp_' num2str(i) '=  hydro.intp.Fdmp']);
end

for j=1:hydro.WAMIT.NBODY
    temp = zeros(system.numerical.maxIt+1,6);
    for i=1:system.numerical.maxIt;
        t = (i-1)*system.numerical.dt;
        for kd=1:6
            num=kd+(j-1)*6;
            temp(i,kd) = waveAmp*(hydro.intp.Fext.Re(num)*cos(w*t)  ...
                       - hydro.intp.Fext.Im(num)*sin(w*t));
        end
    end
    evalc(['hydroForce.F_extTime_' num2str(j) '= temp']);    
    clear temp;
end


%  Calculate all the force coefficients
% for j=1:hydro.WAMIT.NBODY
%     for kd=1:6
%         num=kd+(j-1)*6;
%         hydro.td.C_Res(kd,j)= hydro.model.HGRes(kd,j);                     % Restoring
%         hydro.td.C_Dmp(kd,j)= hydro.td.Fdmp    (num);                      % Radiation damping
%         hydro.td.C_vis(kd,j)= hydro.visDmp.Cd  (kd,j) ...
%             / 2*hydro.model.area(kd,j)*hydro.properties.density;           % Viscous damping
%     end
% end
