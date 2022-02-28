g++ main.cpp -O2 -D LOCAL -o manual.exe   -std=c++17 >compile.stdout 2>compile.stderr
@echo off
echo "IN =>" 
type IN
echo "OUT =>"
manual <in