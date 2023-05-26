#!/bin/bash
echo "=================Interchanged================="

echo "==================size 512=============================="

gcc -O0 ./interchange/512.cpp -o out
./out

echo "==================size 1024=============================="

gcc -O0 ./interchange/1024.cpp -o out
./out

echo "==================size 2048=============================="

gcc -O0 ./interchange/2048.cpp -o out
./out


echo "=================Blocked================="

echo "==================size 512=============================="

gcc -O0 ./block/512.cpp -o out
./out

echo "==================size 1024=============================="

gcc -O0 ./block/1024.cpp -o out
./out

echo "=================Blocked Interchange================="

echo "==================size 512=============================="

gcc -O0 ./interchange_block/512.cpp -o out
./out

echo "==================size 1024=============================="

gcc -O0 ./interchange_block/1024.cpp -o out
./out

