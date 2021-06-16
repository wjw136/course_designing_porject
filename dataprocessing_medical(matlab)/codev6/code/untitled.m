
function varargout = untitled(varargin)
clc;
warning('off');
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @untitled_OpeningFcn, ...
                   'gui_OutputFcn',  @untitled_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end
if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end

end
function untitled_OpeningFcn(hObject, eventdata, handles, varargin)
pushbutton5_Callback(hObject, eventdata, handles)
uitable_empty(hObject, eventdata, handles)
handles.output = hObject;
% Update handles structure
guidata(hObject, handles);
% UIWAIT makes untitled wait for user response (see UIRESUME)
% uiwait(handles.figure1);

%弹出窗口时就最大化
% javaFrame = get(gcf,'JavaFrame');
%  set(javaFrame,'Maximized',1);  

end
function varargout = untitled_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
end
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double

end
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end

%% 选择文件
function pushbutton1_Callback(hObject, eventdata, handles)
global stop;
stop=false;
cla reset;
set(handles.edit3,"Visible",false);
set(handles.edit2,"Visible",false);
set(handles.edit4,"Visible",false);
set(handles.edit1,'String',"");
single=get(handles.radiobutton2,"value")
if single==0
    global directory;
    directory = uigetdir('','选择指定文件夹：');
    subdir=dir(directory);
    length( subdir );
    is=true;
    for i = 1 : length( subdir )
        if stop==true
            stop=false;
            return;
        end
        if( isequal( subdir( i ).name, '.' ) ||  isequal( subdir( i ).name, '..' ) || subdir( i ).isdir )   % 如果是目录跳过
            continue;
        end
        % 找出子文件中的目标文件
        subdir(i).name;
        path=[directory '\' subdir(i).name];
        [YM,RSQ]=calYM(path,hObject, eventdata, handles);
        ans_diff=calforce1(path); %oldData
        YM=YM*1e3;
        str1=get(handles.popupmenu4,"String");
        value1=get(handles.popupmenu4, 'value');
        lb=str2num(str1{value1});
        str2=get(handles.popupmenu5,"String");
        value2=get(handles.popupmenu5, 'value');
        ub=str2num(str2{value2});
        if is
            newData=[{path,YM,RSQ,ans_diff,lb,ub}];
            is=false;
        else
            oldData=get(handles.uitable1,'Data');
            newData=[oldData;{path,YM,RSQ,ans_diff,lb,ub}];
        end
        set(handles.uitable1,'data',newData);
    end
end
if single==1
    global path;
    [file,path1]= uigetfile('.txt','选择指定文件：');
    path=[path1 '\' file];
    [YM,RSQ]=calYM(path,hObject, eventdata, handles);
    ans_diff=calforce1(path); %oldData
    YM=YM*1e3;
    str1=get(handles.popupmenu4,"String");
    value1=get(handles.popupmenu4, 'value');
    lb=str2num(str1{value1});
    str2=get(handles.popupmenu5,"String");
    value2=get(handles.popupmenu5, 'value');
    ub=str2num(str2{value2})
    newData=[{path,YM,RSQ,ans_diff,lb,ub}];
    set(handles.uitable1,'data',newData);
end
end

%% 画图
function pushbutton4_Callback(hObject, eventdata, handles)
path=get(handles.edit1,"String");
%% curveplotting
cla reset;
xdata=textread(path);
d1=xdata(:,[1,2]);
d2=xdata(:,[3,4]);
%%画图
x1=xdata(:,1);
y1=xdata(:,2);
% 高斯去噪
y1 = smoothdata(y1,'gaussian',20);
%y1=abs(y1).^(1/2)
Force_pt = plot(handles.axes1,x1',y1','*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','r');
hold on;
x1=xdata(:,3);
y1=xdata(:,4);
% 高斯去噪
% y1 = smoothdata(y1,'gaussian',15);
Force_pt = plot(handles.axes1,x1',y1','*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','g');
hold on;
calforce(hObject, eventdata, handles);
end

%% 清空
function pushbutton5_Callback(hObject, eventdata, handles)
set(handles.edit3,"Visible",false);
set(handles.edit2,"Visible",false);
set(handles.edit4,"Visible",false);
cla reset;
set(handles.edit1,'String',"");
uitable_empty(hObject, eventdata, handles);
end

%% 杨氏模量
function pushbutton6_Callback(hObject, eventdata, handles) 
border1=20;
border2=0.1;
path=get(handles.edit1,"String");
xdata=textread(path);
d1=xdata(:,[1,2]);
d2=xdata(:,[3,4]);
%%画图
x1=xdata(:,1);
y1=xdata(:,2);
x2=xdata(:,3);
y2=xdata(:,4);
hold on;
border1=0.1;
border2=100;
%% find cp(用分段斜率变化) ###
str1=get(handles.popupmenu4,"String");
value1=get(handles.popupmenu4, 'value');
lb=str2num(str1{value1});
str2=get(handles.popupmenu5,"String");
value2=get(handles.popupmenu5, 'value');
ub=str2num(str2{value2});
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
        f=warndlg('wrong input');
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
border;
cpx;
cpy;
scatter([cpx],[cpy],40,'o','k','filled');
plot([cpx,cpx],[cpy,max(y1_sort)],'linewidth',1 , 'color','y');
hold on;
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
Force_pt_fit = plot(handles.axes1,fitx,y_get,'*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','c');
set(handles.edit2,"String",['杨氏模量: ',num2str(cfun.E*(1-b^2)*1e3)]);
set(handles.edit2,"Visible",true);
set(handles.edit3,"String",['RSQ: ',num2str(gof.adjrsquare)]);
set(handles.edit3,"Visible",true);
set(handles.edit4,"Visible",false);
global ym;
ym=cfun.E*(1-b^2)*1e3;
global rsq;
rsq=gof.adjrsquare;
global lb;
str1=get(handles.popupmenu4,"String");
value1=get(handles.popupmenu4, 'value');
lb=str2num(str1{value1});
global ub;
str2=get(handles.popupmenu5,"String");
value2=get(handles.popupmenu5, 'value');
ub=str2num(str2{value2});
end

%% calculate力
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
path=get(handles.edit1,"String");

xdata=textread(path);
d1=xdata(:,[1,2]);
d2=xdata(:,[3,4]);
%% 落差
[d2_sort,to]=sortrows(d2,1);
x2_sort=d2_sort(:,1);
y2_sort=d2_sort(:,2);
diff=[];
tmp=0;
% 500和12500需要讨论qwq
for i =2:length(x2_sort)
    tmp=(y2_sort(i-1)-y2_sort(i));
    if tmp>500&&x2_sort(i)<12500
        diff=[diff,i];
    end
end
ans_diff=[];
diffx2=[];
diffx1=[];
for i =1:length(diff)
    index=diff(i);
    plot(handles.axes1,[x2_sort(index-1),x2_sort(index)],[y2_sort(index-1),y2_sort(index)],'linewidth',1 , 'color','b');
    ans_diff=[ans_diff,y2_sort(index-1)-y2_sort(index)];
    diffx1=[diffx1,x2_sort(index-1)];
    diffx2=[diffx2,x2_sort(index)];
    hold on;
end
set(handles.edit4,"String",['对应的落差值: ',num2str(ans_diff)]);
set(handles.edit4,"Visible",true);
set(handles.edit2,"String",['起点x坐标: ',num2str(diffx1)]);
set(handles.edit2,"Visible",true);
set(handles.edit3,"String",['终点x坐标: ',num2str(diffx2)]);
set(handles.edit3,"Visible",true);
end

%% cal力(无图)
function calforce(hObject, eventdata, handles)
path=get(handles.edit1,"String");
xdata=textread(path);
d1=xdata(:,[1,2]);
d2=xdata(:,[3,4]);
%% 落差
[d2_sort,to]=sortrows(d2,1);
x2_sort=d2_sort(:,1);
y2_sort=d2_sort(:,2);
diff=[];
tmp=0;
% 500和12500需要讨论qwq
for i =2:length(x2_sort)
    tmp=(y2_sort(i-1)-y2_sort(i));
    if tmp>500&&x2_sort(i)<12500
        diff=[diff,i];
    end
end
ans_diff=[];
diffx2=[];
diffx1=[];
for i =1:length(diff)
    index=diff(i);
    plot(handles.axes1,[x2_sort(index-1),x2_sort(index)],[y2_sort(index-1),y2_sort(index)],'linewidth',1 , 'color','b');
    ans_diff=[ans_diff,y2_sort(index-1)-y2_sort(index)];
    diffx1=[diffx1,x2_sort(index-1)];
    diffx2=[diffx2,x2_sort(index)];
    hold on;
end
end

%% uitable选择
function uitable1_CellSelectionCallback(hObject, eventdata, handles)
set(handles.edit3,"Visible",false);
set(handles.edit2,"Visible",false);
set(handles.edit4,"Visible",false);
cla reset;
set(handles.edit1,'String',"");
a=eventdata.Indices;
global row
if isempty(a)
    return;
end
row=a(1);
oldData=get(handles.uitable1,'Data');
path=cell2mat(oldData(row,1));
set(handles.edit1,'String',path);
pushbutton4_Callback(hObject, eventdata, handles);
end

%% uitable清空
function uitable_empty(hObject, eventdata, handles)
newData=[];
set(handles.uitable1,'data',newData)
end

%% import
function pushbutton8_Callback(hObject, eventdata, handles)
global row;
global ym
global rsq;
global lb;
global ub;
oldData=get(handles.uitable1,'Data');
oldData(row,2)={ym};
oldData(row,3)={rsq};
oldData(row,5)={lb};
oldData(row,6)={ub};
set(handles.uitable1,'Data',oldData);
end


%% 平滑force
function pushbutton9_Callback(hObject, eventdata, handles)
cla reset;
path=get(handles.edit1,"String");
%% curveplotting
cla reset;
xdata=textread(path);
d1=xdata(:,[1,2]);
d2=xdata(:,[3,4]);
%%画图
x1=xdata(:,1);
y1=xdata(:,2);
% 高斯去噪
y1 = smoothdata(y1,'gaussian',20);
Force_pt = plot(handles.axes1,x1',y1','*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','r');
hold on;
x1=xdata(:,3);
y1=xdata(:,4);
% 高斯去噪
y1 = smoothdata(y1,'gaussian',20);
Force_pt = plot(handles.axes1,x1',y1','*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','g');
hold on;

calforce(hObject, eventdata, handles);
end

%%
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

end

function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end


function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2
end


function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end



function popupmenu4_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu4 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu4
end


function popupmenu4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end



function popupmenu5_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu5 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu5
end


function popupmenu5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end


%% 重新计算
function pushbutton11_Callback(hObject, eventdata, handles)
global stop;
stop=false;
single=get(handles.radiobutton2,"value")
if single==0
    global directory;
    subdir=dir(directory);
    length( subdir );
    is=true;
    for i = 1 : length( subdir )
        if stop==true
            stop=false;
            return;
        end
        if( isequal( subdir( i ).name, '.' ) ||  isequal( subdir( i ).name, '..' ) || subdir( i ).isdir )   % 如果是目录跳过
            continue;
        end
        % 找出子文件中的目标文件
        subdir(i).name;
        path=[directory '\' subdir(i).name];
        [YM,RSQ]=calYM(path,hObject, eventdata, handles);
        ans_diff=calforce1(path); %oldData
        YM=YM*1e3;
        str1=get(handles.popupmenu4,"String");
        value1=get(handles.popupmenu4, 'value');
        lb=str2num(str1{value1});
        str2=get(handles.popupmenu5,"String");
        value2=get(handles.popupmenu5, 'value');
        ub=str2num(str2{value2});
        if is
            newData=[{path,YM,RSQ,ans_diff,lb,ub}];
            is=false;
        else
            oldData=get(handles.uitable1,'Data');
            newData=[oldData;{path,YM,RSQ,ans_diff,lb,ub}];
        end
        set(handles.uitable1,'data',newData);
    end
end
if single==1
    global path;
    [YM,RSQ]=calYM(path,hObject, eventdata, handles);
    ans_diff=calforce1(path); %oldData
    YM=YM*1e3;
    str1=get(handles.popupmenu4,"String");
    value1=get(handles.popupmenu4, 'value');
    lb=str2num(str1{value1});
    str2=get(handles.popupmenu5,"String");
    value2=get(handles.popupmenu5, 'value');
    ub=str2num(str2{value2})
    newData=[{path,YM,RSQ,ans_diff,lb,ub}];
    set(handles.uitable1,'data',newData);
end
end


%%
function edit7_Callback(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit7 as text
%        str2double(get(hObject,'String')) returns contents of edit7 as a double
end


function edit7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end

function edit8_Callback(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit8 as text
%        str2double(get(hObject,'String')) returns contents of edit8 as a double

end

function edit8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end

%% 手动选点
function pushbutton12_Callback(hObject, eventdata, handles)
[x,y]=ginput(1);
path=get(handles.edit1,"String");
xdata=textread(path);
d1=xdata(:,[1,2]);
[d1_sort,to]=sortrows(d1,1);
x_sort=d1_sort(:,1);
y_sort=d1_sort(:,2);
y_sort = smoothdata(y_sort,'gaussian',20);
x_b=dsearchn(x_sort,x);
x_e=dsearchn(x_sort,x+1000);
cpx=x_sort(x_b);cpy=y_sort(x_b);
fitx=x_sort(x_b:x_e);
fity=y_sort(x_b:x_e);
scatter([cpx],[cpy],40,'o','k','filled');
plot([cpx,cpx],[cpy,max(y_sort)],'linewidth',1 , 'color','y');
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
Force_pt_fit = plot(handles.axes1,fitx,y_get,'*' , ...
        'markersize',1 , ...
        'linewidth',1.5 , ...
        'color','c');
set(handles.edit2,"String",['杨氏模量: ',num2str(cfun.E*(1-b^2)*1e3)]);
set(handles.edit2,"Visible",true);
set(handles.edit3,"String",['RSQ: ',num2str(gof.adjrsquare)]);
set(handles.edit3,"Visible",true);
set(handles.edit4,"Visible",false);
global ym;
ym=cfun.E*(1-b^2)*1e3;
global rsq;
rsq=gof.adjrsquare;
global lb;
str1=get(handles.popupmenu4,"String");
value1=get(handles.popupmenu4, 'value');
lb=str2num(str1{value1});
global ub;
str2=get(handles.popupmenu5,"String");
value2=get(handles.popupmenu5, 'value');
ub=str2num(str2{value2});

end



function radiobutton2_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton2
end


% 停止
function pushbutton13_Callback(hObject, eventdata, handles)
global stop;
stop= true;
end
