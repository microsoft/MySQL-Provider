@Echo Off
Setlocal EnableDelayedExpansion
Echo Usage: 
Echo demo: sql.bat HostName TotalRepeatCount
Echo eg. sql.bat m50p-ora5-02.scx.com 
Echo Create table
c:\temp\mysql.exe -h %1 -E -e "use employees;create table Test02(id int(4) not null primary key auto_increment,name char(20) not null);"

Echo Alter table Engine
c:\temp\mysql.exe -h %1 -E -e "use employees;ALTER TABLE Test02 ENGINE=MYISAM;"

SET _TotalCount=%2
:_Repeat
If %_TotalCount% equ 0 GOTO :_EndInsert
Set /a _TotalCount-=1
Echo insert values
c:\temp\mysql.exe -h %1 -E -e "use employees;insert into Test02(name) values('!_RndAlphaNum!');"
c:\temp\mysql.exe -h %1 -E -e "use employees;insert into Test02(name) values('!_RndAlphaNum!');"
c:\temp\mysql.exe -h %1 -E -e "use employees;insert into Test02(name) values('!_RndAlphaNum!');"
c:\temp\mysql.exe -h %1 -E -e "use employees;insert into Test02(name) values('!_RndAlphaNum!');"
c:\temp\mysql.exe -h %1 -E -e "use employees;insert into Test02(name) values('!_RndAlphaNum!');"
GOTO :_Repeat

:_EndInsert

Echo Alter DELAY_KEY_WRITE=0
c:\temp\mysql.exe -h %1 -E -e "use employees;Alter table Test02 DELAY_KEY_WRITE=1;"
Echo Drop table.
c:\temp\mysql.exe -h %1 -E -e "use employees;drop table Test02;"