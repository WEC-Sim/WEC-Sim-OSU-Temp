function [n, x, rf] = doRainflow(F, F_avg, nBins) 

ext = sig2ext(F);
ext = ext/abs(F_avg);
rf  = rainflow(ext); 

[n, x] = rfhist(rf, nBins); 
