function  [dam] = calcDamage(sigma, nBin, cFlag)
% INPUT:
%   sigma - time history of stress
% OUTPUT:
%   totDam - total damage over time history
%   cumDam - cumulative damage w.r.t. time
%
% Sean Casey
% 2/2/13
% GRA - OSU

%% Create S-N curve for 316 Steel
Sut = 515e6;                    % [Pa] Ultimate Strength 316 steel
Sf = 0.9*Sut;
Sy = 204e6;                     % [Pa] Yield Strength
ka = 4.51*(Sut*10^-6)^-0.265;   % determination of endurance limit pg. 286 shigley's
kb = 1;                         % For axial loading - pg. 280 shigleys
kc = 0.85;
kd = 1;
ke = 0.868;                     % 95% reliability
Se = ka*kb*kc*kd*ke*0.5*Sut;    % 0.85 for axial loading
x1 = 10^3;
x2 = 10^6;
del_x = x2 - x1;
del_y = Se - Sf;
m = del_y/del_x;                % Slope of S-N curve
b = Sf - m*x1;              % y = mx+b

%% Total Damage
ext = sig2ext(sigma);
rf = rainflow(ext);             % Rainflow counting of stress cycles
if size(rf, 2) > 1;
    [ni, sigma_i] = rfhist(rf, nBin);     % Bin counted cycles
    if any(sigma(1,:) > Sy)
        disp('Failure - stress surpassed yield strength')
    end
    
    
%     sigma_i(1, sigma_i > Sf) = 0;   % remove stresses higher than max on S-N
%     sigma_i(1, sigma_i < Se) = 0;   % remove stresses below endurance limit
    if any(sigma > Sf) 
       dam.error2 = 'Stress levels greater than Sf' 
    elseif any(sigma > Sy)
       dam.error3 = 'Stress levels greater than Sy' 
    end 
    Ni = (sigma_i- b)/m;          % Total number of stresses at stress leve i
    
    Ni = Ni(sigma_i > Se & sigma_i < Sf);
    ni = ni(sigma_i > Se & sigma_i < Sf);
    if isempty(Ni)
       dam.totDam = 0; 
    else
       dam.totDam = sum(ni./Ni);           % Total damage incurred over simulation
    end


% Parameters for damage calculation
dam.Sut = Sut;
dam.Se  = Se;
dam.Sf  = Sf;
dam.Sy  = Sy;
dam.x1  = x1;
dam.x2  = x2;
dam.nBin = nBin;

% Total Damage History
dam.sigma = sigma;
dam.rf  = rf;
dam.ext = ext;
dam.ni  = ni;
dam.Ni  = Ni;
dam.sigma_i = sigma_i;

else 
    dam.error1 = 'No damage - rf < 1'
end



%% Cumulative Damage
c = 0;
if cFlag == 1
    for i = 2:50:length(sigma)
        c = c+1;
        ext = sig2ext(sigma(1:i));
        rf = rainflow(ext);
        if length(rf) > 1
            [ni, sigma_i] = rfhist(rf, nBin);     % Bin counted cycles
            if any(sigma(1,:) > Sy)
                disp('Failure - stress surpassed yield strength')
                break
            end
            
            
            Ni = (sigma_i - b)/m;          % Total number of stresses at stress leve i
            Ni = Ni(sigma_i > Se & sigma_i < Sf);
            ni = ni(sigma_i > Se & sigma_i < Sf);
            sigma_i = sigma_i(sigma_i > Se & sigma_i < Sf);
            
            if isempty(Ni) && c == 1
                dam.cumDam(c) = 0;
            elseif isempty(Ni)
                dam.cumDam(c) = dam.cumDam(c-1);
            else
                dam.cumDam(c) = sum(ni./Ni);           % Total damage incurred over simulation
            end
            
            if c~=1 && dam.cumDam(c) < dam.cumDam(c-1) 
                dam.cumDam(c) = dam.cumDam(c-1);
            end
            
            dam.cumInd(c) = i;
            
        end
        
    end
end




