clear;  
clf;
close all;
rawSpeed = csvread('brakePIDMarch8Slip8.5kP0.02kI0.06kD0min73.csv',1);
%rawSpeed = csvread('brakePIDMarch8ManualSmart.csv',1);
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

[val1, peakv1] = max(movmean(wheelVelR(1:length(wheelVelR)/2),10));
[val2, peakv2] = max(movmean(wheelVelR(peakv1+100:end),10));
start1 = peakv1-10
len1 =  150;
start2 = peakv2-10 + peakv1+100
len2 = 150;
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
    %plot(brakePos(startEnd(i,1):startEnd(i,2))/10,'m');
    %plot(brakePID(startEnd(i,1):startEnd(i,2))/10,'c');
    
    %plot(outputSum(startEnd(i,1):startEnd(i,2))/10,'r');    
    
    ylim([-1 20]);
    yyaxis right;
    hold on;
    plot(braking(startEnd(i,1):startEnd(i,2)),'k');
    %plot(perSlipFW(startEnd(i,1):startEnd(i,2))/100,'Color',[1 0.5 0]);
    %plot(error(startEnd(i,1):startEnd(i,2))/100,'g');
    ylim([-1 2]);
    legend('wheel velocity rear [mph]', 'wheel velocity front [mph]', 'accel-based velocity', 'braking');   %legend('wheel velocity rear [mph]', 'wheel velocity front [mph]', 'accel-based velocity [mph]', 'brake position', 'brake PID' , 'outputSum', 'output', ...         
    %    'slipFW', 'error');
    ylabel('brake position and %wheel slip and errors')
    grid on;
end
grid on;
