@echo off
cd /d "%~dp0"
if not exist dist mkdir dist
pushd src
windres app.rc -o ../dist/app-resource.o
if errorlevel 1 exit /b 1
popd
gcc -O2 -Wall -Wextra -Werror -municode -mwindows -static -s src/main.c dist/app-resource.o -o dist/WorkEarnings.exe -lgdi32 -luser32
if errorlevel 1 exit /b 1
echo Built dist\WorkEarnings.exe
