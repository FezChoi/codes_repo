%% test vital _angle distance

para.freqslope =  
para.samplerate = 
para.bw =
para.chirploops= 
para.adcsample =
para.fps =
para.startfreq =
para.c = 
para.lambda = para.c/(para.bw/2 + para.startfreq); %meter
para.rangereso = para.c/2/para.bw;
para.rangemax = para.samplerate*para.c/2/para.freqslope;
para.tc = para.bw/para.freqslope;  %second
para.velocitymax = para.lambda/4/para.tc;
para.velocityreso = para.lambda/2/para.tc/para.chirploops;

Nfft = 2^nextpow2(1024);
para.freqs = para.startfreq:para.freqslope:(para.startfreq+para.freqslope*(Nfft-1));
Ts = 1/Nfft/( para.bw/Nfft   +1e-16); %Avoid nan checks
time_vector = 0:Ts:Ts*(Nfft-1);
time_vector_m = time_vector *1.5e8/2/(Nfft/512);

aa= '20200723_17_00_5_60deg.bin';
RawData = readDCA1000(aa,para.adcsample);

datalength = 1200*5; % 5min. No of Frames

rawdata = reshape(RawData,4,[], datalength);
rawdata_1= reshape(rawdata,4,para.adcsample,[],datalength);

%% mean clutter remove

rawdata_CR = zeros(size(rawdata_1));
for iii = 1%:4
    for jj = 1:datalength
        rawdata_CR(iii,:,:,jj) = rawdata_1(iii,:,:,jj) - mean( rawdata_1(iii,:,:,jj),3 );
    end
end

%%

fftsize = Nfft;
raw_fft1d_4 = zeros(1,fftsize,datalength);
rawdata_CR_3 = reshape(rawdata_CR,4,[],datalength);
rawdata_CR_3 = rawdata;

%% range fft

for ii = 1:datalength
        raw_fft1d_4(1,:,ii) = fft( squeeze(rawdata_CR_3(1,para.adcsample*1+1:para.adcsample*2 ,ii)) , fftsize ) ;
%         raw_fft1d_4(1,:,ii) = fft( squeeze(rawdata_CR_3(1,1:para.adcsample ,ii)) , fftsize ) ;
%     end
end
% end
%
% figure; mesh( abs(squeeze(raw_fft1d_4(1,1:256,100:end))), [0 90]);
% yticks([0:10:fftsize/2]);
% yticklabels(round(time_vector_m([1:10:fftsize/2]) ,2));
% % xticks([1:1200])
% ylim([1,256])
% xlabel('Slow time')
% ylabel('Distance')
%% Background subtraction remove clutter
rawdata_removed = zeros(size(raw_fft1d_4));
alpha_clutter = 
for iii = 1
    for jj = 1+1:datalength
        rawdata_removed(iii,:,jj) = raw_fft1d_4(iii,:,jj)*alpha_clutter + (1-alpha_clutter )*rawdata_removed(iii,:,jj-1);
    end
end
range_max=[16,72];%[54,67];
if (1)
    rawdata_removed_amp= (squeeze(raw_fft1d_4(1,1:Nfft/2,100:end) -rawdata_removed(1,1:Nfft/2,100:end))) ;
%     [target_amp, target_index ] = max(abs(rawdata_removed_amp(range_max(1):range_max(2),:)));
%     target_index = target_index + range_max(1) - 1;
else
    rawdata_removed_amp= (squeeze(raw_fft1d_4(1,1:Nfft/2,100:end)));
%     [target_amp, target_index ] = max(abs(rawdata_removed_amp(range_max(1):range_max(2),:)));
%     target_index = target_index + range_max(1) - 1;
end
% tmp = ;
% raw_fft1d_4
[~,target.maxvarpoint]=max(var(abs(squeeze(raw_fft1d_4(1,1:326,:))),[],2));
% [~,target.maxvarpoint]=max(var(abs(rawdata_removed_amp),[],2));
target.maxvarpoint_m = time_vector_m(target.maxvarpoint);
%%
% tmp = abs(squeeze(raw_fft1d_4(1,1:256,100:end) -rawdata_removed(1,1:256,100:end)));
% tmp = abs(rawdata_removed_amp);
% figure(12); mesh( tmp , [0 90]);
% yticks([1:10:fftsize/2]);
% yticklabels(round(time_vector_m([1:10:fftsize/2]) ,2));
% % xticks([1:1200])
% % ylim([1,256])
% xlabel('Slow time')
% ylabel('Distance')
%%
Fs = 20;  % Sampling Frequency

Fstop =              % Stopband Frequency
Fpass =              % Passband Frequency
Dstop =              % Stopband Attenuation
Dpass =              % Passband Ripple
dens  =              % Density Factor

% Calculate the order from the parameters using FIRPMORD.
[N, Fo, Ao, W] = firpmord([Fstop, Fpass]/(Fs/2), [0 1], [Dstop, Dpass]);

