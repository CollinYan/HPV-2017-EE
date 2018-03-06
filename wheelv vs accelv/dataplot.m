clear;  
clf;
close all;
rawSpeed = csvread('accel v and wheel v comparison 2.csv',1);;
wheelVel = rawSpeed(:,5);
accelVel = rawSpeed(:,6);
brakePos = rawSpeed(:,7);
braking = rawSpeed(:,8);
perSlip = rawSpeed(:,9);
startEnd = [1000 1500 
    1700 2200
    2300 2700
    2800 3300
    3600 3950];
for i = 1:5
    figure;
    plot(wheelVel(startEnd(i,1):startEnd(i,2)),'b');
    hold on;
    plot(accelVel(startEnd(i,1):startEnd(i,2)),'r');
    ylabel('velocity [mph]')
    yyaxis right;
    plot(brakePos(startEnd(i,1):startEnd(i,2)),'g');
    hold on;
    plot(perSlip(startEnd(i,1):startEnd(i,2)),'m');
    legend('wheel velocity [mph]', 'accel-based velocity [mph]', 'brake position', '% wheel slip');
    ylabel('brake position and %wheel slip')
end
%%
%plot (rawSpeed(startI:endI,2));
hold on;
%plot (errorMM(:)*100);
hold on;
plot(errorAverageRef*100);
%plot ( error(startI:endI)*100);
%plot ( movmeanerror(startI:endI)*100);
ylabel('% error');
ylim([-10 10]);

yyaxis right;
plot(rawSpeed(startI:endI,1));
hold on;
plot(movmeanSpeed,'g');
ylabel('speed [mph]');
xlabel('samples');
legend('diff','error','speed','speed smoothed');
ax = gca;
set(ax,'Fontsize', 24);