function [y] = filter_removeImpluseNoise2(datap5,datap4,datap3,datap2,datap1,thresh)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here

backdiff2 = datap3 - datap5;
backdiff1 = datap3 - datap4;
forwarddiff1 = datap3 - datap2;
forwarddiff2 = datap3 - datap1;

x  = 1;
x1 = 0;
x2 = 2;
y1 = datap5;
y2 = datap4;
y3 = datap3;



if((forwarddiff>thresh)&&(backdiff>thresh) ) ||  ((forwarddiff < -thresh)&&(backdiff < -thresh) )
    y = y1 + (x-x1)*((y2-y1)) / (x2-x1) ;
else
    y = datap1;
    
end
end

