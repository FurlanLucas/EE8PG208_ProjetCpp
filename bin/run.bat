@echo off
setlocal EnableDelayedExpansion

rem Dispay the number of lines in all .cpp and .h files -------------------------
set cmd="findstr /R /N "^^" ..\lib\media\*.cpp ..\lib\media\*.h ..\lib\user\*.cpp ..\lib\user\*.h ..\src\*.cpp ..\src\*.h | find /C ":""
for /f %%a in ('!cmd!') do set number=%%a
echo Total number of lines: %number%


rem Cunt the number of files ---------------------------------------------------
set counter=0
for %%A in (..\src\*.cpp ..\lib\media\*.cpp ..\lib\user\*.cpp) do set /a counter+=1
echo cpp files count = %counter%

set counter=0
for %%A in (..\src\*.h ..\lib\media\*.h ..\lib\user\*.h) do set /a counter+=1
echo header files count = %counter%

set counter=0
for %%A in (..\src\*.h ..\src\*.cpp) do set /a counter+=1
echo src files = %counter%

set counter=0
for %%A in (..\lib\media\*.cpp ..\lib\user\*.cpp ..\lib\media\*.h ..\lib\user\*.h) do set /a counter+=1
echo lib files = %counter%


rem Compile all files -----------------------------------------------------------
echo Starting building...
start /B /wait g++ ../src/*.cpp ../lib/media/*.cpp ../lib/user/*.cpp -o main.exe
echo Project compiled.

rem Run the application ---------------------------------------------------------
echo Runing project...
start /wait main.exe
echo Program terminated.