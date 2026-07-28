// virtual_function.cpp
#include <iostream>
#include <vector>

// 最简化的extern "C"包装
extern "C" {
    // 只包装程序中实际使用的工具函数
    double get_pi_value() {
        return 3.14159;
    }
}

class Shape {
public:
    virtual void draw() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius_;
public:
    Circle(double r) : radius_(r) {}
    
    void draw() const override {
        std::cout << "Drawing Circle with radius " << radius_ << std::endl;
    }
    
    double area() const override {
        return get_pi_value() * radius_ * radius_;  // 使用extern "C"函数
    }
};

class Rectangle : public Shape {
private:
    double width_, height_;
public:
    Rectangle(double w, double h) : width_(w), height_(h) {}
    
    void draw() const override {
        std::cout << "Drawing Rectangle " << width_ << "x" << height_ << std::endl;
    }
    
    double area() const override {
        return width_ * height_;
    }
};

int main() {
    std::vector<Shape*> shapes;
    
    shapes.push_back(new Circle(5.0));
    shapes.push_back(new Rectangle(4.0, 6.0));
    shapes.push_back(new Circle(3.0));
    
    for (auto shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->area() << std::endl;
        std::cout << "---" << std::endl;
    }
    
    for (auto shape : shapes) {
        delete shape;
    }
    
    return 0;
}



// // virtual_function.cpp
// #include <iostream>
// #include <vector>

// class Shape {
// public:
//     virtual void draw() const = 0;  // 纯虚函数
//     virtual double area() const = 0;
//     virtual ~Shape() = default;
// };

// class Circle : public Shape {
// private:
//     double radius_;
// public:
//     Circle(double r) : radius_(r) {}
    
//     void draw() const override {
//         std::cout << "Drawing Circle with radius " << radius_ << std::endl;
//     }
    
//     double area() const override {
//         return 3.14159 * radius_ * radius_;
//     }
// };

// class Rectangle : public Shape {
// private:
//     double width_, height_;
// public:
//     Rectangle(double w, double h) : width_(w), height_(h) {}
    
//     void draw() const override {
//         std::cout << "Drawing Rectangle " << width_ << "x" << height_ << std::endl;
//     }
    
//     double area() const override {
//         return width_ * height_;
//     }
// };

// int main() {
//     std::vector<Shape*> shapes;
    
//     shapes.push_back(new Circle(5.0));
//     shapes.push_back(new Rectangle(4.0, 6.0));
//     shapes.push_back(new Circle(3.0));
    
//     // 虚函数间接调用 - 运行时多态
//     for (auto shape : shapes) {
//         shape->draw();  // 间接调用，通过虚函数表
//         std::cout << "Area: " << shape->area() << std::endl;  // 间接调用
//         std::cout << "---" << std::endl;
//     }
    
//     // 清理内存
//     for (auto shape : shapes) {
//         delete shape;
//     }
    
//     return 0;
// }