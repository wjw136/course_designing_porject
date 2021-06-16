clc,clear;
close all;
xdata=textread("data\1\t 2_25.txt");
d1=xdata(:,[1,2]);
d2=xdata(:,[3,4]);
%% 画图
x1=xdata(:,1);
y1=xdata(:,2);
Force_pt = plot(x1',y1','*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','r');
hold on;
x1=xdata(:,3);
y1=xdata(:,4);
Force_pt = plot(x1',y1','*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','g');
hold on;
%% 落差
[d2_sort,to]=sortrows(d2,1);
x1_sort=d2_sort(:,1);
y1_sort=d2_sort(:,2);
diff=[];
tmp=0;
% 70和12500需要讨论qwq
for i =2:length(x1_sort)
    tmp=(y1_sort(i-1)-y1_sort(i));
    if tmp>70&&x1_sort(i)<12500
        diff=[diff,i];
    end
end
ans_diff=[];
diffx2=[];
diffx1=[];
for i =1:length(diff)
    index=diff(i);
    plot([x1_sort(index-1),x1_sort(index)],[y1_sort(index-1),y1_sort(index)],'linewidth',1 , 'color','b');
    ans_diff=[ans_diff,y1_sort(index-1)-y1_sort(index)];
    diffx1=[diffx1,x1_sort(index-1)];
    diffx2=[diffx2,x1_sort(index)];
    hold on;
end
ans_diff
diffx1