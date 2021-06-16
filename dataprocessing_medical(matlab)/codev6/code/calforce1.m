function ans_diff = calforce1(path)
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
    ans_diff=[ans_diff,y2_sort(index-1)-y2_sort(index)];
    diffx1=[diffx1,x2_sort(index-1)];
    diffx2=[diffx2,x2_sort(index)];
end
ans_diff=num2str(ans_diff);

end

