function sol = findLinSys(xDot, x, xBar, u, uBar)
% Get symbolic representation of a linear system at working points xBar and
% uBar

sol.xDot = xDot;
sol.xBar = xBar; 
sol.uBar = uBar; 
sol.x    = x; 
sol.u    = u; 
sol.jacX = jacobian(xDot,x);
sol.jacU = jacobian(xDot,u);

sol.A       = subs(sol.jacX, [x; u], [xBar; uBar]); 
sol.B       = subs(sol.jacU, [x; u], [xBar; uBar]);
sol.xDotBar = subs(sol.xDot, [x; u], [xBar; uBar]);
sol.Ntilde  = sol.xDot - (sol.xDotBar + sol.A*(x-xBar) + sol.B*(u-uBar)); 

sol.A = simplify(sol.A);
sol.B = simplify(sol.B); 
sol.xDotBar = simplify(sol.xDotBar); 
sol.Ntilde = simplify(sol.Ntilde); 

end