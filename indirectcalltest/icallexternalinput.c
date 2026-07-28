// external_input.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
    void (*handler)();
} Command;

void cmd_help() { printf("Help command executed\n"); }
void cmd_exit() { printf("Exit command executed\n"); }
void cmd_run() { printf("Run command executed\n"); }
void cmd_stop() { printf("Stop command executed\n"); }
void cmd_unknown() { printf("Unknown command\n"); }

Command commands[] = {
    {"help", cmd_help},
    {"exit", cmd_exit}, 
    {"run", cmd_run},
    {"stop", cmd_stop}
};

// 模拟从外部来源获取命令
char* get_external_command() {
    // 模拟网络、文件、用户输入等
    static const char* external_sources[] = {
        "help", "run", "stop", "exit", "unknown"
    };
    
    // int index = rand() % 5;
    int index = rand() % 5;
    return (char*)external_sources[index];
}

// 复杂的字符串匹配和转换
void (*resolve_command(const char* input))() {
    // 大小写不敏感匹配
    char normalized[32];
    strncpy(normalized, input, 31);
    normalized[31] = '\0';
    
    // 转换为小写
    for (char* p = normalized; *p; p++) {
        if (*p >= 'A' && *p <= 'Z') {
            *p = *p - 'A' + 'a';
        }
    }
    
    // 模糊匹配
    for (int i = 0; i < 4; i++) {
        if (strstr(commands[i].name, normalized) || 
            strstr(normalized, commands[i].name)) {
            return commands[i].handler;
        }
    }
    
    return cmd_unknown;
}

int main() {
    srand((unsigned int)time(NULL));
    
    printf("External input based indirect calls:\n");
    
    for (int i = 0; i < 10; i++) {
        // 从外部获取命令（模拟）
        char* external_cmd = get_external_command();
        printf("Received command: %s -> ", external_cmd);
        
        // 静态分析无法知道external_cmd的值
        void (*handler)() = resolve_command(external_cmd);
        handler();  // 依赖于外部输入
        
        // 添加延迟，模拟真实场景
        for (int j = 0; j < 1000000; j++); // 忙等待
    }
    
    return 0;
}