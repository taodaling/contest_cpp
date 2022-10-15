g++ main.cpp -O2 -D LOCAL -D _GLIBCXX_DEBUG -o manual.exe -std=c++17 
@echo off
echo "IN =>" 
type in
echo "OUT =>"
manual <in