% Calculate the coefficients using the FIRPM function.
RespHPF  = firpm(N, Fo, Ao, W, {dens});
%% fdesign bandpass
bandpassSpecs= fdesign.bandpass('Fst1,Fp1,Fp2,Fst2,Ast1,Ap,Ast2',0.01,0.1,0.5,0.6,2,1,2);
% designmethods(bandpassSpecs,'Systemobject',true)
% designoptions(bandpassSpecs,'butter')
bpFilter = design(bandpassSpecs,'butter','matchexactly','passband','SystemObject',true);
% fvtool(bpFilter)
bpFilter.SOSMatrix;
%%
% N= 2;                % order of prototype LPF
% fcenter= 0.3;         % Hz center frequency
% bw= .4;              % Hz -3 dB bandwidth
% fs= 20;             % Hz sample frequency
% [a,K]= biquad_bp(N,fcenter,bw,fs);
%%
% N= 4;                % order of prototype LPF
% fcenter= 2.05;         % Hz center frequency
% bw= 3.9;              % Hz -3 dB bandwidth
% fs= 20;             % Hz sample frequency
% [a,K]= biquad_bp(N,fcenter,bw,fs);
%% 
raw_br = squeeze(  raw_fft1d_4(1,1:Nfft/2,100:end));
% raw_br_abs = abs(raw_br);
% [~,raw_br_ind ]= max(raw_br_abs(25:31,:) ) ;
% raw_br_ind = raw_br_ind+25+1;

% figure;mesh(abs(raw_br),[0,90])
% view_p = 98;%
view_p = [target.maxvarpoint];
% [199 297]
% raw_br_phase = (imag(raw_br([20,28,29],:)));
% raw_br_phase = atan(imag(raw_br(view_p,:)) ./real(raw_br(view_p,:)));
%  atan2(imag(h), real(h));
% raw_br_phase = atan2(imag(raw_br(view_p,:)) ,real(raw_br(view_p,:)));

raw_br_phase = zeros(1,size(raw_br,2));
for ii = 1:size(raw_br,2)
% raw_br_phase(ii) = angle( raw_br(target_index(ii),ii));
% raw_br_phase(ii) = angle(raw_br(view_p, ii));
% raw_br_phase(ii) = angle(rawdata_removed_amp(target_index(ii),ii));
raw_br_phase(ii) = angle(rawdata_removed_amp(view_p,ii));
end

