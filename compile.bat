chcp 65001
windres app.rc -O coff app.res
g++ main.cpp -static app.res -o main.exe
del app.res
start start.bat
pause