function [T1_map sim_imgs fit_error error_map coef]=T1mapping_mex(TI,img3d)
    %function [T1_map sim_imgs fit_error error_map ]=T1mapping_mex(t,new_img)
    % TI: inversion times
    % img3d: (x,y,number of TI)

    %=======================

    new_t = TI;
    new_img = img3d;
    [d1 d2 d3]=size(new_img);
    y=reshape(new_img,d1*d2, d3);
    y=y';
    [coef,maps]=lmcurve_T1map(new_t,y);
    coef=reshape(coef,3,d1,d2);
    maps=reshape(maps,d3,d1,d2);
    T1_map=abs(squeeze(coef(3,:,:).*(coef(2,:,:)./coef(1,:,:)-1)));
    %simimg=squeeze(coef(1,:,:));
    sim_imgs=permute(maps,[2 3 1]);

    % coef=reshape(coef,d1,d2,3);

    for ii=1:d3
        error_map_temp=(squeeze(maps(ii,:,:))-squeeze(new_img(:,:,ii))).^2;
        fit_error(ii)=sum(error_map_temp(:));
        if ii==1
            error_map=error_map_temp;
        else
            error_map=error_map+error_map_temp;
        end

    end
end

%=======================
