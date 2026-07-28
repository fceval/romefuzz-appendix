// callback_example.c
#include <stdio.h>
#include <stdlib.h>

// 回调函数类型定义
typedef void (*EventHandler)(int event_id, void* user_data);

// 事件处理器结构
struct EventManager {
    EventHandler handlers[10];
    void* user_data[10];
    int count;
};

void register_event(struct EventManager* mgr, EventHandler handler, void* user_data) {
    if (mgr->count < 10) {
        mgr->handlers[mgr->count] = handler;
        mgr->user_data[mgr->count] = user_data;
        mgr->count++;
    }
}

void trigger_event(struct EventManager* mgr, int event_id) {
    for (int i = 0; i < mgr->count; i++) {
        // 间接调用回调函数
        mgr->handlers[i](event_id, mgr->user_data[i]);
    }
}

// 具体的回调函数实现
void log_handler(int event_id, void* user_data) {
    printf("LOG: Event %d occurred. User data: %s\n", 
           event_id, (char*)user_data);
}

void alert_handler(int event_id, void* user_data) {
    printf("ALERT: Critical event %d! Data: %s\n", 
           event_id, (char*)user_data);
}

int main() {
    struct EventManager mgr = {0};
    
    // 注册回调函数
    register_event(&mgr, log_handler, "Main System");
    register_event(&mgr, alert_handler, "Security Module");
    
    // 触发事件 - 导致间接调用
    printf("=== Triggering event 100 ===\n");
    trigger_event(&mgr, 100);
    
    // printf("\n=== Triggering event 200 ===\n");
    // trigger_event(&mgr, 200);
    
    return 0;
}