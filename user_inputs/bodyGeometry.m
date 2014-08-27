%bodyGeometry.m
r_PR_W=6.06;                    %cm, offset from point of rotation (PR) to waterline/world (W)

%Spar/Nacelle
r_CG_PR_S=[0 0 (53.35-r_PR_W)];     %cm, offset from point of rotation (PR) to AF CG
r_CG_W_S=[0 0 53.35];       %cm, offset from AF CG to waterline/world (W)
MI_S = [4.8649913 4.4668629 1.2269318]; %moments of inertia, g-cm2
PI_S = [.0000040 .0000027 .0000002]; %products of inertia, g-cm2
M_S=39.500;              %g, mass of spar/nacelle

%Forward Float
r_PR_CG_FF=[23.37 0 2.40];     %cm, offset from point of rotation (PR) to AF CG
% r_PR_CG_FF=[23.37 0 0];     %cm, offset from point of rotation (PR) to AF CG
r_CG_W_FF=[-23.37 0 3.66];       %cm, offset from AF CG to waterline/world (W)
MI_FF = [.3261483 .0688825 .3729845]; %moments of inertia, g-cm2
PI_FF = [.0013574 .0117290 .0088438]; %products of inertia, g-cm2
M_FF=8.2939;              %g, mass of forward float

%Aft Float
r_PR_CG_AF=[-23.00 0 (-6.05+r_PR_W)];     %cm, offset from point of rotation (PR) to AF CG
r_CG_W_AF=[23.00 0 r_PR_W];       %cm, offset from AF CG to waterline/world (W)
MI_AF = [.3504810 .0691134 .3697848]; %moments of inertia, g-cm2
PI_AF = [-.0003017 .0068382 .0063938]; %products of inertia, g-cm2
M_AF=8.926;              %g, mass of aft float
