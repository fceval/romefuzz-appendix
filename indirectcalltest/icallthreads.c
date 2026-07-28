// thread_communication.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void task1() { printf("Task 1 executed by thread\n"); }
void task2() { printf("Task 2 executed by thread\n"); }
void task3() { printf("Task 3 executed by thread\n"); }

typedef void (*TaskFunc)();

// 共享数据
struct SharedData {
    pthread_mutex_t mutex;
    TaskFunc current_task;
    int command;
};

struct SharedData shared = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .current_task = NULL,
    .command = 0
};

// 工作线程
void* worker_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&shared.mutex);
        
        if (shared.current_task) {
            TaskFunc task = shared.current_task;
            shared.current_task = NULL;  // 重置
            
            pthread_mutex_unlock(&shared.mutex);
            
            // 静态分析无法知道哪个函数会被调用
            task();  // 由主线程决定的间接调用
            
            usleep(100000);  // 100ms
        } else {
            pthread_mutex_unlock(&shared.mutex);
            usleep(10000);  // 10ms
        }
        
        pthread_mutex_lock(&shared.mutex);
        if (shared.command == -1) {  // 退出命令
            pthread_mutex_unlock(&shared.mutex);
            break;
        }
        pthread_mutex_unlock(&shared.mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    
    printf("Thread communication based indirect calls:\n");
    
    // 创建工作线程
    pthread_create(&thread, NULL, worker_thread, NULL);
    
    TaskFunc tasks[] = {task1, task2, task3};
    
    // 主线程根据运行时条件选择任务
    for (int i = 0; i < 10; i++) {
        usleep(200000);  // 200ms
        
        pthread_mutex_lock(&shared.mutex);
        
        // 基于循环计数和时间的复杂逻辑选择任务
        int choice = (i + (int)time(NULL)) % 3;
        shared.current_task = tasks[choice];
        
        printf("Main thread scheduling task %d\n", choice + 1);
        
        pthread_mutex_unlock(&shared.mutex);
    }
    
    // 通知线程退出
    pthread_mutex_lock(&shared.mutex);
    shared.command = -1;
    pthread_mutex_unlock(&shared.mutex);
    
    pthread_join(thread, NULL);
    
    return 0;
}