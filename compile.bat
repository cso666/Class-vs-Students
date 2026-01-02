windres app.rc -O coff app.res
g++ main.cpp app.res -o main.exe
del app.res
pause