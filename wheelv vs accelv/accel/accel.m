clear;  
clf;
close all;
rawSpeed = csvread('brakePIDMarch9Slip8.5kP0.02kI0.06kD0min73Accel0.9.csv',1);
%rawSpeed = csvread('brakePIDMarch8ManualSmart.csv',1);
wheelVelR = rawSpeed(:,1);
wheelVelF = rawSpeed(:,2);
accelVel = rawSpeed(:,3);
braking = rawSpeed(:,4);

[val1, peakv1] = max(movmean(wheelVelR(1:length(wheelVelR)*0.7),200));
[val2, peakv2] = max(movmean(wheelVelR(peakv1+100:end),200));
start1 = peakv1-10
len1 =  500;
start2 = peakv2-10 + peakv1+100
len2 = 500;
startEnd = [1 length(wheelVelR),
    start1 start1+len1,
    start2 start2+len2 ];
%startEnd = startEnd(1:2,:);
for i = 1:3
    figure;
    plot(wheelVelR(startEnd(i,1):startEnd(i,2))/100,'b');
    hold on;
    plot(wheelVelF(startEnd(i,1):startEnd(i,2))/100,'r');
    plot(accelVel(startEnd(i,1):startEnd(i,2))/100,'g');
    ylabel('velocity [mph]')
    
    ylim([-1 20]);
    yyaxis right;
    hold on;
    
    plot(braking(startEnd(i,1):startEnd(i,2)),'Color',[1 0.5 0]);
    ylim([-1 3]);
    legend('wheel velocity rear [mph]', 'wheel velocity front [mph]', 'accel velocity', 'braking');
    
    ylabel('braking')
    grid on;
end
grid on;
