function [hydro]=pressureDistribution(hydro)

if hydro.WAMIT.IOPTN(5)==1
   fname=[hydro.WAMIT.fileDir,hydro.WAMIT.fileName,'.5p'];
   [hydro.WAMIT.pressure] = parseInputFile_WAMIT_5p(fname, hydro);

   for j=4:18   
      i=1;
      if j<10
         fname=[hydro.WAMIT.fileName,'_5p00',int2str(j),'.vtk'];
      elseif j<100
         fname=[hydro.WAMIT.fileName,'_5p0',int2str(j),'.vtk'];
      else
         fname=[hydro.WAMIT.fileName,'_5p',int2str(j),'.vtk'];          
      end
      fileID = fopen(fname,'w');
      fprintf(fileID,'%s \n','# vtk DataFile Version 2.0');  
      fprintf(fileID,'%s %s \n', hydro.WAMIT.fileName,'pressure distribution plot');
      fprintf(fileID,'%s \n','ASCII');  
      fprintf(fileID,'%s \n','DATASET POLYDATA'); 
      temp=['POINTS ',int2str(hydro.WAMIT.TotNumV(i)),' float'];
      fprintf(fileID,'%s \n',temp);     
      for k=1:hydro.WAMIT.TotNumV(i)
         fprintf(fileID,'%f %f %f \n',hydro.WAMIT.points.X(k,i),hydro.WAMIT.points.Y(k,i),hydro.WAMIT.points.Z(k,i));    
      end
      temp=['POLYGONS ',int2str(hydro.WAMIT.NPanel(i)),'  ',int2str(hydro.WAMIT.NPanel(i)*5)];
      fprintf(fileID,'%s \n',temp);        
      for k=1:hydro.WAMIT.NPanel(i)
         k1=hydro.WAMIT.points.gdf2Node((k-1)*4+1,i)-1;
         k2=hydro.WAMIT.points.gdf2Node((k-1)*4+2,i)-1;
         k3=hydro.WAMIT.points.gdf2Node((k-1)*4+3,i)-1;
         k4=hydro.WAMIT.points.gdf2Node((k-1)*4+4,i)-1;
         fprintf(fileID,'%s %d %d %d %d \n', '4', k1, k2, k3, k4);           
      end
      temp=['CELL_DATA ',int2str(hydro.WAMIT.NPanel(i))];
      fprintf(fileID,'%s \n',temp);        
      fprintf(fileID,'%s \n','SCALARS cell_scalars float 1');  
      fprintf(fileID,'%s \n','LOOKUP_TABLE default');  
      for k=1:hydro.WAMIT.NPanel(i)
         fprintf(fileID,'%d \n', hydro.WAMIT.pressure(k,j,i));           
      end
   end
fclose(fileID);   
end
