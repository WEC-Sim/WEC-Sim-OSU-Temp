function [hydro, hydroForce] = hydroForce_Irr(HH, TT, hydro, system)

string=['Hs=',num2str(HH),' m, Tp=',num2str(TT),' sec'];
disp(string);

hydro.waves.WFQSt=min(hydro.WAMIT.frequency);
hydro.waves.WFQEd=max(hydro.WAMIT.frequency);
hydro.intp.df  = (hydro.waves.WFQEd-hydro.waves.WFQSt)/(hydro.waves.NPERWaves-1);
hydro.intp.frequency = [hydro.waves.WFQSt:hydro.intp.df:hydro.waves.WFQEd]';
hydro.intp.period    = 2*pi./hydro.intp.frequency;

%call JONSWAP frequency from WAFO
IrrSeaStates = bretschneider(linspace(hydro.waves.WFQSt,hydro.waves.WFQEd,400), [HH TT], []);

for i=1:hydro.waves.NPERWaves
    hydro.waves.Sf(i) = interp1(IrrSeaStates.w, IrrSeaStates.S, hydro.intp.frequency(i));
end

phaseRand = [4.22399847844665,2.71126472429284,4.36306844257805,1.61342499504952,0.0613154055763440,3.34443317135020,1.75547149102146,5.94533939780669,5.69535101392752,2.46730995811658,0.156170040100613,4.21876181492381,5.26009823580331,6.10411225336761,0.357719869262089,2.82946796363992,3.65976884173790,4.31427262739708,4.52032930061494,4.08432650156559,4.56733882586942,2.34895416112916,3.65418800016197,0.729594133387073,0.362253035280110,6.15604645977144,1.78960025574677,3.73833377242993,6.04543605319071,1.16727925504212,1.21290493544750,2.14661321859088,5.86157035210292,2.45463652606772,1.71667120538135,0.954711659562535,2.49510844607674,2.35445069861814,0.823818000847767,2.73344144670666,0.574994187643745,3.86181507198343,0.0689836713677969,3.60190121730856,4.96201904058849,1.47885305085981,2.81499088096413,3.57738297173835,0.385796640041485,3.11827503436905,4.03578564452396,1.39025358451699,5.25938075984588,6.10144562636562,5.31791769234891,3.17928834669236,1.75222714247844,4.69113435827820,1.48867750828240,6.01517780736698,3.89720874531453,3.77155829310962,1.08450606870569,0.567665297653110,1.60385972112850,5.39455774718524,5.72440312376442,4.39592860663961,4.55645511810884,1.44441683300255,3.61945061290835,5.09332659897271,2.53742271863267,6.21054708070880,0.565479231989191,2.01653198080346,3.21327713034896,0.380801031943120,4.55963169882091,3.49694290199104,3.32606636148025,5.21493342216815,5.39574214528769,4.95761493790593,1.99700397330866,2.84130322928066,4.72638772906732,0.690281455394396,0.689531637924302,1.69572907043529,3.29639366019180,6.11134695587741,4.46362941343256,1.95947382524881,1.83127914210897,5.34295272804458,5.72804969985426,4.01669049579534,1.60453890393460,0.557103903339577,5.26691519127509,3.67389543738963,5.95714287584891,0.383456071215277,3.67340964721115,1.79138693476848,5.20079463048995,1.20000319806042,2.78049775649990,2.47187739648414,5.19351748041847,4.25290650914686,1.30440833534219,1.99871094149172,0.840759217128834,4.21892576148471,3.58764273587606,1.06667793490062,0.927748609519976,2.99129709086428,5.70577576081074,3.46941801485243,0.206967450146096,0.338430747981581,5.05836144903186,2.83607185510303,2.40423716741880,4.96147771692994,2.28888190603955,3.34485328986316,4.47147095877732,5.47564845342353,2.06521773868151,4.08481202511192,6.12507616203847,0.477317008308516,3.68835020564727,2.60052556164959,1.94236145268685,1.65771817325497,4.76746904833547,6.25312643010477,1.17226295656833,4.90808047403049,1.23023499756259,6.23517531973194,5.04075810765781,2.66549503057759,4.57958674667447,3.13124790749229,5.08303576051633,2.24001169272637,0.460202071433729,3.71330882845162,5.71887880480472,1.21746728315394,2.71664695506661,4.70710940241076,0.246203390773468,5.94593527176268,4.79830100672915,3.51117307231168,1.15511928749599,3.12870467825453,3.25371986677818,6.24701307624469,5.37119153501307,6.04696229357000,4.26591217204618,2.53527399756212,5.87464685679413,3.01269025213769,1.45638964872917,2.48996506681517,4.43013243205196,3.50952991914326,4.75405090282048,6.25479196068998,6.04713485908465,3.36192577410060,6.05617463866756,0.726498825201410,0.323259160103493,1.91228082347932,3.64545280134788,3.33614804556655,5.66245744646957,3.39637848921936,2.71421422712117,3.40967724215143,4.47623424035392,0.104770311347506,5.03233431835919,0.895412496497242,3.00634377800377,1.61374412374574,2.31907147622646,4.15799158046454,1.06568360466431,1.75165166109890;];

%  Calulate wave history
for i=1:system.numerical.maxIt+1;
    hydroForce.waveAmpTime(i) = 0;
    t = (i-1)*system.numerical.dt;
    for j=1:hydro.waves.NPERWaves
        w = hydro.intp.frequency(j);
        tmp=sqrt(2*hydro.waves.Sf(j)*hydro.intp.df);
        hydroForce.waveAmpTime(i) = hydroForce.waveAmpTime(i) ...
            + tmp*real(exp(sqrt(-1)*(w*t + phaseRand(j))));
    end
end

