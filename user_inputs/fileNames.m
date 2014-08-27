%fileNames.m

base_name = 'WEC_Sim_Driver';
%base_name = 'WEC_Sim_Driver_610PM_Tuesday';

case_name = ['post_processing/' base_name '/'];
if exist(case_name) ~= 7
    mkdir(case_name)
end

%STL file names
baseDir = './user_inputs/geometry/';
aft_float = [baseDir 'AFT.STL'];
spar = [baseDir 'spar.STL'];
fwd_float = [baseDir 'FWD.STL'];
