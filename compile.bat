chcp 65001
windres app.rc -O coff app.res
g++ main.cpp -static app.res -o main.exe -lgdi32 -DPICUSE -std=c++17
del app.res
pause