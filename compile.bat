g++ main.cpp -O2 -D LOCAL  -D _GLIBCXX_DEBUG -o manual.exe -std=c++17 >compile.stdout 2>compile.stderr
@echo off
echo "IN =>" 

echo "OUT =>"
manual <in