// dynamic_library.c
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
    void* handle;
    double (*cosine)(double);
    char* error;
    
    printf("=== Dynamic Library Function Call ===\n");
    
    // 动态加载数学库
    handle = dlopen("libm.so.6", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 1;
    }
    
    // 获取函数指针
    cosine = (double(*)(double)) dlsym(handle, "cos");
    error = dlerror();
    if (error) {
        fprintf(stderr, "Error getting symbol: %s\n", error);
        dlclose(handle);
        return 1;
    }
    
    // 间接调用动态库中的函数
    printf("cos(0) = %f\n", cosine(0.0));
    printf("cos(1.57) = %f\n", cosine(1.57));
    
    dlclose(handle);
    return 0;
}