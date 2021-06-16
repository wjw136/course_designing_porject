clc,clear;
close all;
xdata=textread("C:\Users\ASUS\Desktop\代码\数据及代码\data\data\1\t 6_40.txt");
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
x1_end_indice=[];
for i=1:length(x1_sort)-50
    x1_end_indice=[x1_end_indice,dsearchn(x1_sort,x1_sort(i)+1000)];
end
% for i = 2:length(d1_sort)
%     if x1_sort(i)-tmp>100||i==length(d1_sort)
%         tmp=x1_sort(i);
%         index=[index,i];
%     end
% end\
x1_end_indice;
x_fit=[];
y_fit=[];
slope=[];
for i = 1:length(x1_end_indice)
    x_e=x1_end_indice(i);
    x_fit=x1_sort(i:x_e);
    y_fit=y1_sort(i:x_e);
    p=polyfit(x_fit,y_fit,1);
    slope=[slope,p(1)];
end
slope=abs(slope)
cpx=0;cpy=0;
fity=[];
flag=true;
num=[];

while flag
    border1;border2;
    border=(border1+border2)/2;
    if border2-border1<0.0001
        f=warndlg('wrong input');
        return;
    end
    num=[num,border];
    flag1=true;
    for i=1:length(slope)
        %if abs((slope(i)-max(slope(1:i-1)))/max(slope(1:i-1)))>5
        %%%%%%0.8的阈值可能得再讨论一下qwq  
        if abs((slope(i)))>border
            if (i/length(slope))<0.3
                border1=border;  
                flag1=false;
                break; 
            end
            if (i/length(slope))>0.7
                border2=border;
                flag1=false;
                break; 
            end
            cpx=x1_sort(i);
            endx_index=dsearchn(x1_sort,cpx+1000);
            fitx=x1_sort(i:endx_index);
            cpy=y1_sort(i);fity=y1_sort(i:endx_index);
            flag=false;
            break;
        end
    end
    if flag==true&&flag1==true
        border2=border;
    end
end
border;
cpx;
cpy;
scatter([cpx],[cpy],40,'o','k','filled');
plot([cpx,cpx],[cpy,max(y1_sort)],'linewidth',1 , 'color','y');
hold on;
%% 拟合
syms t
f=fittype('(2/pi)*tan(h)*(E/(1-d))*t^2','independent','t','coefficients',{'E'},'problem', {'h','d'});
fitx1=fitx-fitx(1);
fity1=fity-fity(1);
[cfun,gof]=fit(fitx1,fity1,f,'problem',{10,0.25}) %显示拟合函数，数据必须为列向量形式
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