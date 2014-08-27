function [NPanel, NVertices, points, TotNumV]= parseInputFile_WAMITgdf(hydro)

for i=1:hydro.WAMIT.NBODY

   fname=[hydro.WAMIT.fileDir,hydro.WAMIT.meshFile{i}];
   fid = fopen(fname, 'r');
   if fid == -1; error(['ERROR: Could not locate and open file ' fname]); end
   temp1 = fgetl(fid);
   temp2 = fgetl(fid);
   temp3 = fgetl(fid);
   temp4 = fgetl(fid);

   A=textscan(temp3, '%f %f');
   ISX=A{1};
   ISY=A{2};
   
   A=textscan(temp4, '%f');
   NPanel(i)=A{1};

   FR = importdata(fname,' ',4);
   NVertices(i)=length(FR.data);
   TotNumV(i)=0;
   for j=1:NVertices(i)
       tmp=0;
       for k=1:TotNumV(i)
          if (abs(FR.data(j,1)-points.X(k,i))<0.000001)
          if (abs(FR.data(j,2)-points.Y(k,i))<0.000001)
          if (abs(FR.data(j,3)-points.Z(k,i))<0.000001)
              tmp=k;
          end
          end
          end
       end
       if tmp==0
          TotNumV(i)=TotNumV(i)+1;
          points.X(TotNumV(i),i)=FR.data(j,1);
          points.Y(TotNumV(i),i)=FR.data(j,2);
          points.Z(TotNumV(i),i)=FR.data(j,3);
          points.gdf2Node(j,i)=TotNumV(i);
       else
          points.gdf2Node(j,i)=tmp;           
       end
   end
%    if ISY=1;
%       NVertices_tp=NVertices(i);
%       NVertices(i)=NVertices(i)*2;
%       for j=NVertices_tp+1:NVertices(i)
%           points.X(j,i)=FR.data(j,1);
%           points.Y(j,i)=points.Y(j-NVertices_tp,i);
%           points.Z(j,i)=points.Z(j-NVertices_tp,i);
%           points.P(j,i)=ceil(j/4);
%       end      
%    end   
end

