clear;  
clf;
close all;
rawSpeed = csvread('data pid (Autosaved).csv',1);;
wheelVelR = rawSpeed(:,1);
wheelVelF = rawSpeed(:,2);
accelVel = rawSpeed(:,3);
brakePos = rawSpeed(:,4);
brakePID = rawSpeed(:,5);
braking = rawSpeed(:,6);
perSlipFW = rawSpeed(:,7);
error = rawSpeed(:,8);
outputSum = rawSpeed(:,9);
output = rawSpeed(:,10);

startEnd = [1000 length(rawSpeed)-1000]
startEnd = startEnd(1:2,:);
for i = 1:1
    figure;
    plot(wheelVelR(startEnd(i,1):startEnd(i,2)),'b');
    hold on;
    plot(wheelVelF(startEnd(i,1):startEnd(i,2)),'r');
    plot(accelVel(startEnd(i,1):startEnd(i,2)),'g');
    ylabel('velocity [mph]')
    plot(brakePos(startEnd(i,1):startEnd(i,2)),'m');
    plot(brakePID(startEnd(i,1):startEnd(i,2)),'k');
    ylim([-100 1000]);
    yyaxis right;
    hold on;
    plot(perSlipFW(startEnd(i,1):startEnd(i,2)),'c');
    plot(error(startEnd(i,1):startEnd(i,2)),'y');
    plot(outputSum(startEnd(i,1):startEnd(i,2)),'y');
    ylim([-20 20]);
    legend('wheel velocity rear [mph]', 'wheel velocity front [mph]', 'accel-based velocity [mph]', 'brake position', 'brake PID', 'slipFW', 'error', 'outputSum', 'output');
    ylabel('brake position and %wheel slip and errors')
end

