function [time, tind] = getTwindow(timeTemp, val_Start, val_End)

[t_delta_Start, t_ind_Start] = min(abs(timeTemp-val_Start));
[t_delta_End, t_ind_End] = min(abs(timeTemp-val_End));
ti   = timeTemp(t_ind_Start); 
tf   = timeTemp(t_ind_End); 

time = timeTemp(t_ind_Start:t_ind_End);
tind = t_ind_Start:t_ind_End;