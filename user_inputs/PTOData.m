%PTOData.m
%% Choose Electricity Generation Module    
VSS_GEN=1; %1=Spring/Damper, 2=Damper, 3=Thev_equivalen
%% Choose DriveTrain Module    
VSS_DRIVE=1; %1=direct-drive, 2= hydraulic
%% Electric Generator Modules
%% Spring-Damper System
%T_gen=-K_# *(rel_disp) -C_# * (rel_vel);
% VSS_GEN =1, if you want to use the Spring_Damper PTO module
    K_for = 0;
    C_for = 3.5743;      %provided by CPT, includes 10^-2 unit conversion
    K_aft = 0;
    C_aft = 1200000;      %Ns/m, provided by Yi-Hsiang
    VSS_Spring_Damper=Simulink.Variant('VSS_GEN==1');
%% Simple Linear Damper Generation
%T_gen=-Gen_damp * (rel_vel);
    Gen_Damp = 2.1;             % Generator Rotary Damping [Nm/(rad/s)]
    VSS_Damper=Simulink.Variant('VSS_GEN==2');
%% Thevenin-Equivalent Generator from FAST User's Manual (Appendix J)
% Generator specs from 'Dynamic Models for Wind Turbines and Wind Power
% Plants' (Singh and Santoso) Appendix A.2 VS-SCIG 1.5 MW,
% Thevenin model of Squirrel Cage Induction Generator from 'Electric
% Machinery Fundamentals, 4th Edition' Stephen Chapman, Eq. 7-50. 
% Must be very careful about magnitude and synchronous speed of Thevenin
% Equivalent generator. These built in values will make the code work.
switch VSS_DRIVE
    case 2                                      % Generator when connected to Hydraulic Drivetrain
        base_VA=2.5e5;                          % Rated Power [Watts] 
        N_poles=3;                              % Number of poles in generator [-] (should be 6, but synchronous speed is too low)
    case 1                                      % Generator when connected to Direct-Drive Drivetrain
        switch VSS_GEN
            case 3
                error('Cannot have bidirectional rotational motion to Thevenin Equivalent Generator')
        end
        base_VA=2.6e2;                          % Rated Power [Watts] 
        N_poles=6;                              % Number of poles in generator [-] (should be 6, but synchronous speed is too low)   
    otherwise
        base_VA=1.5e6;                          % Rated Power [Watts] 
