CREATE TABLE Student (  
  SID varchar(10) NOT NULL ,
  Sname nvarchar(10) NOT NULL ,  
  Sex nvarchar(5) NOT NULL DEFAULT '男', 
  SchoolAge int NOT NULL,  
  SchoolYear int NOT NULL ,  
  Class  nvarchar(20) NOT NULL ,  
  primary key(SID)
);
-- 触发器
DELIMITER $
create trigger studentcheck before insert on Student for each row
begin
if new.schoolAge<15 or new.schoolAge>30 then set new.schoolAge=20;end if;
if new.Sex<>'男' and new.Sex<>'女' then set new.Sex='男';end if;
end 
$
DELIMITER ;

CREATE TABLE Course (  
  CID varchar(7) NOT NULL ,  
  Cname nvarchar(10) NOT NULL ,  
  TID varchar(5) NOT NULL ,  
  Credit int NOT NULL ,  
  Grade  varchar(30) NOT NULL ,  
  CancelYear  int NULL ,  
  primary key(CID)
);

CREATE TABLE Teacher (  
  TID varchar(5) NOT NULL ,  
  Tname nvarchar(10) NOT NULL ,  
  Course nvarchar(10) NOT NULL , 
  primary key(TID)
);

CREATE TABLE Choose (  
  SID varchar(10) NOT NULL,  
  CID varchar(7) NOT NULL,  
  TID varchar(5) NOT NULL ,  
  Score int NULL ,  
  ChooseYear  int NOT NULL ,  
  foreign key(SID) references Student(SID),
  foreign key(CID) references Course(CID),
  foreign key(TID) references Teacher(TID)
);
-- 外键约束(外键<主键表)
CREATE TABLE Permission1 (  
  SID varchar(10) NOT NULL , 
  SPW varchar(10) NOT NULL ,  
  primary key(SID)
);
CREATE TABLE Permission2 (   
  TID varchar(5) NOT NULL ,
  TPW varchar(10) NOT NULL , 
  primary key(TID)
);
CREATE TABLE Permission3 (  
  MID varchar(7) NOT NULL ,  
  MPW varchar(10) NOT NULL , 
  primary key(MID)
);