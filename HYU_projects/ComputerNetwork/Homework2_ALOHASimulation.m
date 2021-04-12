Lambda = 0:0.01:10;          % x-axis
Users = 200;                 % given number of users
PacketRate = Lambda / Users; % lambda = n x p

PureALOHA = Lambda .* exp(-2*Lambda); % 2 slots for 1 packet success
SlotALOHA = Lambda .* exp(-Lambda);   % 1 slot for 1 packet success

[PureMax, PureIdx] = max(PureALOHA);  % find max point
PureMaxPercent = round(PureMax * 100, 2); % change to the real value
PureIdxReal = (PureIdx - 1) * 0.01;
[SlotMax, SlotIdx] = max(SlotALOHA);  % find max point
SlotMaxPercent = round(SlotMax * 100, 2);
SlotIdxReal = (SlotIdx - 1) * 0.01;

figure(1);
subplot(311)
plot(Lambda, PureALOHA, 'Color', '#0072BD'); % pure ALOHA graph
title('Pure ALOHA');
xlabel(['Max value is : ', num2str(PureMaxPercent),...
        '% when lamda = ', num2str(PureIdxReal)]);

subplot(312)
plot(Lambda, SlotALOHA, 'Color', '#D95319'); % slotted ALOHA graph
title('Slotted ALOHA');
xlabel(['Max value is : ', num2str(SlotMaxPercent),...
        '% when lamda = ', num2str(SlotIdxReal)]);

subplot(313) % compare both graphs
plot(Lambda, PureALOHA);
hold on
plot(Lambda, SlotALOHA);
title('Comparison');