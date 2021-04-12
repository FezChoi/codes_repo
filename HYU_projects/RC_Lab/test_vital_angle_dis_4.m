%% test vital _angle distance

para.freqslope =  40.8450012207031251e6*1e6;%49.209e6*1e6; % % MHz/us
para.samplerate = 3000e3; %3280e3;%%ksps
para.bw =3.746303561822511e9;  %2952.54e6;%1798.92e6;  %MHz
para.chirploops= 2;
para.adcsample = 256;%100;
para.fps = 20;  %FPS
para.startfreq =60.25e9; % 60.25;% GHz
para.c = 3e8;   %299792458;
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

aa= '20200724_3_10_dummy_30deg_30deg_HR120_BR40.bin';
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
end

%% Background subtraction remove clutter

rawdata_removed = zeros(size(raw_fft1d_4));
alpha_clutter = 0.01;
for iii = 1
    for jj = 1+1:datalength
        rawdata_removed(iii,:,jj) = raw_fft1d_4(iii,:,jj)*alpha_clutter + (1-alpha_clutter )*rawdata_removed(iii,:,jj-1);
    end
end
range_max=[16,72];%[54,67];
if (1)
    rawdata_removed_amp= (squeeze(raw_fft1d_4(1,1:Nfft/2,100:end) -rawdata_removed(1,1:Nfft/2,100:end))) ;
else
    rawdata_removed_amp= (squeeze(raw_fft1d_4(1,1:Nfft/2,100:end)));
end

[~,target.maxvarpoint]=max(var(abs(squeeze(raw_fft1d_4(1,1:326,:))),[],2));
target.maxvarpoint_m = time_vector_m(target.maxvarpoint);

%%

Fs = 20;  % Sampling Frequency

Fstop = 0.1;             % Stopband Frequency
Fpass = 0.2;             % Passband Frequency
Dstop = 0.1;          % Stopband Attenuation
Dpass = 0.57501127785;  % Passband Ripple
dens  = 20;              % Density Factor

% Calculate the order from the parameters using FIRPMORD.
[N, Fo, Ao, W] = firpmord([Fstop, Fpass]/(Fs/2), [0 1], [Dstop, Dpass]);

% Calculate the coefficients using the FIRPM function.
RespHPF  = firpm(N, Fo, Ao, W, {dens});

%% fdesign bandpass

bandpassSpecs= fdesign.bandpass('Fst1,Fp1,Fp2,Fst2,Ast1,Ap,Ast2',0.01,0.1,0.5,0.6,2,1,2);
bpFilter = design(bandpassSpecs,'butter','matchexactly','passband','SystemObject',true);
bpFilter.SOSMatrix;

%% 

raw_br = squeeze(  raw_fft1d_4(1,1:Nfft/2,100:end));
view_p = [target.maxvarpoint];

raw_br_phase = zeros(1,size(raw_br,2));
for ii = 1:size(raw_br,2)
    raw_br_phase(ii) = angle(rawdata_removed_amp(view_p,ii));
end

raw_br_phase_unw  = unwrap(raw_br_phase(1,:)' );

%% remove impulses noise

raw_br_phase_rmN = raw_br_phase_unw;
for ii =3:length(raw_br_phase_unw)
   raw_br_phase_rmN(ii)  = filter_removeImpluseNoise(raw_br_phase_unw(ii-2),...
                                                                            raw_br_phase_unw(ii-1), raw_br_phase_unw(ii), 0.4 );
end

raw_br_phase_unw_dis = raw_br_phase_rmN;%*para.lambda/(4*pi);

%% IIR filter BR

filtercoef = [1,0,-1,1,-1.850099942932254,0.868089891124046;...
                   1,0,-1,1,-1.963154313093595,0.964395116008088];
scaleVals = [0.115921965026776, 0.031242409616612,1];

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

raw_br_phase_unw_iir_freq = fft(raw_br_phase_unw_iir,512);

%% IIR filter HR

filtercoef_hr = [1.0000, 0, -1.0000, 1.0000, -0.5306, 0.5888;
                       1.0000, 0, -1.0000, 1.0000, -1.8069, 0.8689;
                       1.0000, 0, -1.0000, 1.0000, -1.4991, 0.5887;
                       1.0000, 0, -1.0000, 1.0000, -0.6654, 0.2099 ];
scaleVals_hr = [0.4188, 0.4188, 0.3611, 0.3611, 1.0000];
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

raw_br_phase_unw_iir_hr_freq = fft(raw_br_phase_unw_iir_hr,512);

%% figure

figure(33);
figs.row=3;

subplot(figs.row,1,1)
tmp = abs(rawdata_removed_amp);
mesh( tmp , [0 90]);
yticks([1:10:fftsize/2]);
yticklabels(round(time_vector_m([1:10:fftsize/2]) ,2));
ylim([max(0,target.maxvarpoint-30),min(target.maxvarpoint+30, Nfft/2) ]);
xlabel('Slow time')
ylabel('Distance')

subplot(figs.row,1,2)
plot([raw_br_phase_unw_dis';raw_br_phase_unw_iir']')

subplot(figs.row,1,3)
plt.x = linspace( 0,20,256)*60/2; % index / 256 * 600 -> 0 ~ 600
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
xlabel('Slow time')
ylabel('Distance')


%% bandpass filter

Fs = 20;
n = 5;
Wn = [14/60 37/60];
Fn = Fs/2;
ftype = 'bandpass';
[b, a] = butter(n, Wn/Fn, ftype);


%%
% raw_br_phase_unw_iir_rmN = raw_br_phase_unw_iir;
% for ii =5:length(raw_br_phase_unw_iir)
%    raw_br_phase_unw_iir_rmN(ii)  = filter_removeImpluseNoise2(raw_br_phase_unw(ii-2),...
%                                                                             raw_br_phase_unw(ii-1), raw_br_phase_unw(ii), 0.4 );
% end
% 

%%
figure(44);

win = zeros(1,512);
win(1,1:50) = hamming(50); % 10 ~ 40

d_length = length(raw_br_phase_unw);
arr_tmp = zeros(d_length-199,1);
cnt = 0;

for ii = 1:(d_length-199)
    Margin = ii;
    Margin_end = ii+199;
    
    tmp = raw_br_phase_unw_iir(Margin:Margin_end,1)';
    tmp = filter(b,a,tmp);
    tmp = abs(fft(tmp,512));%.*win;
    
    [br_v1, br_i1] = max(tmp);
    arr_tmp(ii,1) = br_i1/256*600;
end

plt2.x = linspace(0,300,d_length-199);
plot(plt2.x, arr_tmp');axis([0 300 0 50]);


hold on
arr_tmp_mean = zeros(length(arr_tmp),1);
for ii = 200:(length(arr_tmp)-199) 
   arr_tmp_mean(ii)  = mean(arr_tmp(ii-199:ii+199,1)); % mean 400frame
end
plot(plt2.x, arr_tmp_mean');axis([0 300 0 50]);


% load('ECGdata_20200731_5_54_7');
% tmptmp = zeros(300,1);
% for ii = 10:(300-9)
%     tmptmp(ii) = mean(ECGdata_20200731_5_54_7(ii-9:ii+9,1));
% end
% plot(1:300,ECGdata_20200731_5_54_7','Color','b');
% plot(1:300,tmptmp','Color','g');
hold off
