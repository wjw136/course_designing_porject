TYPE=TRIGGERS
triggers='CREATE DEFINER=`root`@`localhost` trigger studentcheck before insert on Student for each row\nbegin\nif new.schoolAge<15 or new.schoolAge>30 then set new.schoolAge=20;end if;\nif new.Sex<>\'男\' and new.Sex<>\'女\' then set new.Sex=\'男\';end if;\nend'
sql_modes=1098907648
definers='root@localhost'
client_cs_names='utf8mb4'
connection_cl_names='utf8mb4_general_ci'
db_cl_names='utf8mb4_general_ci'
created=161961423913
