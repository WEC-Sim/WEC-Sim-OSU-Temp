function wave = makeWaveSignal(wave, wec)

% Create wave and forcing signals 
mask                    = linspace(0,1,150);                           % This makes the forcing function fade in slowly, so we don't get abrupt derivatives and blow our solution up if our intitial conditions aren't perfect.
mask                    = mask';
remainingLength         = length(wave.sig.eta(:,2)) - length(mask);
mask                    = [mask;  ones(remainingLength,1)];
wave.sig.eta(:,2)       = wave.sig.eta(:,2).*mask;                     % Wave elevation  % Multiply the forcing functions by our mask.
wave.sig.etaDot(:,2)    = wave.sig.etaDot(:,2).*mask;                  % Wave heave velocity
wave.sig.eta2Dot(:,2)   = wave.sig.eta2Dot(:,2).*mask;                 % Wave heave acceleration
wave.sig.Fe             = (wec.A*wave.sig.eta2Dot(:,2) + wec.B*wave.sig.etaDot(:,2) + wec.K*wave.sig.eta(:,2));         % Excitation force
wave.sig.FeDot          = (wec.A*wave.sig.eta3Dot(:,2) + wec.B*wave.sig.eta2Dot(:,2) + wec.K*wave.sig.etaDot(:,2));     % Derivative of excitation force - for LQT 
wave.sig.tFe            = wave.sig.eta(:,1);                           % Time vector for signal
wave.zDotOpt            = wave.sig.Fe/2/wec.B.*mask;                   % Optimum velocity signal
wave.z2DotOpt           = wave.sig.FeDot/2/wec.B.*mask;                % Derivative of optimum velocity signal - for LQT
wave.zDotOptFun         = @(t) interp1(wave.sig.tFe, wave.zDotOpt, t, 'cubic', 'extrap');                               % Make them a function
wave.z2DotOptFun        = @(t) interp1(wave.sig.tFe, wave.z2DotOpt, t, 'cubic', 'extrap');
