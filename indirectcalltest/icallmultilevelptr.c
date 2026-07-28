// multi_level_ptr.c
#include <stdio.h>
#include <stdlib.h>

void target1() { printf("Reached target 1\n"); }
void target2() { printf("Reached target 2\n"); }
void target3() { printf("Reached target 3\n"); }

// 复杂的三级指针结构
void*** create_pointer_maze(int path) {
    void*** level3 = malloc(sizeof(void**));
    void** level2 = malloc(sizeof(void*));
    void* level1;
    
    // 根据路径选择不同的目标
    switch (path % 3) {
        case 0: level1 = target1; break;
        case 1: level1 = target2; break;
        case 2: level1 = target3; break;
    }
    
    *level2 = level1;
    *level3 = level2;
    
    return level3;
}

// 复杂的控制流影响指针赋值
void setup_pointers(void**** ptr, int depth) {
    if (depth == 0) {
        *ptr = create_pointer_maze(rand());
        return;
    }
    
    void*** temp = malloc(sizeof(void**));
    setup_pointers(&temp, depth - 1);  // 递归设置
    
    // 在运行时决定如何连接指针
    if (depth % 2 == 0) {
        *ptr = temp;
    } else {
        void** intermediate = malloc(sizeof(void*));
        *intermediate = *(void**)temp;  // 额外解引用层
        *ptr = intermediate;
    }
}

int main() {
    srand((unsigned int)time(NULL));
    
    printf("Multi-level pointer indirection:\n");
    
    for (int i = 0; i < 5; i++) {
        void*** maze = NULL;
        
        // 创建复杂的指针迷宫
        setup_pointers(&maze, 3 + (i % 2));  // 动态深度
        
        // 多级解引用 - 静态分析极难跟踪
        void (*func)() = (void (*)())(*(void**)(*maze));
        func();  // 间接调用
        
        // 清理内存（简化）
        free(*(void**)maze);
        free(*maze);
        free(maze);
    }
    
    return 0;
}