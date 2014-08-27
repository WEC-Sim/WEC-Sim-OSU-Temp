function [hydro,hydroForce, system] = hydroForce(HH, TT, hydro, system)

CPUTime_tmp = cputime;
disp('Calculate Hydrodynamic Loads')

if strcmp (hydro.waves.RegIregCon, 'Regular')
    [hydro, hydroForce] = hydroForce_Reg(HH, TT, hydro, system);
else
    [hydro, hydroForce] = hydroForce_Irr(HH, TT, hydro, system);
end
for i=1:hydro.WAMIT.NBODY
    for j=1:6
        temp(j)=hydro.model.HGRes(j,j,i);
    end
    temp=temp';
    evalc(['hydroForce.HGRes_' num2str(i) '= temp']); 
end
clear temp
    
system.CPUTime.hydroForce =cputime-CPUTime_tmp;

