g++ main.cpp -Wl,--stack,200000000 -O2 -o main.exe -std=c++17 
@echo off
echo "IN =>" 
type in
echo "OUT =>"
main <in