%  Interpolate the hydrodynamic coefficients based on the given wave period
%  *** NEED TO UPDATE DIRECTIONAL WAVE CAPABILITY ***
for i=1:hydro.WAMIT.NBODY
    for j = 1:hydro.waves.NPERWaves
        w = hydro.intp.frequency(j);
        for kd=1:6
            num=kd+(i-1)*6;
            
            tmp(1:hydro.WAMIT.NPER)= hydro.WAMIT.Fadm   (num,num,1:hydro.WAMIT.NPER);
            hydro.intp.Fadm(j,num) = interp1(hydro.WAMIT.frequency,tmp,w,'spline','extrap');

            tmp(1:hydro.WAMIT.NPER)= hydro.WAMIT.Fdmp   (num,num,1:hydro.WAMIT.NPER);
            hydro.intp.Fdmp(j,num) = interp1(hydro.WAMIT.frequency,tmp,w,'spline','extrap');

            tmp(1:hydro.WAMIT.NPER)=hydro.WAMIT.Fext.Re(num,1:hydro.WAMIT.NPER,1);
            hydro.intp.Fext_Re (j,num) = interp1(hydro.WAMIT.frequency,tmp,w,'spline','extrap');

            tmp(1:hydro.WAMIT.NPER)=hydro.WAMIT.Fext.Im(num,1:hydro.WAMIT.NPER,1);
            hydro.intp.Fext_Im (j,num) = interp1(hydro.WAMIT.frequency,tmp,w,'spline','extrap');

%             hydro.intp.Fadm(num)       = hydro.WAMIT.Fadm_ZoP(num,num);
%             hydro.intp.Fadm(j,num)     = hydro.intp.Fadm_tmp;
%             hydro.intp.Fdmp(j,num)     = hydro.intp.Fdmp_tmp;
%             hydro.intp.Fext.Re(j,num)  = hydro.intp.Fext_Re;
%             hydro.intp.Fext.Im(j,num)  = hydro.intp.Fext_Im;
        end
    end
    for kd=1:6
        num=kd+(i-1)*6;
        Adm_tmp(kd)=hydro.WAMIT.Fadm_ZoP(num,num);
        Dmp_tmp(kd)=hydro.WAMIT.Fdmp_ZoP(num,num);
    end
    Adm_tmp=Adm_tmp';
    Dmp_tmp=Dmp_tmp';
    evalc(['hydroForce.Fadm_' num2str(i) '=  Adm_tmp']);
    evalc(['hydroForce.Fdmp_' num2str(i) '=  Dmp_tmp']);
end

%  Calculate wave excitation force
for j=1:hydro.WAMIT.NBODY
    temp = zeros(system.numerical.maxIt+1,6);    
    for i=1:system.numerical.maxIt+1;
        t = (i-1)*system.numerical.dt;
        for kd=1:6
            num=kd+(j-1)*6;
            F_ext=0;
            for k=1:hydro.waves.NPERWaves
                w  = hydro.intp.frequency(k);
                tmp= sqrt(2*hydro.waves.Sf(k)*hydro.intp.df);
                F_ext = F_ext + tmp*(hydro.intp.Fext_Re(k,num)*cos(w*t+phaseRand(k)) ...
                    -hydro.intp.Fext_Im(k,num)*sin(w*t+phaseRand(k)));
            end
            temp(i,kd) = F_ext;
        end
    end
    evalc(['hydroForce.F_extTime_' num2str(j) '= temp']);    
    clear temp;    
end

% Impulse Response calculation
hydro.CI.time = 100;
hydro.CI.kt   = hydro.CI.time/system.numerical.dt;
for i=1:hydro.WAMIT.NBODY
    tempS = zeros(hydro.CI.kt+1,6); 
    tempC = zeros(hydro.CI.kt+1,6); 
    for kt=1:hydro.CI.kt;
        dt=system.numerical.dt;
        t = dt*(kt-1);
        for kd=1:6
            num=kd+(i-1)*6;
            tmp=0*(hydro.WAMIT.Fadm_InP(num,num)-hydro.WAMIT.Fadm_ZoP(num,num))*sin(0*t);
            for k=1:1:hydro.waves.NPERWaves
                tmp=tmp+2*hydro.intp.frequency(k)*(hydro.intp.Fadm(k,num)-hydro.WAMIT.Fadm_ZoP(num,num))*sin(hydro.intp.frequency(k)*t);
            end
            tempS(kt,kd) =-2./pi.*tmp*(hydro.intp.frequency(2)-hydro.intp.frequency(1))/2;
            tmp=0*cos(0*t);
            for k=1:1:hydro.waves.NPERWaves
                tmp= tmp+2*hydro.intp.Fdmp(k,num)*cos(hydro.intp.frequency(k)*t);
            end
            tempC(kt,kd) = 2./pi.*tmp*(hydro.intp.frequency(2)-hydro.intp.frequency(1))/2;
        end
    end
    evalc(['hydroForce.IRKS_' num2str(j) '= tempS']);    
    evalc(['hydroForce.IRKC_' num2str(j) '= tempC']);    
    clear tempS;
    clear tempC;    
end; clear tmp;

% trapz(system.Res.time(maxIt/2+1:maxIt),system.Res.PowerTime(maxIt/2+1:maxIt))

%  Calculate all the force coefficients
% for i=1:hydro.WAMIT.NBODY
%     for kd=1:6
%         hydro.td.C_Res(kd,i)= hydro.model.HGRes(kd,i);                     % Restoring
%         hydro.td.C_Dmp(kd,i)= 0;                                           % Radiation damping
%         hydro.td.C_vis(kd,i)= hydro.visDmp.Cd(kd,i) ...
%             / 2*hydro.model.area(kd,i)*hydro.properties.density;           % Viscous damping
%     end
% end

