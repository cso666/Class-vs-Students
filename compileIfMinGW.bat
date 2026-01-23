@echo off
cd "%~dp0"
"%~dp0/MinGW64/bin/windres.exe" app.rc -O coff app.res
"%~dp0/MinGW64/bin/g++.exe" -static main.cpp app.res -o main.exe -std=c++14
del app.res
pause