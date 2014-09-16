function [b22, u22] = getHydroParams(d, h, T)

% Data From Wehausen 'Motion of Floating Bodies' 
% ** d/h must equal either 2 or 4 ** 

% INPUT: 
% h - cylinder draft 
% d - cylinder diameter
% OUTPUT: 
% b22 - radiation damping coeficient 
% u22 - added mass coeficient 

%% 
rho = 1025;             % Density of saltwater [kg/m^3]
g   = 9.81;             % acceleration due to gravity [m/s^2]

BT = d/h; 
V = pi*d^2/4*h;         % displaced volume
sigma = 2*pi/T;         % period
x = sigma*sqrt(d/2/g);  


switch BT
    case 2           % B/T = 2 
        
        bx = [0.00; 0.125; 0.25; 0.375; 0.50; 0.625; 0.75; 0.875; 1.00; 1.25; 1.50];
        by = [0.00; 0.250; 0.40; 0.450; 0.45; 0.420; 0.40; 0.220; 0.15; 0.05; 0.00]; 

        ux = [ 0.125; 0.25; 0.375; 0.50; 0.625; 0.75; 0.875; 1.00; 1.25; 1.50];
        uy = [ 2.500; 1.50; 1.100; 0.95; 0.900; 0.90; 0.925; 0.95; 1.00; 1.05]; 
        
    case 4 % B/T = 4

        bx = [0.00; 0.125; 0.25; 0.375; 0.50; 0.625; 0.75; 0.875; 1.00; 1.25; 1.50];
        by = [0.00; 0.500; 0.75; 0.870; 1.00; 0.950; 0.85; 0.750; 0.70; 0.45; 0.30]; 

        ux = [0.125; 0.25; 0.375; 0.50; 0.625; 0.75; 0.875; 1.00; 1.25; 1.50];
        uy = [4.000; 3.00; 2.150; 1.95; 1.700; 1.50; 1.520; 1.55; 1.65; 1.90];
    otherwise       % Interpolate between 2 and 4 

        bx = [0.00; 0.125; 0.25; 0.375; 0.50; 0.625; 0.75; 0.875; 1.00; 1.25; 1.50];
        by2 =[0.00; 0.250; 0.40; 0.450; 0.45; 0.420; 0.40; 0.220; 0.15; 0.05; 0.00]; 
        by4 = [0.00; 0.500; 0.75; 0.870; 1.00; 0.950; 0.85; 0.750; 0.70; 0.45; 0.30];
        by = by2+(by4-by2)*(BT-2)/(4-2);
        
        ux = [ 0.125; 0.25; 0.375; 0.50; 0.625; 0.75; 0.875; 1.00; 1.25; 1.50];
        uy2 = [ 2.500; 1.50; 1.100; 0.95; 0.900; 0.90; 0.925; 0.95; 1.00; 1.05]; 
        uy4 = [4.000; 3.00; 2.150; 1.95; 1.700; 1.50; 1.520; 1.55; 1.65; 1.90];
        uy = uy2+(uy4-uy2)*(BT-2)/(4-2);
end
%% Curve Fit 
by_poly = polyfit(bx, by, 5);
uy_poly = polyfit(ux, uy, 5);

yB = polyval(by_poly, x); % Non-dimensional y-values
yU = polyval(uy_poly, ux(end)); 

b22 = yB*rho*V*sqrt(2*g/d);    % radiation damping coeficient 
u22 = yU*rho*V;
%% Plot

bx_poly = linspace(bx(1), bx(end)); 
by_polyVal = polyval(by_poly, bx_poly); 

ux_poly = linspace(ux(1), ux(end)); 
uy_polyVal = polyval(uy_poly,ux_poly); 

%{
figure
subplot(2,1,1)
plot(ux, uy, 'r*'); hold on 
p1 = plot(ux_poly, uy_polyVal, 'r');
plot(ux(end), yU, 'ko')
title('Added Mass')

subplot(2,1,2)
plot(bx, by, 'b*'); hold on 
p2 = plot(bx_poly, by_polyVal, 'b');
plot(x, yB, 'ko')
grid on
title('Radiation Damping')
%}



