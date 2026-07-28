// runtime_calculation.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void function_a() { printf("Called function A\n"); }
void function_b() { printf("Called function B\n"); }
void function_c() { printf("Called function C\n"); }
void function_d() { printf("Called function D\n"); }

// 函数指针数组
void (*functions[])() = { function_a, function_b, function_c, function_d };

// 复杂的运行时计算决定调用目标
int calculate_target_index() {
    // 使用多种运行时因素计算索引
    int factors[5];
    
    // 1. 当前时间
    time_t t = time(NULL);
    factors[0] = (t % 4);
    
    // 2. 堆地址的随机性
    int* heap_val = malloc(sizeof(int));
    factors[1] = ((long)heap_val % 4);
    free(heap_val);
    
    // 3. 栈地址
    int stack_val;
    factors[2] = ((long)&stack_val % 4);
    
    // 4. 伪随机数
    factors[3] = (rand() % 4);
    
    // 5. 复杂的数学计算
    double x = (double)t / 1000.0;
    factors[4] = ((int)(sin(x) * 1000) % 4);
    
    // 非线性组合
    int result = 0;
    for (int i = 0; i < 5; i++) {
        result = (result * 31 + factors[i]) % 4;
    }
    
    // 添加分支，使分析更复杂
    if (result < 0) result = -result;
    if (result >= 4) result = result % 4;
    
    return result;
}

int main() {
    srand((unsigned int)time(NULL));
    
    printf("Runtime-calculated indirect calls:\n");
    
    for (int i = 0; i < 5; i++) {
        // 静态分析无法确定调用目标
        int index = calculate_target_index();
        functions[index]();  // 难以静态分析
        
        // 进一步混淆：基于前一次调用的结果
        if (index % 2 == 0) {
            functions[(index + 1) % 4]();  // 嵌套间接调用
        }
    }
    
    return 0;
}