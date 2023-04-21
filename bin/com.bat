@ECHO OFF

ECHO Starting building...

start /B /wait g++ ../src/*.cpp ../lib/media/*.cpp ../lib/user/*.cpp -o main.exe

ECHO Project compiled.
ECHO Runing project...

start /wait main.exe

ECHO Program terminated.