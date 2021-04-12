function [output ,output_p ] = filter_IIR_biquadCascade(data,filtercoef,scaleVals, output_p, num_stage)
%UNTITLED9 Summary of this function goes here
%   Detailed explanation goes here


% filtercoef = [1,0,-1,1,-1.9632,0.9644;...
%                    1,0,-1,1,-1.8501,0.8681];
% scaleVals = [0.0602, 0.0602,1];

% numCoefsStage = 6;
for ii = 1:num_stage
    index_tmp = ii;%numCoefsStage*(ii-1);
    b0 = filtercoef(index_tmp ,1);
    b1 = filtercoef(index_tmp ,2);
    b2 = filtercoef(index_tmp ,3);
    a1 = filtercoef(index_tmp ,5);
    a2 = filtercoef(index_tmp ,6);
    scaleV = scaleVals(ii);
    
%     output_p(ii) = scaleV*data - a1*output_p(ii+1) - a2*output_p(ii+2) ;
%     y  = b0*output_p(ii) +b1*output_p(ii+1) +b2*output_p(ii+2);
%     
%     output_p(ii +2) = output_p(ii+1);
%     output_p(ii +1) = output_p(ii );
%     data = y;
    
    output_p(ii,end) = scaleV*data - a1*output_p(ii,end-1) - a2*output_p(ii,end- 2) ;
    y  = b0*output_p(ii,end) +b1*output_p(ii,end- 1) +b2*output_p(ii,end- 2);
    
    output_p(ii,end- 2)= output_p(ii,end- 1);
    output_p(ii,end-1) = output_p(ii,end);
    
    data = y;
end

output = y;


% outputArg1 = inputArg1;
% outputArg2 = inputArg2;
end

