function [ptoS,zdot_rms] = PTOsize(ptoConfig, Ts, Hs, waveSrc, noEff, wec)


%% WEC Model - 1DOF PA - SIZE PTO
% Sean Casey
% 11/10/12
% GRA - OSU


%% Specify Wave Climate

% Configuration parameters
simParam.t0 = 0;
simParam.tf = 300;
simParam.del_t = 0.01;

% Time
t0 = simParam.t0;
tf = simParam.tf;
df = 1/tf;

if waveSrc == 1
    wave = makeWave2D(Hs, Ts, df, 'Regular');
elseif waveSrc == 0
    wave = makeWave2D(Hs, Ts, df, 'Irregular');
end

eta(:, 1)       = wave.ts.t;        % Wave Displacement
eta(:, 2)       = wave.ts.z;
etaDot(:, 1)    = wave.ts.t;        % Wave Velocity
etaDot(:, 2)    = wave.ts.w;
etaDotDot(:, 1) = wave.ts.t;        % Wave Acceleration
etaDotDot(:, 2) = wave.ts.wdot;

%% Size PTO

switch noEff
    case 'Eff'
        % Feed through
        ptoS.motor.eta_h  = ptoConfig.eta_hm;
        ptoS.motor.eta_v  = ptoConfig.eta_vm;
        ptoS.pump.eta_h   = ptoConfig.eta_hp;
        ptoS.pump.eta_v   = ptoConfig.eta_vp;
        ptoS.gen.eta_g    = ptoConfig.eta_g;
        
        % Change Units
        ptoS.motor.V_nom  = ptoConfig.V_nom / 100^3 / (2*pi);   % [m^3/rad]
        ptoS.gen.omega_r  = ptoConfig.omega_r * 2*pi / 60;          % [rad/s]
        ptoS.gen.P_r      = ptoConfig.Pg_r * 1000;              % [W]
        
        % Calculate Size
        ptoS.motor.Vdot_r  = ptoS.motor.V_nom * ptoS.gen.omega_r * ptoS.motor.eta_v;
        ptoS.gen.tau_r     = ptoS.gen.P_r  / ptoS.gen.omega_r / ptoS.gen.eta_g;                       % rated torque [N-m]
        ptoS.motor.del_p_r = ptoS.gen.tau_r  / ptoS.motor.V_nom / ptoS.motor.eta_h ;
        
        ptoS.gen.bt        = ptoS.gen.tau_r / ptoS.gen.omega_r;
        ptoS.gen.bg        = ptoS.gen.eta_g * ptoS.gen.bt;
        ptoS.gen.bf        = ptoS.gen.bt - ptoS.gen.bg;
        
        %(ptoS.motor.eta_h * ptoS.motor.del_p_r * ptoS.motor.V_nom - ptoS.gen.tau_r * ptoS.gen.eta_g) / ptoS.gen.omega_r;
        %ptoS.motor.eta_h * ptoS.motor.del_p_r * ptoS.motor.V_nom / ptoS.gen.omega_r - ptoS.gen.bf;
        % Accumulator
        
        % Pump
        ptoS.pump.zdot_rms   =  mean(abs(etaDot(:,2))); sqrt(1/length(etaDot(:,2))*sum(etaDot(:,2).^2));
        ptoS.pump.A_p        = ptoS.motor.V_nom * ptoS.gen.omega_r *  ptoS.motor.eta_v * ptoS.pump.eta_v  / ptoS.pump.zdot_rms;
        ptoS.pump.d_p        = sqrt(4*ptoS.pump.A_p/pi);
        
        
    case 'noEff'
        % Change Units
        ptoS.motor.V_nom  = ptoConfig.V_nom / 100^3 / (2*pi);   % [m^3/rad]
        ptoS.gen.omega_r  = ptoConfig.omega_r * 2*pi / 60;      % [rad/s]
        ptoS.gen.P_r      = ptoConfig.Pg_r * 1000;              % [W]
        
        % Calculate Size
        ptoS.motor.Vdot_r  = ptoS.motor.V_nom * ptoS.gen.omega_r;
        ptoS.gen.tau_r     = ptoS.gen.P_r  / ptoS.gen.omega_r;                       % rated torque [N-m]
        ptoS.motor.del_p_r = ptoS.gen.tau_r  / ptoS.motor.V_nom ;
        
        ptoS.gen.bt        = ptoS.gen.tau_r / ptoS.gen.omega_r;
        ptoS.gen.bg        = ptoS.gen.bt;
        
        % Accumulator
        
        % Pump
        ptoS.pump.zdot_rms   =  mean(abs(etaDot(:,2))); %sqrt(1/length(etaDot(:,2))*sum(etaDot(:,2).^2));
        ptoS.pump.A_p        = ptoS.motor.V_nom * ptoS.gen.omega_r / ptoS.pump.zdot_rms;
        ptoS.pump.d_p        = sqrt(4*ptoS.pump.A_p/pi);
end





