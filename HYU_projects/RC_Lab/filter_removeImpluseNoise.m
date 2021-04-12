function [y] = filter_removeImpluseNoise(datap2,datap1, datac, thresh)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here

backdiff = datap1 - datap2;
forwarddiff = datap1 - datac;

x1 = 0;
x2  =2;
y1 = datap2;
y2 = datac;
x=1;

if((forwarddiff>thresh)&&(backdiff>thresh) ) ||  ((forwarddiff < -thresh)&&(backdiff < -thresh) )
    y = y1 + (x-x1)*(y2-y1) / (x2-x1) ;
else
    y = datap1;
    
end
end

