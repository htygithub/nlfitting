

for ii = 1:8
   fname = sprintf('./testdata/030-%03d.dcm',ii);
   disp(fname);
   info = dicominfo(fname);
   TI(ii)= info.InversionTime/1000;
   ima(:,:,ii) = double(dicomread(fname));
    
end

[T1_map sim_imgs fit_error error_map coef]=T1mapping_mex(TI,ima);
imagesc(T1_map,[0 2]);colormap jet;axis off image;