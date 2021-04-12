clear; clc;
%% Preset
Users = 200;
PacketLength = 1;

%% ALOHA simulation
Cursor = 1; %data cursor for arrays
for p = 0:0.0001:1 %arrival rate (per unit time)
    G(Cursor) = Users * p; %average arrival rate (per unit time)
    
    % Pure ALOHA
    TimeSlot = 0.01;
    PacketDuration = PacketLength / TimeSlot; %number of slots for 1 packet
    ArrivalRate = p * TimeSlot; %arrival rate (per time slot)
    NoArrivalRate = (1 - ArrivalRate) ^ Users; %probability of no arrival packets from all users
    NoPacket = NoArrivalRate ^ (2*PacketDuration); %probability of idle time for 2 packet duration
    SuccessPacketPure(Cursor) = G(Cursor) * NoPacket; %probability of packet success
    
    % Slotted ALOHA
    TimeSlot = 1;
    PacketDuration = TimeSlot; %1 slot for 1 packet
    ArrivalRate = p * TimeSlot; %arrival rate (per time slot)
    NoArrivalRate = (1 - ArrivalRate) ^ Users; %probability of no arrival packets from all users
    NoPacket = NoArrivalRate ^ (PacketDuration); %probability of idle time for 1 time slot
    SuccessPacketSlot(Cursor) = G(Cursor) * NoPacket; %probability of packet success
    
    Cursor = Cursor + 1; %increase data cursor
end

%% Find max point
[Vmax, Vidx] = max(SuccessPacketPure);  
PureMaxVal = Vmax; 
PureMaxIdx = (Vidx - 1) * 0.02; %change to the real value
[Vmax, Vidx] = max(SuccessPacketSlot);
SlotMaxVal = Vmax; 
SlotMaxIdx = (Vidx - 1) * 0.02; %change to the real value

%% Draw graph
figure(1);
plot(G,SuccessPacketPure);
text(PureMaxIdx, PureMaxVal, ['\leftarrow Pure ALOHA',...
    ' (G = ', num2str(PureMaxIdx), ', Th = ', num2str(round(PureMaxVal*100,2)),'%)']);
hold on
plot(G,SuccessPacketSlot);
text(SlotMaxIdx, SlotMaxVal, ['\leftarrow Slotted ALOHA',...
    ' (G = ', num2str(SlotMaxIdx), ', Th = ', num2str(round(SlotMaxVal*100,2)),'%)']);
axis([0 10 0 0.4]);
title("Pure ALOHA & Slotted ALOHA Simulation");
xlabel("G");
ylabel("Throughput");

%%
