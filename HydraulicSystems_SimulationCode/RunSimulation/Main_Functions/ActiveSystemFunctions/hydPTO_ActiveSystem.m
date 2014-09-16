function  simData = hydPTO_ActiveSystem(tspan, dynModel, init, pto, wec, wave)

%% Determine Control Law - offline - regulate motor speed
dynModel.Df = [0; 1/(wec.m+wec.A); 0; 0];
dynModel.F = @(t) interp1(wave.sig.tFe, wave.sig.Fe, t, 'cubic', 'extrap');

% Specify operating point
uBar = init.uBar;
xBar = init.xBar;

% Create matrix form of dynamics equations
xDotBar    = dynModel.fun_xDotBar(xBar(1), xBar(2), xBar(3), xBar(4), uBar(1), uBar(2));
Abar       = dynModel.fun_A(xBar(1), xBar(2), xBar(3), xBar(4), uBar(1), uBar(2));
Bbar       = dynModel.fun_B(xBar(1), xBar(2), xBar(3), xBar(4), uBar(1), uBar(2));
Ntilde     = @(x1,x2,x3,x4, u1, u2) dynModel.fun_Ntilde(xBar(1), xBar(2), xBar(3), xBar(4), uBar(1), uBar(2), x1, x2, x3, x4, u1, u2);

doUncontrolled = 0;
doTracking     = 1;

if doTracking
    
    omega_ref = 0; % 0.8*pto.omega_r;
    
    R = init.R;
    Q = init.Q;

    [Kbar, piLQR, e]=lqr(Abar,Bbar,Q,R);
    
    cloopA = Abar - Bbar*Kbar;
    
    % Create tracker
    init.xid = [0; 0; 0; 0];
    init.xi0 = init.xi - init.xid;
    
    tspanb = [init.tf init.ti];
    b0     = [0; 0; 0; 0];

    options1 = odeset('MaxStep', 0.05, 'RelTol', 1e-5);
    bsoln = ode15s(@trackerFunc, tspanb, b0, options1, Abar, piLQR, cloopA);
    
    fw = -Bbar*inv(R)*Bbar';
    bk =  Bbar*Kbar;
    
end

% Specify forcing function
Df = dynModel.Df;
F  = dynModel.F;

uNOctrl = [1; pto.bg];

%% Call ODE

% Specify Options
options2 = odeset('MaxStep', 0.05, 'RelTol', 1e-5);

% Evaluate ODE
if doUncontrolled
    simSol = ode15s(@simPTO_Uncontrolled, tspan, init.xi, options2);
    u1 = uNOctrl;
    u1(u1(1,:) > 1 ,:) = 1;
    u1(u1(1,:) < -1 ,:) = -1;
    simData = getOutput_Active(simSol, pto, wec, wave, u1);
end
if doTracking
    simSol = ode15s(@simPTO_Tracking, tspan, init.xi0, options2);
    btrack = deval(bsoln, simSol.x);
    for i = 1:length(simSol.x)
        u1(:,i) = -Kbar*simSol.y(:,i) + -inv(R)*Bbar'*btrack(:,i);
    end
    u1(1,u1(1,:) > 1) = 1;
    u1(1, u1(1,:) < -1) = -1;
    simData = getOutput_Active(simSol, pto, wec, wave, u1);
end


%% FUNCTIONS

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function xDot = simPTO_Uncontrolled(t,x)
        u = uNOctrl;
        xDot = xDotBar + Abar*(x - xBar) + Bbar*(u - uBar) + Ntilde(x(1),x(2),x(3),x(4),u(1), u(2)) + Df*F(t);
        
    end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function xDot = simPTO_LQR(t,x)
        u = -Kbar*(x);
        if u(1) > 1
            u(1) = 1;
        elseif u(1) < -1
            u(1) = -1;
        end
        
        xDot = xDotBar + (cloopA)*(x - xBar) + Ntilde(x(1),x(2),x(3),x(4),u(1),u(2)) + Df*F(t); %
    end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function xDot = simPTO_Tracking(t,x)
        
        bb = deval(bsoln, t);
        u = -Kbar*(x) - inv(R)*Bbar'*bb;
        if u(1) > 1
            u(1) = 1;
        elseif u(1) < -1
            u(1) = -1;
        end
        
        ref = [0; wave.zDotOptFun(t); 0; 0];
        refDot = [0; wave.z2DotOptFun(t); 0; 0];
        
        xDot =  xDotBar + (cloopA)*(x - xBar) + bk*ref + fw*bb  + Ntilde(x(1),x(2),x(3),x(4),u(1), u(2)) + Df*F(t) ; %(cloopA*ref - refDot)
        
    end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    function bDot = trackerFunc(t,b,a,p,clA_lqr)
        ref = [0; wave.zDotOptFun(t); 0; 0];
        refDot = [0; wave.z2DotOptFun(t); 0; 0];
        
        omega = a*ref - refDot;
        
        bDot = -clA_lqr'*b - p*omega;
        
    end

end