end
    f_line=60;                                  % Line Frequency (60 in N. America, 50 in Europe) [Hz]
    q1= 3;                                      % Number of phases of generator [-]
    base_V=690/sqrt(q1);                        % Rated Phase Voltage [Volts]
    base_A=base_VA/(base_V*sqrt(q1));           % Base Amperage [Amps]
    base_R=base_V/(base_A*sqrt(q1));            % Base Resistance [Ohms]  
 
    R2=2.1e-3*base_R;                           % Rotor Resistance [Ohms]
    R1=5e-3*base_R;                             % Stator Resistance [Ohms]
    X1=8e-2*base_R;                             % Stator Leakage Reactance [Ohms]
    X2=4.78e-2*base_R;                          % Rotor Leakage Reactance [Ohms]
    Xm=6.8*base_R;                              % Magnetizing Reactance [Ohms]
    omega_s= 4*pi*f_line/N_poles;               % Synchronous speed [rad/s]
    Vth= base_V*(1i*Xm/(R1+1i*(X1+Xm)));        % Thevenin's Equivalent Voltage [Volts]
    Zth=1i*Xm*(R1+1i*X1)/(R1+1i*(X1+Xm));       % Thevenin's Equivalent Impedance [Ohms]
    Rth=real(Zth);                              % Thevenin's Equivalent Resistance [Ohms]
    Xth=imag(Zth);                              % Thevenin's Equivalent Reactance [Ohms]
    s=[-2:1/50:-.15 .15:1/50:1]';               % Synchronous slip speeds for interpolation (avoid ill-defined area around s=0) [-]
    omega=(1-s)*omega_s;                        % Rotor speeds for interpolation [rad/s]
    T_ind=(3*(Vth*Vth')*R2)./(omega_s*s.*((Rth+R2./s).^2+(Xth+X2)^2)); % Generator torque values for look-up table [rad/s]
    ss=-2:.01:1;                                % Synchronous slip speeds used in interpolation [-]
    Ts=spline(s,T_ind,ss);                      % Generator torques (better defined around s=0) [-]
    omegas=(1-ss)*omega_s;                      % Rotor speeds for plotting [rad/s]
%     figure(1)                                 % Plot to see Thevenin generator speed-torque curve
%     plot(omegas,Ts,'o-')
%     xlabel('Generator Shaft Rotational Velocity (rad/s)')
%     ylabel('Generator Torque (Nm)')
    VSS_Thev=Simulink.Variant('VSS_GEN==3');
%% Drivetrain Modules
%% Direct-Drive 
% theta_LSS* r_LSS= + theta_HSS*r_HSS
% T_out=1/r_g*T_in -Id*ddot(theta_LSS) -Bd*dot(theta_LSS)-Kd*theta_LSS
% VSS_DRIVE =1, if you want to use the Hydraulics PTO module
    r_LSS=1;   % gear radius of low speed shaft (connected to body)[m]
    %I_LSS=1e0;   % moment of inertia of LSS [kg-m^2]
    B_LSS=0;   % torsional viscous damping of LSS [kg-m^2/sec]
    K_LSS=0;   % torsional spring constant of LSS [N-m]
    r_HSS=1;   % gear radius of high speed shaft (connected to generator) [m]
    %I_HSS=0;   % moment of inertia of HSS [kg-m^2]
    B_HSS=0;   % torsional viscous damping of HSS [kg-m^2/sec]
    K_HSS=0;   % torsional spring constant of HSS [N-m]
    r_g=r_LSS/r_HSS; %gear ratio of LSS to HSS, (should be >=1, since omega_HSS= +r_g*omega_LSS) [-]
    %Id=1/r_g*(I_LSS+r_g^2*I_HSS); %Gearbox Inertia [kg-m^2]
    Bd=1/r_g*(B_LSS+r_g^2*B_HSS); %Gearbox damping constant [kg-m^2/sec]
    Kd=1/r_g*(K_LSS+r_g^2*K_HSS); %Gearbox spring constant [N-m]
    VSS_DD=Simulink.Variant('VSS_DRIVE==1');
%% Reuhl's Hydraulic System
%T_PTO= it's complicated, see subsystem
% VSS_DRIVE =2, if you want to use the Hydraulics PTO module
    angle_arm_aft= 1;       % displacement of aft_cylinder [m] =angle_arm_aft [m] *angle_aft [rad]
    angle_arm_fwd= 2;       % displacement of fwd_cylinder [m] =angle_arm_fwd [m] *angle_fwd [rad]
    CPT_scale=2e-3;         % To make the magnitude of the PTO smaller so the simulation doesn't break
% Hyraulic Cylinder Specs
    Dbore = 0.1524*CPT_scale;                 %% Bore Diameter [m]
    Drod = 0.1016*CPT_scale;                  %% Rod Diamteter [m]
    A_bore = pi*Dbore^2/4;          %% Area of Bore [cm^2]
    A_rod = pi*(Dbore^2-Drod^2)/4;  %% Area of Rod [cm^2]
    
% Accumulator Initial Conditions    
    p_atm = 101325;             % Atm Pressure [Pa]
    p_lp(1) = p_atm;            % low pressure accumulator initial pressure [Pa]
    delta_p(1) = 16023415.9;    %Operating Pressure [Pa]<- from report
    p_hp(1) = p_lp(1) + delta_p(1);     % high pressure accumulator initial pressure [Pa]
    
    V_lp(1) = 2;                % low pressure accumulator Ni (tot) volume [m^3]
    V_hp(1) = 50;               % high pressure accumulator Ni (tot) volume [m^3]

% Fixed Displacement Hydraulic Motor Specs (from Model 250 Spec Sheet)
    Vg = 0.00025;               % Fixed Displacement Motor Chamber Volume [m^3]
    Jmot = 0.061;               % Motor Moment of Intertia [kg-m^2]<- from data sheet
    hyd_mot_eff = 0.93;         % Hydraulic Motor vol/mech Efficiency <- from report
    hyd_mot_tot = 0.865;        % Hydraulic Motor TOTAL Efficiency <- from report
    pump_vol_eff = 0.97;        % Pump volumetric efficiency <- from report
    
% Electric Generator
    Jgen=3.9;           
    Jtot = Jmot+Jgen;  
    VSS_Hydraulics=Simulink.Variant('VSS_DRIVE==2');    




