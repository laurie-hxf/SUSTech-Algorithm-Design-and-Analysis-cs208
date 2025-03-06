#!/bin/bash

# 编译 C++ 程序
javac GenerateTestData.java
g++ -o your_sort Main.cpp
javac StandardQuickSort.java



# if diff -q output_custom.out output_standard.out; then
#     echo "Test Passed"
# else
#     echo "Test Failed"
# fi

# 批量测试 (5个测试用例)
for i in {1..5}; do
# 单个测试用例
    java GenerateTestData data.in_$i
    ./your_sort < data.in_$i > output_custom_$i.out
    java StandardQuickSort < data.in_$i > output_standard_$i.out
    
    if diff -q "output_custom_$i.out" "output_standard_$i.out"; then
        echo "Case $i: Passed"
    else
        echo "Case $i: Failed"
    fi
done