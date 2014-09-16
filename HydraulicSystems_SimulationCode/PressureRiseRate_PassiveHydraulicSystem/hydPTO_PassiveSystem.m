function  simData = hydPTO_PassiveSystem(tspan, dynModel, init, pto, wec, wave)

% xDot = [vDotA; vDotB; vDotC; vDotD; vDotE; vDotF; omegaDot; z1Dot; z2Dot];
% x = [vA, vB, vC, vD, vE, vF, omega, z1, z2];

% Initial Conditions;
xi = init.xi; 

tFe = wave.sig.tFe;
Fe  = wave.sig.Fe; 

% Control inputs
u = pto.alpha_i;

% Specify Options
options = odeset('MaxStep', 0.05, 'RelTol', 1e-6);

% Evaluate ODE
simSol = ode23tb(@simPTO, tspan, xi, options);

% Extract Simulation Data
simData = getOutput(simSol, pto, wec, wave);


    function xDot = simPTO(t, x)
        
%         xDot = zeros(7,1);
        
        xDot = dynModel.fun_xDot(x(1), x(2), x(3), x(4), x(5), x(6), x(7), u(1));
        xDot(7,1) = xDot(7,1) + 1/(wec.m + wec.A)*interp1(tFe, Fe, t, 'cubic', 'extrap'); 
        
    end

end
