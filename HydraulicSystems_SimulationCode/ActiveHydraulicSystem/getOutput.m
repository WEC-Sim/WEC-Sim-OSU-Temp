function simData = getOutput_var3(simSol, pto, wec, wave, u)


simData.simSol          = simSol;
simData.time            = simSol.x;
simData.x               = simSol.y;
simData.z               = simSol.y(1,:);
simData.zDot            = simSol.y(2,:);
simData.pA              = simSol.y(3,:);
simData.omega           = simSol.y(4,:);
simData.pR              = pto.pR; 
simData.Fe              = interp1(wave.sig.tFe, wave.sig.Fe, simData.time,'cubic','extrap');
simData.eta             = interp1(wave.sig.tFe, wave.sig.eta, simData.time,'cubic','extrap');
simData.etaDot          = interp1(wave.sig.tFe, wave.sig.etaDot, simData.time,'cubic','extrap');
simData.eta2Dot         = interp1(wave.sig.tFe, wave.sig.eta2Dot, simData.time,'cubic','extrap');
simData.zDotOpt        = simData.Fe/2/wec.B;
simData.u               = u; 
simData.alpha           = u(1,:);
simData.bg              = u(2,:); % u(2,:);
simData.T_gen           = simData.bg.*simData.omega(1,:);
simData.P_gen           = simData.T_gen.*simData.omega;
simData.Fpto            = pto.Ap*(simData.pA - pto.pR);
simData.P_exc           = simData.Fe.*simData.zDot;
simData.P_excOpt        = simData.Fe.*simData.zDotOpt; 
simData.P_hyd           = simData.Fpto.*simData.zDot; 
simData.P_hydOpt        = simData.Fpto.*simData.zDotOpt; 
simData.P_gen           = simData.T_gen.*simData.omega;
simData.Vdot_p          = pto.Ap*simData.zDot;
simData.Vdot_m          = simData.alpha.*simData.omega*pto.D;
simData.Vdot_leakageA   = pto.Ct*simData.pA;
simData.Vdot_leakageR   = pto.Ci*pto.pR;
simData.Vdot_bp         = 0.1*pto.D*simData.omega;

