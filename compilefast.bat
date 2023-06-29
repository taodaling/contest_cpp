g++ main.cpp -Wl,--stack,200000000 -O2 -o main.exe -std=c++17 -DLOCAL
@echo off
echo "IN =>" 

echo "OUT =>"
main <in