clear;  
clf;
close all;

rawSpeed = csvread('brakePIDMarch9Slip9kP0.02kI0.06kD0min73.csv',1);
%rawSpeed = csvread('brakePIDMarch8ManualSmart.csv',1);

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
%{

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
%}
t = linspace(0,130,131)*50/1000;
[val1, peakv1] = max(movmean(wheelVelR(1:length(wheelVelR)/2),10));
[val2, peakv2] = max(movmean(wheelVelR(peakv1+100:end),10));
start1 = peakv1-10
len1 =  130;
start2 = peakv2-10 + peakv1+100
len2 = 130;
startEnd = [1 length(wheelVelR),
    start1 start1+len1,
    start2 start2+len2 ];
%startEnd = startEnd(1:2,:);
lineWidth = 2;
h = animatedline('Color','b','LineWidth',lineWidth);
h2 = animatedline('Color','r','LineWidth',lineWidth);
h3 = animatedline('Color',[0.4 0.8 0.6],'LineWidth',lineWidth);
h4 = animatedline('Color','k','LineWidth',lineWidth);
h5 = animatedline('Color',[1 0.5 0],'LineWidth',lineWidth);
 legend('wheel velocity rear [mph]', 'wheel velocity front [mph]', ...
        'brake position',  'output', 'slip');    
axis([0, 8, -1, 21])
i=2;
a = tic; % start timer
for k = startEnd(i,1):startEnd(i,2)
    addpoints(h,t(k-startEnd(i,1)+1),wheelVelR(k)/100);
    addpoints(h2,t(k-startEnd(i,1)+1),wheelVelF(k)/100);
    addpoints(h3,t(k-startEnd(i,1)+1),(brakePos(k)-90)/(175-90)*10);
    addpoints(h4,t(k-startEnd(i,1)+1),(output(k)-90)/(175-90)*10);
    addpoints(h5,t(k-startEnd(i,1)+1),perSlipFW(k)/100);
    b = toc(a); % check timer
    while b < (1/20) 
        b = toc(a); % check timer
        drawnow % update screen every 1/30 seconds
    end
    a = tic; % reset timer after updating
end

for i = 2:3
    figure;
    plot(t,wheelVelR(startEnd(i,1):startEnd(i,2))/100,'b','LineWidth',lineWidth);
    hold on;
    plot(t,wheelVelF(startEnd(i,1):startEnd(i,2))/100,'r','LineWidth',lineWidth);
    ylabel('velocity [mph]')
    ylim([-1 21]);
    
    yyaxis right;
    plot(t,(brakePos(startEnd(i,1):startEnd(i,2))-90)/(175-90)*100,'Color',[0.4 0.8 0.6],'LineWidth',lineWidth);
    hold on;
    plot(t,(output(startEnd(i,1):startEnd(i,2))-90)/(175-90)*100,'-k','LineWidth',lineWidth);
    plot(t,perSlipFW(startEnd(i,1):startEnd(i,2))/100,'-','Color',[1 0.5 0],'LineWidth',lineWidth);
    ylim([-5 105]);
    ylabel('brake position and %wheel slip')
    
    xlabel('time [s]');
    legend('wheel velocity rear [mph]', 'wheel velocity front [mph]', ...
        'brake position',  'output', 'slip');    
    grid on;
end
