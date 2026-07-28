// jump_table.c
#include <stdio.h>

// 各种操作函数
void operation1() { printf("Executing operation 1\n"); }
void operation2() { printf("Executing operation 2\n"); }
void operation3() { printf("Executing operation 3\n"); }
void operation4() { printf("Executing operation 4\n"); }
void default_operation() { printf("Unknown operation\n"); }

// 函数指针类型定义
typedef void (*OperationFunc)();

// 跳转表
OperationFunc jump_table[] = {
    operation1,
    operation2, 
    operation3,
    operation4
};

void execute_operation(int op_code) {
    if (op_code >= 0 && op_code < 4) {
        jump_table[op_code]();  // 通过跳转表间接调用
    } else {
        default_operation();
    }
}

int main() {
    printf("=== Function Pointer Array/Jump Table Example ===\n");
    
    // 通过不同的操作码进行间接调用
    // for (int i = 0; i <= 5; i++) {
    //     printf("Operation code %d: ", i);
    //     execute_operation(i);
    // }
     for (int i = 0; i < 2; i++) {
        printf("Operation code %d: ", i);
        execute_operation(i);
    }   
    return 0;
}