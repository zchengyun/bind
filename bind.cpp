#include <functional>
#include <iostream>

//bind_front按顺序绑定一定数量的参数到函数对象
//bind绑定一或多个实参到函数对象
//std::function可以取代函数指针的作用，因为它可以延迟函数的执行，特别适合作为回调函数使用。

int minus(int a, int b,int c) {
    return a - b - c;
}

struct S
{
    int val;
    int minus(int new_val , int arg) const noexcept { return val - new_val - arg; }
};

struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1 + n2 << '\n';
    }
    int data = 10;
};

void print_sum(int n1, int n2)
{
    std::cout << n1 + n2 << '\n';
}

int main()
{
    auto fifty_minus = std::bind_front(minus, 50);
    std::cout << fifty_minus(3,2) << '\n';//45

    auto member_minus = std::bind_front(&S::minus, S{ 50 });
    std::cout << member_minus(3,2) << '\n';//45

    // 绑定 lambda
    auto plus = [](int a, int b) { return a + b; };
    auto forty_plus = std::bind_front(plus, 40);
    std::cout << forty_plus(7) << '\n';//47


    Foo foo;
    auto f = std::bind(&Foo::print_sum, &foo, 95, std::placeholders::_1); //std::placeholders::_1表示f中第1个参数
    f(5); // 100

    auto f1 = std::bind(print_sum, 95, std::placeholders::_2);//std::placeholders::_1表示f中第1个参数
    f1(10,15,20,25);//110
}
