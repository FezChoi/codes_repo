clear; clc;
%% Define
G = 0:0.01:10; % average packet generation rate
Users = 200; % number of users
GenerationRate = G ./ Users; % packet generation rate
FrameTime = 1; % length of packet

%% Pure ALOHA
RealTime = 0:0.01:10;
PureALOHA = zeros(1,length(G));
for i = 2:length(G)
    NumberPackets = round(G(i)*length(RealTime)); % total number of packets generated
    RandomTimeIndex = rand(1,NumberPackets)*10;
    PacketTimeIndex = sort(RandomTimeIndex);
    PacketTimeDiffLeft = diff(PacketTimeIndex);
    PacketTimeDiffRight = diff(circshift(PacketTimeIndex, 1));
    NumberSuccessPackets = sum((PacketTimeDiffLeft > FrameTime) & (PacketTimeDiffRight > FrameTime));
    PureALOHA(i) = NumberSuccessPackets;
end

plot(G, PureALOHA);





%%
% 
% Packets = round(G .* Users); 
% RandomTimeIndex = round(rand(1,Packets)*100, 2);
% PacketTimeIndex = sort(RandomTimeIndex); % time index of generated packets
% PacketTimeDiffLeft = diff(PacketTimeIndex);
% PacketTimeDiffRight = diff(circshift(PacketTimeIndex, 1));
% 
% for i = 2:length(G)
%     NumberPackets = round(G(i)*Users); % number of packets generated in unit time
%     
%     RandomTimeIndex = round(rand(1,NumberPackets)*10, 2);
%     PacketTimeIndex = sort(RandomTimeIndex); % time index of generated packets
%     
%     SuccessPackets = sum((PacketTimeDiffLeft > FrameTime(i))&(PacketTimeDiffRight > FrameTime(i)));
%     PureALOHA(i) = SuccessPackets * FrameTime(i);
% end
% 
% figure(1);
% plot(G,PureALOHA);



%% Slotted ALOHA



