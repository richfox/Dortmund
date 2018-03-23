@echo off

rem author: xfu date: 16.01.2013 email: tech@zhongwenshu.de
rem delete all the folders under usr\work

F:
cd F:\usr\Work
for /d %%i in (*) do rd /s /q %%i

echo [all the folders under usr\work are deleted!]


rem pause