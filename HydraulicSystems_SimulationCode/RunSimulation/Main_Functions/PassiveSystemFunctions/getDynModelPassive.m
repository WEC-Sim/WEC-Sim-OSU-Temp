function dynModel = getDynModelPassive(pto, wec, con)

%% Define symbolic system
syms pC0 pD0                                real positive
syms vC0 vD0                                real positive
syms D bg J bf                              real positive
syms m A B K Cd Ap rho k1 c b_e V0 Ct       real positive
syms Rt Dh  v                               real positive
syms av1 av2 av3 k2                         real positive
syms x1 x2 x3 x4 x5 x6 x7                   real
syms u1                                     real
%% 
x           = [x1; x2; x3; x4; x5; x6; x7]; 
u           = [u1]; 

% Orifice equation - includes laminar and turbulent flow 
syms cv(p1, p2)   
Av          = av1 + av2*tanh(k2*((p1-p2)-av3));      % valve area equation
cV(p1, p2)  = (Cd*Av*sqrt(2/rho*((p1-p2)*tanh(k1*(p1-p2)))));% + (v*Rt/2/Cd/Dh)^2) - Av*v*Rt/2/Dh);% * 1/2+1/2*tanh(k2*(;

% Accumulator pressure
syms pi(vi, v0i, p0i)
pi(vi,v0i,p0i) = p0i/(1-vi/v0i)^(1.4); 

% Define pressures 
% pA = pi(x1, vA0, pA0);
% pB = pi(x2, vB0, pB0); 
pC = pi(x3, vC0, pC0); 
pD = pi(x4, vD0, pD0); 

% Define flows 
vDotP = Ap*x7; 
vDotM = u1*D*x5; 
vDot1 = cV(x1, pC); 
vDot2 = cV(x2, pC); 
vDot3 = cV(pD, x2); 
vDot4 = cV(pD, x1); 

% State space -- full system
xDot1       =  b_e/(V0 - Ap*x6)*( vDotP - vDot1 + vDot4 ); %- Ct*x1
xDot2       =  b_e/(V0 + Ap*x6)*(-vDotP - vDot2 + vDot3 ); %  + Ct*x2
xDot3       =  vDot1 + vDot2 - vDotM;
xDot4       = -vDot3 - vDot4 + vDotM; 
xDot5       =  1/J*(u1*D*(pC-pD) - bg*x5 - bf*x5) ;
xDot6       =  x7;
xDot7       =  1/(m+A)*(-B*x7 - K*x6 - Ap*(x1-x2));

xDot  = [xDot1; xDot2; xDot3; xDot4; xDot5; xDot6; xDot7]; 

%% Create numeric dynamics model 

subVars = [b_e V0 pC0 pD0 vC0 vD0 D bg J m A B K Cd Ap rho k1 Rt Dh v av1 av2 av3 k2 bf];  
subVals = [pto.b_e pto.V0 pto.pC0 pto.pD0 pto.vC0 pto.vD0 pto.D pto.bg pto.J wec.m wec.A wec.B wec.K pto.Cd pto.Ap pto.rho pto.k1 pto.Rt pto.Dh pto.v pto.av1 pto.av2 pto.av3 pto.k2 pto.bf];

dynModel.xDot           = xDot; 
dynModel.sym_xDot       = subs(xDot, subVars, subVals);
dynModel.fun_xDot       = matlabFunction(dynModel.sym_xDot, 'vars', [x; u]'); 
