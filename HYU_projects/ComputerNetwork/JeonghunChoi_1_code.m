clear; clc;
%% Variables
ArrivalRate = [0, 0.25, 0.5, 0.75, 1, 1.5, 2, 3, 4]; % given arrival rate, packets/slot

%% Calculate Throughput
SuccessPacket_a = zeros(length(ArrivalRate),length(ArrivalRate)); % 9x9 Table
SuccessPacket_b = zeros(length(ArrivalRate),length(ArrivalRate)); % 9x9 Table

ptr1 = 1; % data pointer for G1
for G1 = ArrivalRate % packets per slot
    ptr2 = 1;        % data pointer for G2
    for G2 = ArrivalRate % packets per slot
        % Problem 1(a)
        Nonarrival_even = exp(-G1); % non-arrival rate for even slots
        Nonarrival_odd  = exp(-G2); % non-arrival rate for odd slots
        Success_even = 1/2 * G1 * Nonarrival_even; % Throughput for even slots in the channel        
        Success_odd  = 1/2 * G2 * Nonarrival_odd;  % Throughput for odd slots in the channel
        SuccessPacket_a(ptr1, ptr2) = 1/2 * Success_even + 1/2 * Success_odd; % total Throughput

        % Problem 1(b)
        Arrival_G = G1 + G2; % total average packets generated each slot.        
        Nonarrival_G1 = exp(-G1); % non-arrival rate for G1
        Nonarrival_G2 = exp(-G2); % non-arrival rate for G2
        NoPacket = Nonarrival_G1 * Nonarrival_G2; % no packets in channel
        SuccessPacket_b(ptr1, ptr2) = Arrival_G * NoPacket; % total Throughput        
        
        ptr2 = ptr2 + 1; % increase the pointer
    end
    ptr1 = ptr1 + 1; % increase the pointer
end

%% Plot the graph
% Problem 1(a)
figure(1);
disp('Problem 1(a) Throughput Table');
disp(SuccessPacket_a); % display the Throughput table, each row for G1, each column for G2.
plot(ArrivalRate, SuccessPacket_a); % 2-dimentional graph
xlabel('ArrivalRate (G1)'); % x-axis is G1
ylabel('Throughput');       % y-axis is Throughput or Efficiency
title('Problem 1(a) Throughput Graph');

% Problem 1(b)
figure(2);
disp('Problem 1(b) Throughput Table');
disp(SuccessPacket_b); % display the Throughput table, each row for G1, each column for G2.
plot(ArrivalRate, SuccessPacket_b); % 2-dimentional graph
xlabel('ArrivalRate (G1)'); % x-axis is G1
ylabel('Throughput');       % y-axis is Throughput or Efficiency
title('Problem 1(b) Throughput Graph');