raw_br_phase_unw  = unwrap(raw_br_phase(1,:)' );

% raw_br_phase_unw = raw_br_phase_unw - mean(raw_br_phase_unw);
% raw_br_phase_unw = movmean(raw_br_phase_unw, 600);

% raw_br_phase_unw = diff(raw_br_phase_unw);
% raw_br_phase_unw  = unwrap(raw_br_phase_rmN(1,:)' );
% figure;plot(raw_br_phase_unw)
% tempcorrection=0;
% for ii = 2:length(raw_br_phase)
% [raw_br_phase_unw(ii) , tempcorrection ]= unwrap_ti(raw_br_phase(1,ii) ,raw_br_phase(1,ii-1), tempcorrection );
% end

% raw_br_phase = imag(raw_br([20,28,29],:));
% figure;plot( raw_br_phase(1,:))

% raw_br_phase = diff(raw_br_phase);
%% remove impulses noise
% raw_br_phase_rmN = raw_br_phase;
% for ii =3:length(raw_br_phase)
%    raw_br_phase_rmN(ii)  = filter_removeImpluseNoise(raw_br_phase(ii-2),raw_br_phase(ii-1),raw_br_phase(ii),1.5);
% end
% 
raw_br_phase_rmN = raw_br_phase_unw;
for ii =3:length(raw_br_phase_unw)
   raw_br_phase_rmN(ii)  = filter_removeImpluseNoise(raw_br_phase_unw(ii-2),...
                                                                            raw_br_phase_unw(ii-1), raw_br_phase_unw(ii), 0.4 );
end

% figure;plot([raw_br_phase(1:1000) ; raw_br_phase_rmN((1:1000))']')
% figure;plot([raw_br_phase_unw' ; raw_br_phase_rmN'  ]')



% figure;plot( [raw_br_phase;raw_br_phase_unw(:,1)']')
% xu = raw_br_phase(1,:);
% for i = 2:size(raw_br_phase,2)
%         dif= raw_br_phase(1,i) - raw_br_phase(1,i-1);
%         if dif > pi
%             xu(i:end) = xu(i:end) - pi;
%         elseif dif < -pi
%             xu(i:end) = xu(i:end) + pi;
%         end
% end


% figure;plot([raw_br_phase ;xu]')
% figure; plot(diff(xu))
% raw_br_phase_unw = xu;
% figure;plot( raw_br_phase_unw(:,1))
raw_br_phase_unw_dis = raw_br_phase_rmN;%*para.lambda/(4*pi);
% raw_br_phase_unw_dis = movmean(raw_br_phase_unw_dis, 20);
% raw_br_phase_unw_dis = raw_br_phase_unw_dis-mean(raw_br_phase_unw_dis);
% figure;plot( raw_br_phase_unw_dis)

%% IIR filter BR
filtercoef = [];
scaleVals = [];
% filtercoef = [1,0,-1,1,-1.9632,0.9644;...
%                    1,0,-1,1,-1.8501,0.8681];
% scaleVals = [0.0602, 0.0602,1];
output_p = zeros(2,3);

raw_br_phase_unw_iir = zeros(size(raw_br_phase_unw_dis));
for ii =1:(length(raw_br_phase_unw))
    [raw_br_phase_unw_iir(ii),output_p] = filter_IIR_biquadCascade(...
        raw_br_phase_unw_dis(ii), ...
        filtercoef,...
        scaleVals,...
        output_p, ...
        2 );
end

% figure;plot(raw_br_phase_unw_iir)

% figure;plot([raw_br_phase_unw_dis';raw_br_phase_unw_iir']')
% raw_br_phase_unw_iir_freq = fft(raw_br_phase_unw_iir,512);
% plt.x = linspace( 0,20,256)*60/2;
% figure;plot(plt.x,  normalize( abs(raw_br_phase_unw_iir_freq(1:256) ) ,'range'),...
%                 'LineWidth',1.5)
% xlabel('Frequency (cycles/minute)')
% ylabel('Magnitude')
% xlim([0,100])

% raw_br_phase_unw_dis_RESPHPF = conv(raw_br_phase_unw_dis , RespHPF', 'same');
% figure;plot(raw_br_phase_unw_dis_RESPHPF );
%% IIR filter HR
% N= 4;                % order of prototype LPF
% fcenter= 2.4;         % Hz center frequency
% bw= 3.2;              % Hz -3 dB bandwidth
% fs= 20;             % Hz sample frequency
% [a,K]= biquad_bp(N,fcenter,bw,fs)
% filtercoef_hr = [];
% scaleVals_hr = [];

filtercoef_hr = [];
scaleVals_hr = [];
output_p_hr = zeros(4,3);
 raw_br_phase_unw_iir_hr = raw_br_phase_unw_dis;
for ii =1:(length(raw_br_phase_unw))
    [raw_br_phase_unw_iir_hr(ii),output_p_hr] = filter_IIR_biquadCascade(...
        raw_br_phase_unw_dis(ii), ...
        filtercoef_hr,...
        scaleVals_hr,...
        output_p_hr, ...
        4 );
end
% figure;plot((raw_br_phase_unw_iir_hr))

raw_br_phase_unw_iir_hr_freq = fft(raw_br_phase_unw_iir_hr,512);
plt.x = linspace( 0,20,256)*60/2;
% figure;plot(plt.x,  abs(raw_br_phase_unw_iir_hr_freq(1:256) ) ,...
%                 'LineWidth',1.5)
% xlabel('Frequency (cycles/minute)')
% ylabel('Magnitude')
% xlim([0,200])

%% figure
figure(33);
figs.row=3;
subplot(figs.row,1,1)
tmp = abs(rawdata_removed_amp);
mesh( tmp , [0 90]);
yticks([1:10:fftsize/2]);
yticklabels(round(time_vector_m([1:10:fftsize/2]) ,2));
% xticks([1:1200])
% ylim([1,250])
ylim([max(0,target.maxvarpoint-30),min(target.maxvarpoint+30, Nfft/2) ]);
xlabel('Slow time')
ylabel('Distance')
% title( sprintf('file=%s, target index = %d -> %.2f(m)',...
%     filename.name{filename.ind}(1:end-4),...
%     target.maxvarpoint,...
%     target.maxvarpoint_m))
subplot(figs.row,1,2)
plot([raw_br_phase_unw_dis';raw_br_phase_unw_iir']')
raw_br_phase_unw_iir_freq = fft(raw_br_phase_unw_iir,512);
plt.x = linspace( 0,20,256)*60/2;
subplot(figs.row,1,3)
plot(plt.x,  normalize( abs(raw_br_phase_unw_iir_freq(1:256) ) ,'range'),...
    'LineWidth',1.5)
hold on;
plot(plt.x,  normalize(abs(raw_br_phase_unw_iir_hr_freq(1:256) ) ,'range') ,...
    'LineWidth',1.5)
hold off;
xlabel('Frequency (cycles/minute)')
ylabel('Magnitude')
xlim([0,130])

%%
tmp = abs(squeeze(raw_fft1d_4(1,1:256,100:end) -rawdata_removed(1,1:256,100:end)));
tmp = abs(rawdata_removed_amp);
figure(12); mesh( tmp , [0 90]);
yticks([1:10:fftsize/2]);
yticklabels(round(time_vector_m([1:10:fftsize/2]) ,2));
% xticks([1:1200])
% ylim([1,256])
xlabel('Slow time')
ylabel('Distance')



