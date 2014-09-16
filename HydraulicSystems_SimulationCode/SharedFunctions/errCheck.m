%% Non-Linear Hydraulic PTO - GMREC Conference
% Sean Casey
% 2/20/13
% GRA - OSU
%
%   error check
%
% Notes:
%%
function simData = errCheck(simData, pto)

% Check if accumulators in bounds
if any(simData.V_A  < pto.V_A1) || any(simData.V_A  > pto.V_A2)
    simData.errCode.errStrA = 'V_A out of limits';
    simData.errCode.errA  = 1;
end
if any(simData.V_B  < pto.V_B1) || any(simData.V_B  > pto.V_B2)
    simData.errCode.errStrB = 'V_B out of limits';
    simData.errCode.errB  = 1;
end
if any(simData.V_C  < pto.V_C1) || any(simData.V_C  > pto.V_C2)
    simData.errCode.errStrC = 'V_C out of limits';
    simData.errCode.errC  = 1;
end
if any(simData.V_D  < pto.V_D1) || any(simData.V_D  > pto.V_D2)
    simData.errCode.errStrD = 'V_D out of limits';
    simData.errCode.errD  = 1;
end
if any(simData.V_E  < pto.V_E1) || any(simData.V_E  > pto.V_E2)
    simData.errCode.errStrE = 'V_E out of limits';
    simData.errCode.errE  = 1;
end
if any(simData.V_F  < pto.V_F1) || any(simData.V_F  > pto.V_F2)
    simData.errCode.errStrF = 'V_F out of limits';
    simData.errCode.errF  = 1;
end