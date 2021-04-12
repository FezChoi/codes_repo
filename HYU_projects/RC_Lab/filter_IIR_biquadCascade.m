function [output ,output_p ] = filter_IIR_biquadCascade(data,filtercoef,scaleVals, output_p, num_stage)
%UNTITLED9 Summary of this function goes here
%   Detailed explanation goes here


% filtercoef = [];
% scaleVals = [];

% numCoefsStage = 6;
for ii = 1:num_stage
    index_tmp = ii;%numCoefsStage*(ii-1);
    b0 = filtercoef(index_tmp ,1);
    b1 = filtercoef(index_tmp ,2);
    b2 = filtercoef(index_tmp ,3);
    a1 = filtercoef(index_tmp ,5);
    a2 = filtercoef(index_tmp ,6);
    scaleV = scaleVals(ii);
    
%     output_p(ii) = ;
%     y  = ;
%     
%     output_p(ii +2) = output_p(ii+1);
%     output_p(ii +1) = output_p(ii );
%     data = y;
    
    output_p(ii,end) = ;
    y  = ;
    
    output_p(ii,end- 2)= output_p(ii,end- 1);
    output_p(ii,end-1) = output_p(ii,end);
    
    data = y;
end

output = y;


% outputArg1 = inputArg1;
% outputArg2 = inputArg2;
end
