@ECHO OFF

ECHO Starting building...

start /B /wait g++ src/*.cpp lib/media/*.cpp lib/user/*.cpp -o bin/main.exe

ECHO Project compiled.
ECHO Runing project...

start /wait bin/main.exe

ECHO Program terminated.
