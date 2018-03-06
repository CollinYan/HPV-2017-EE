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
perSlipA = rawSpeed(:,7);
perSlipFW = rawSpeed(:,8);
startEnd = [1000 length(rawSpeed)-1000
    1700 2200
    2300 2700
    2700 2800
    2600 2900];
startEnd = startEnd(1:2,:);
for i = 1:length(startEnd)
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
    plot(perSlipA(startEnd(i,1):startEnd(i,2)),'c');
    plot(perSlipFW(startEnd(i,1):startEnd(i,2)),'y');
    ylim([-20 20]);
    legend('wheel velocity rear [mph]', 'wheel velocity front [mph]', 'accel-based velocity [mph]', 'brake position', 'brake PID', 'slipA', 'slipFW');
    ylabel('brake position and %wheel slip')
end

