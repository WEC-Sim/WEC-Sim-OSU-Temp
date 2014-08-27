%NonlinearSetup
baseDir = './user_inputs/geometry/';
float = [baseDir 'Float.STL'];
plate = [baseDir 'Plate.STL'];

%parse STL file for float
[Faces Vertices ~] = rndread(float);
for i=1:1:length(Faces)
    v1 = Faces(i,1);
    v2 = Faces(i,2); 
    v3 = Faces(i,3); 
    STLfloat(i,1,:) = Vertices(v1,:);
    STLfloat(i,2,:) = Vertices(v2,:);
    STLfloat(i,3,:) = Vertices(v3,:);
end

%parse STL file for submerged plate
[Faces Vertices ~] = rndread(plate);
for i=1:1:length(Faces)
    v1 = Faces(i,1);
    v2 = Faces(i,2); 
    v3 = Faces(i,3); 
    STLplate(i,1,:) = Vertices(v1,:);
    STLplate(i,2,:) = Vertices(v2,:);
    STLplate(i,3,:) = Vertices(v3,:);
end

Amp = hydro.waves.H/2;
w = 2*pi/hydro.waves.T;         %rad/s
d=50;                      %m
lambda = hydro.properties.g/(2*pi)*hydro.waves.T^2;      %m
k=2*pi/lambda;              %/m

nonlinear_params=[Amp;k;w;d];