function [YM,RSQ] = calYM(path,hObject, eventdata, handles)
xdata=textread(path);
x1=xdata(:,1);
y1=xdata(:,2);
d1=xdata(:,[1,2]);
d2=xdata(:,[3,4]);
%% ###
str1=get(handles.popupmenu4,"String");
value1=get(handles.popupmenu4, 'value');
lb=str2num(str1{value1});
str2=get(handles.popupmenu5,"String");
value2=get(handles.popupmenu5, 'value');
ub=str2num(str2{value2});
border1=0.1;
border2=100;
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
slope=abs(slope);
cpx=0;cpy=0;
fity=[];
flag=true;
num=[];
while flag
    border1;border2;
    border=(border1+border2)/2;
    if border2-border1<0.0001
        YM=-1;RSQ=-1;
        return;
    end
    num=[num,border];
    flag1=true;
    for i=1:length(slope)
        %if abs((slope(i)-max(slope(1:i-1)))/max(slope(1:i-1)))>5
        %%%%%%0.8的阈值可能得再讨论一下qwq  
        if abs((slope(i)))>border
            if (i/length(slope))<lb
                border1=border;  
                flag1=false;
                break; 
            end
            if (i/length(slope))>ub
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
%% 拟合
a=str2num(get(handles.edit7,"String"));
b=str2num(get(handles.edit8,"String"));
a=a/180*pi;
f=fittype('(2/pi)*tan(h)*(E)*t^2','independent','t','coefficients',{'E'},'problem', {'h'});
fitx1=fitx-fitx(1);
fity1=fity-fity(1);
[cfun,gof]=fit(fitx1,fity1,f,'problem',{a}); %显示拟合函数，数据必须为列向量形式
y_get=cfun(fitx1);
y_get=y_get+fity(1);
YM=cfun.E*(1-b^2);
RSQ=gof.adjrsquare;
end

