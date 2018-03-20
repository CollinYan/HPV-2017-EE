clear;  
clf;
close all;
%rawSpeed = csvread('brakePIDMarch8Slip8kP0.02kI0.06kD0min70.csv',1);
rawSpeed = csvread('brakePIDMarch9ManualSmart.csv',1);
wheelVelR = rawSpeed(:,4);
wheelVelF = rawSpeed(:,5);
accelVel = rawSpeed(:,6);
brakePos = rawSpeed(:,7);
brakePID = rawSpeed(:,8);
braking = rawSpeed(:,9);
perSlipFW = rawSpeed(:,10);
error = rawSpeed(:,1);
outputSum = rawSpeed(:,2);
output = rawSpeed(:,3);
slipCalc = (wheelVelF-wheelVelR)./wheelVelF*100;
%{
wheelVelR = rawSpeed(:,1);
wheelVelF = rawSpeed(:,2);
slipCalc = (wheelVelF-wheelVelR)./wheelVelF*100;
accelVel = rawSpeed(:,3);
brakePos = rawSpeed(:,4);
brakePID = rawSpeed(:,5);
braking = rawSpeed(:,6);
perSlipFW = rawSpeed(:,7);
error = rawSpeed(:,8);
outputSum = rawSpeed(:,9);
output = rawSpeed(:,10);
%}
t = linspace(0,150,151)*50/1000;
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
lineWidth = 2;
for i = 2:3
    figure;
    plot(t,wheelVelR(startEnd(i,1):startEnd(i,2))/100,'b','LineWidth',lineWidth);
    hold on;
    plot(t,wheelVelF(startEnd(i,1):startEnd(i,2))/100,'r','LineWidth',lineWidth);
    %plot(accelVel(startEnd(i,1):startEnd(i,2))/100,'g');
    ylabel('velocity [mph]')
    
    %plot(brakePID(startEnd(i,1):startEnd(i,2))/10,'c');
    
    ylim([-1 20]);
    yyaxis right;
    hold on;
    plot(t,(brakePos(startEnd(i,1):startEnd(i,2))-90)/(175-90)*100,'Color',[0.4 0.8 0.6],'LineWidth',lineWidth);
    plot(t,slipCalc(startEnd(i,1):startEnd(i,2)),'-','Color',[1 0.5 0],'LineWidth',lineWidth);
    
    ylim([-5 105]);
    legend('wheel velocity rear [mph]', 'wheel velocity front [mph]', 'brake position', 'error');

    ylabel('slip')
    grid on;
    xlabel('time [s]');
end
grid on;
