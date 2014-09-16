function [k, L] = calcDR(T,h)

sigma = 2*pi/T; 
g = 9.81;

k = fzero('DR',[0 1000],[], g, h, sigma);

L = 2*pi/k;
% 
% fprintf('k = %3.3e\n',k)
% fprintf('L = %3.3e [m]\n\n',L)