#!/bin/bash

# 编译 C++ 程序

#javac GenerateTestData.java
g++ -o me Main.cpp
# g++ -o Force Force.cpp
#g++ -o your_sort Main.cpp
javac Main.java
#g++ -o your_sort ../hw4.2/Main.cpp



# if diff -q output_custom.out output_standard.out; then
#     echo "Test Passed"
# else
#     echo "Test Failed"
# fi



while true; do
    all_passed=true
    for i in {1..10}; do
        echo "Running test case $i..."

        # 生成测试数据
        python3 Generate.py > data_$i.in

        # 运行你的排序程序和标准排序程序
        ./me < data_$i.in > output_custom_$i.out
        # ./Force < data_$i.in > output_standard_$i.out
#        ./standard < data.in_$i > output_standard_$i.out
        java Main.java < data_$i.in > output_standard_$i.out

        # 对比结果
        if diff -q "output_custom_$i.out" "output_standard_$i.out" > /dev/null; then
            echo "Case $i: Passed"
        else
            echo "Case $i: Failed"
            echo "Input:"
#            cat data.in_$i
            echo "Your Output:"
            cat output_custom_$i.out
            echo "Standard Output:"
            cat output_standard_$i.out
            all_passed=false
            break
        fi
    done

    if [ "$all_passed" = false ]; then
        echo "Stopping testing due to failure."
        break
    fi
done
