function dynModel = getDynModelActive(pto, wec, con)

%% Define symbolic system
syms Ap rho D bg J b_e V0 Ct Ci bf  pR              real positive
syms m A B K                                        real positive
syms x1 x2 x3 x4                                    real
syms u1 u2                                          real 
syms xBar1 xBar2 xBar3 xBar4                        real
syms uBar1 uBar2                                    real

%% 
% Create state variables and deviation variables 
x           = [x1; x2; x3; x4]; 
u           = [u1; u2]; 
xBar        = [xBar1; xBar2; xBar3; xBar4]; 
uBar        = [uBar1; uBar2]; 

xDot1 = x2; 
xDot2 = 1/(m+A)*(-B*x2 - K*x1 - Ap*(x3)); 
xDot3 = b_e/(V0 - Ap*x1)*(-u1*D*x4 - Ct*x3 + Ci*pR + Ap*x2);  % pg. 154 merrit
xDot4 = 1/J*(u1*D*(x3) - 0.1*D*pR - u2*x4 - bf*x4); 

xDot  = [xDot1; xDot2; xDot3; xDot4]; 
sol = findLinSys(xDot, x, xBar, u, uBar);


% 
%% Create numeric dynamics model 

subVars = [pR Ci Ct bf V0, b_e, Ap, rho, D, J, bg, m, A, B, K]; 
subVals = sym([pto.pR pto.Ci pto.Ct pto.bf pto.V0, pto.b_e, pto.Ap, pto.rho, pto.D, pto.J, pto.bg, wec.m, wec.A, wec.B, wec.K],'f');

dynModel.xDot       = xDot; 
dynModel.A          = sol.A;
dynModel.B          = sol.B;
dynModel.Ntilde     = sol.Ntilde;
dynModel.xDotBar    = sol.xDotBar;
    
dynModel.sym_A        = subs(sol.A, subVars, subVals);
dynModel.sym_B        = subs(sol.B, subVars, subVals);
dynModel.sym_Ntilde   = subs(sol.Ntilde, subVars, subVals);
dynModel.sym_xDotBar  = subs(sol.xDotBar, subVars, subVals);
dynModel.sym_xDot     = subs(sol.xDot, subVars, subVals);

dynModel.fun_A         = matlabFunction(dynModel.sym_A,         'vars', [xBar; uBar]');
dynModel.fun_B         = matlabFunction(dynModel.sym_B,         'vars', [xBar; uBar]');
dynModel.fun_xDotBar   = matlabFunction(dynModel.sym_xDotBar,   'vars', [xBar; uBar]');
dynModel.fun_Ntilde    = matlabFunction(dynModel.sym_Ntilde,    'vars', [xBar; uBar; x; u]');
dynModel.fun_xDot      = matlabFunction(dynModel.sym_xDot,      'vars', [x; u]'); 
