insert into Student values('1561401613',N'毛挺','男','18','2015',N'计联');
insert into Student values('1530561331',N'谈力','男','18','2015',N'计联');
insert into Student values('1530501085',N'晁阳','男','19','2015',N'计联');
insert into Student values('1530591376',N'韩梅梅','女','17','2015',N'计科');

insert into Course values('1008060',N'算法','10001',2,'2','2019');
insert into Course values('1203006',N'计组','10003',1,'2','2018');
insert into Course values('3009405',N'java','20010',2,'1','2020');
insert into Course values('7787564',N'经济学','35790',1,'1','2020');

insert into Teacher values('10001',N'颜老师',N'算法');
insert into Teacher values('10003',N'毛老师',N'计组');
insert into Teacher values('20010',N'张老师',N'java');
insert into Teacher values('35790',N'田老师',N'经济学');

ALTER TABLE choose
CHANGE COLUMN ChooseYear ChooseYear INT NULL;
insert into Choose values('1561401613','1008060','10001',95,null);
insert into Choose values('1561401613','1203006','10003',92,null);
insert into Choose values('1561401613','3009405','20010',94,null);
insert into Choose values('1530561331','1008060','10001',96,null);
insert into Choose values('1530561331','1203006','10003',88,null);
insert into Choose values('1530591376','1203006','10003',94,null);
insert into Choose values('1530591376','3009405','20010',92,null);

insert into Permission1  values('1561401613','111111');
insert into Permission1  values('1530561331','222222');
insert into Permission1  values('1530501085','333333');
insert into Permission1  values('1530591376','444444');

insert into Permission2  values('10001','555555');
insert into Permission2  values('10003','666666');
insert into Permission2  values('30405','777777');
insert into Permission2  values('35790','888888');

insert into Permission3  values('24680','100000');