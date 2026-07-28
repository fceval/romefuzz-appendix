// function_pointer.c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int calculate(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);  // 间接调用
}

int main() {
    int x = 10, y = 5;
    
    // 定义函数指针
    int (*func_ptr)(int, int);
    
    // 第一种间接调用方式
    func_ptr = add;
    printf("Addition: %d\n", func_ptr(x, y));
    
    // 第二种间接调用方式
    func_ptr = multiply;
    printf("Multiplication: %d\n", func_ptr(x, y));
    
    // 第三种间接调用方式（作为参数）
    printf("Calculate add: %d\n", calculate(x, y, add));
    printf("Calculate multiply: %d\n", calculate(x, y, multiply));
    
    return 0;
}