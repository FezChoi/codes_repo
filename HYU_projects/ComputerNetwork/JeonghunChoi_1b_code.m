clear; clc;
%% Variables
ArrivalRate = [0, 0.25, 0.5, 0.75, 1, 1.5, 2, 3, 4]; % given arrival rate, packets/slot

%% Calculate Throughput
SuccessPacket = zeros(length(ArrivalRate),length(ArrivalRate)); % 9x9 Table

ptr1 = 1; % data pointer for G1
for G1 = ArrivalRate % packets per slot
    ptr2 = 1;        % data pointer for G2
    for G2 = ArrivalRate % packets per slot
        Arrival_G = G1 + G2; % total average packets generated each slot.
        
        Nonarrival_G1 = exp(-G1); % non-arrival rate for G1
        Nonarrival_G2 = exp(-G2); % non-arrival rate for G2
        NoPacket = Nonarrival_G1 * Nonarrival_G2; % no packets in channel
       
        SuccessPacket(ptr1, ptr2) = Arrival_G * NoPacket; % total Throughput

        ptr2 = ptr2 + 1; % increase the pointer
    end
    ptr1 = ptr1 + 1; % increase the pointer
end    

%% Plot the Graph
disp(SuccessPacket); % display the Throughput table, each row for G1, each column for G2.
plot(ArrivalRate, SuccessPacket); % 2-dimentional graph
xlabel('ArrivalRate (G1)'); % x-axis is G1
ylabel('Throughput');       % y-axis is Throughput or Efficiency