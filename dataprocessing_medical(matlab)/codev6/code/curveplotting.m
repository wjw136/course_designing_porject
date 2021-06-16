clc,clear;
close all;
xdata=textread("C:\Users\ASUS\Desktop\代码\数据及代码\data\min\s1_4.txt");
d1=xdata(:,[1,2]);
d2=xdata(:,[3,4]);
%% 画图
x1=xdata(:,1);
y1=xdata(:,2);
y1 = smoothdata(y1,'gaussian',20);

Force_pt = plot(x1',y1','*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','r');
hold on;
x2=xdata(:,3);
y2=xdata(:,4);
Force_pt = plot(x2',y2','*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','g');
hold on;
border1=0.1;
border2=100;
%% 
%%find cp(用分段斜率变化)
[d1_sort,to]=sortrows(d1,1);
x1_sort=d1_sort(:,1);
y1_sort=d1_sort(:,2);
y1_sort = smoothdata(y1_sort,'gaussian',20);
index=[];
tmp=x1_sort(1);
for i = 2:length(d1_sort)
    if x1_sort(i)-tmp>100||i==length(d1_sort)
        tmp=x1_sort(i);
        index=[index,i];
    end
end
x_b=1;
x_e=1;
x_fit=[];
y_fit=[];
slope=[];
for j = 2:length(index)
    x_e=index(j);
    x_fit=x1_sort(x_b:x_e);
    y_fit=y1_sort(x_b:x_e);
    p=polyfit(x_fit,y_fit,1);
    slope=[slope,p(1)];
    x_b=x_e;
end
slope=abs(slope);
cpx=0;cpy=0;
fity=[];
flag=true;
num=[];
while flag
border=((border1)+border2)/2;
num=[num,border];
for i=1:length(slope)-11
    %if abs((slope(i)-max(slope(1:i-1)))/max(slope(1:i-1)))>5
    %%%%%%0.8的阈值可能得再讨论一下qwq 
    if abs((slope(i)))>border
        if (i/length(slope))<0.6
            i;
            border1=border;
            break; 
        end
        if i/length(slope)>0.9
            border2=border;
            break;
        end
        cpx=x1_sort(index(i));fitx=x1_sort(index(i):index(i+10));
        cpy=y1_sort(index(i));fity=y1_sort(index(i):index(i+10));
        flag=false;
        break;
    end
end
if length(fity)==0
    border2=border
end
end
border
cpx;
cpy;
scatter([cpx,x1_sort(index(i))],[cpy,y1_sort(index(i))],40,'o','k','filled');
plot([cpx,cpx],[cpy,max(y1_sort)],'linewidth',1 , 'color','y');
hold on;
%% 拟合
syms t
f=fittype('(2/pi)*tan(20)*(E/(1-0.25))*t^2','independent','t','coefficients',{'E'});
fitx1=fitx-fitx(1);
fity1=fity-fity(1);
[cfun,gof]=fit(fitx1,fity1,f) %显示拟合函数，数据必须为列向量形式
cfun.E
gof.sse
y_get=cfun(fitx1);
y_get=y_get+fity(1);
Force_pt_fit = plot(fitx,y_get,'*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','c');


% figure
% 
% plot(x,y,'r*',xi,yi,'b-');
% 
% title('拟合函数图形');
% 
% figure
% 
% plot(x,sqrt(y-yi(1:1:18,:).^2/18),'r*');
% 
% title('标准误差图');