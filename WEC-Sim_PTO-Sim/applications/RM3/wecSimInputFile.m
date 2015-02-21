% Simulation Data

simu.startTime=0;                           % Simulation Start Time [s]
simu.endTime=600;                           % Simulation End Time [s]
simu.dt = 0.001;                              % Simulation Delta_Time [s]
simu.simMechanicsFile = 'RM3.slx';          % Specify Simulink Model File          
simu.mode='rapid-accelerator';                         % Specify Simulation Mode 
                                                % (normal/accelerator
                                                % /rapid-accelerator)                                              
%simu.explorer='on';                         % Turn SimMechanics Explorer 
                                                % (on/off)
%simu.verbose='on';
%Wave Information
waves.H = 3;                              % Wave Height [m]
waves.T = 8;                                % Wave Period [s]
waves.type = 'regular';                     % Specify Type of Waves 

% waves.H = 3;                              % Wave Height [m]
% waves.T = 8;                                % Wave Period [s]
% waves.type = 'irregular';                   % Specify Type of Waves 
% waves.spectrumType = 'PM';                   % Specify Wave Spectrum Type

% % Wave Information: Irregular Waves using PM Spectrum
% waves.H = 2.5;                              % Wave Height [m]
% waves.T = 8;                                % Wave Period [s]
% waves.type = 'irregular';                   % Specify Type of Waves 
% waves.spectrumType = 'PM';                   % Specify Wave Spectrum Type

% % Wave Information: Irregular Waves using User-Defined Spectrum
% waves.type = 'irregularImport';                   % Specify Type of Waves 
% waves.spectrumDataFile = 'ndbcBuoyData.txt';    % Specify fileName.text

% Body Data
body(1) = bodyClass('Float');               % Initialize bodyClass for Float
body(1).hydroDataType = 'wamit';            % Specify BEM solver
body(1).hydroDataLocation = ...             % Location of WAMIT *.out file
    './wamit/rm3.out';
body(1).mass = 'wamitDisplacement';         % Mass from WAMIT [kg]
body(1).cg = 'wamit';                       % Cg from WAMIT [m]
body(1).momOfInertia = ...                  % Moment of Inertia [kg-m^2]
    [20907301 21306090.66 37085481.11];      
body(1).geometry = 'geometry/float.stl';    % Geometry File

body(2) = bodyClass('Spar_Plate');          % Initialize bodyClass for 
                                                % Spar/Plate
body(2).hydroDataType = 'wamit';            % Specify BEM solver
body(2).hydroDataLocation = ...             % Location of WAMIT *.out file
    './wamit/rm3.out'; 
body(2).mass = 'wamitDisplacement';         % Mass from WAMIT [kg]
body(2).cg = 'wamit';                       % Cg from WAMIT [m]
body(2).momOfInertia = ...
    [94419614.57 94407091.24 28542224.82];  % Moment of Inertia [kg-m^2]
body(2).geometry = 'geometry/plate.stl';    % Geometry File

% PTO and Constraint Parameters
constraint(1) = ...                         % Initialize Constraint Class 
    constraintClass('Constraint1');             % for Constraint1

pto(1) = ptoClass('PTO1');                  % Initialize ptoClass for PTO1
pto(1).k=0;                                 % PTO Stiffness Coeff [N/m]
%pto(1).c=1200000;                           % PTO Damping Coeff [Ns/m]
pto(1).c=2500000;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
% PTO-Sim
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Constants

fixedDamping = 2.5e6;               % WEC-Sim fixed damping coefficient
Ap = 0.054;                         % Piston Area [m^2]
z_dRated = 1.1;                     % Rated piston velocity [m/s]
P_rated = 0.5e6;                    % Hydraulic Rated Power
Beta_e = 1.86e9;                    % Effective bulk modulus [Pa]
Vo = Ap*20;                         % Vol. Cylinder Chamber [m^3] 
Cd = 0.61;                          % Discharge coefficient
Amax = 0.002;                       % Maximum valve area [m^2]
Amin = 1e-8;                        % Minimum valve area [m^2]
pMax = 1e6;                         % Maximum area pressure [Pa]
pMin = 0.75*pMax;                      

omegaInit = 0;                        
omegaGen = 251.3274;                % Rotational speed of the generator [rad/s]

rho = 850;                          % Hydraulic fluid density [kg/m^2]
alpha = 1;                          % Swashplate angle ratio 
                  
D = 0.5*z_dRated*Ap/omegaGen;       % Norminal Motor displacement [m^3]
J = 12;                             % Motor Moment of Inertia [kg-m^2] 
bg = P_rated/(omegaGen)^2;          % Generator damping [kg-m^2/s]
bf = 0.05*bg;                       % Fractional damping [kg-m^2/s]

k1 = 200;                             
k2 = atanh((Amin-(Amax-Amin)/2)*...
     2/(Amax - Amin))*1/(pMin-(pMax + pMin)/2);                      



%% Low Pressure Accumulator D 
                                                      
VD0 = 6;                                    % Vol. Accumulator D [m^3]
pDrated = 16e6;                             % Rated working pressure
pDupper_limit = (4/3)*pDrated;              % Uppder working pressure   
pDlower_limit = (0.5)*pDupper_limit;        % Lower workig pressure
pDprecharge = 0.9*pDlower_limit;            % Precharge pressure

VDmax = VD0*(1-(pDprecharge/pDupper_limit)^(1/1.4));  
VDmin = VD0*(1-(pDprecharge/pDlower_limit)^(1/1.4));
VDeq = VDmax;
pDeq = pDprecharge/(1-VDeq/VD0)^(1.4);


%% High Pressure Accumulator C
                                 
VC0 = 8.5;                                  % Vol. Accumulator C [m^3]
motor.del_p_r = 15e6;
pCrated = motor.del_p_r + pDrated;
pCeq = pDeq;
pClower_limit = pCeq;
pCupper_limit = 1.5*pClower_limit;
pCprecharge = 0.9*pClower_limit;

VCeq = VC0*(1-(pCprecharge/pCeq)^(1/1.4));
VCmax = VC0*(1-(pCprecharge/pCupper_limit)^(1/1.4));
VCmin = VC0*(1-(pCprecharge/pClower_limit)^(1/1.4));


%% Top and Bottom Pressures A and B 

pAeq = pDupper_limit;
pBeq = pDupper_limit;
pAupper_limit = 32e6;
pAlower_limit = 20e6;

% Pressure A
pAi = pAeq;                     

% Pressure B

pBi = pBeq;
pBupper_limit = 32e6;
pBlower_limit = 20e6;


%% Generator

load motorEff
%TgenBase = 1387;
TgenBase = 2000;
%omegaBase = 863;
omegaBase = 251.3;
driveEff = 0.98;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

