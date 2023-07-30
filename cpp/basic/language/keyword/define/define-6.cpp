#include <iostream>

// 系统常见预定义宏
int this_is_a_function(int a, int b) {
    std::cout << "I am a function, my name is " << __FUNCTION__ << std::endl;

    return 2023;
}

int main() {
    std::cout << __cplusplus << std::endl;
    std::cout << __STDC_HOSTED__ << std::endl;
    std::cout << __FILE__ << std::endl;
    std::cout << __LINE__ << std::endl;
    std::cout << __DATE__ << std::endl;
    std::cout << __TIME__ << std::endl;

    this_is_a_function(4, 11);

    return 0;
}