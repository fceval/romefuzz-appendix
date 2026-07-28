// std_function_example.cpp
#include <iostream>
#include <functional>
#include <vector>
#include <string>

// 使用extern "C"包裹普通函数
extern "C" {
    void regular_function() {
        std::cout << "Regular function called" << std::endl;
    }
}

class TaskScheduler {
private:
    std::vector<std::function<void()>> tasks;
    
public:
    void schedule_task(std::function<void()> task) {
        tasks.push_back(task);
    }
    
    void run_all() {
        for (auto& task : tasks) {
            task();  // 间接调用，可能是函数指针、lambda或函数对象
        }
    }
};

class Functor {
private:
    std::string name;
public:
    Functor(const std::string& n) : name(n) {}
    
    void operator()() const {
        std::cout << "Functor " << name << " called" << std::endl;
    }
};

int main() {
    TaskScheduler scheduler;
    
    // 1. 注册普通函数（现在被extern "C"包裹）
    scheduler.schedule_task(regular_function);
    
    // 2. 注册lambda表达式
    scheduler.schedule_task([]() {
        std::cout << "Lambda function called" << std::endl;
    });
    
    // 3. 注册函数对象
    scheduler.schedule_task(Functor("MyFunctor"));
    
    // 4. 捕获变量的lambda
    std::string message = "Hello from captured lambda";
    scheduler.schedule_task([message]() {
        std::cout << message << std::endl;
    });
    
    // 执行所有任务 - 多种形式的间接调用
    std::cout << "=== Running all scheduled tasks ===" << std::endl;
    scheduler.run_all();
    
    return 0;
}