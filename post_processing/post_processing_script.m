figure(1)

subplot(2,2,1)
plot(Structure1Response.time, Structure1Response.signals.values(:,3))
xlabel('Time (s)')
ylabel('Z-Direction Displacement (m)')
title('Float Response')

subplot(2,2,2)
plot(Structure1Response.time, Structure2Response.signals.values(:,3))
xlabel('Time (s)')
ylabel('Z-Direction Displacement (m)')
title('Plate Response')

subplot(2,2,3)
plot(Structure1Response.time, RelativeMotion.signals.values(:,1))
xlabel('Time (s)')
ylabel('Z-Direction Relative Motion (m)')
title('Relative Motion')

