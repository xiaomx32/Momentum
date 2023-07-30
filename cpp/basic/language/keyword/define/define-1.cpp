#include <iostream>

// #define 标识符 字符串

// 标识符为宏名
// 字符串可以是常数、表达式、格式串等
#define MAXNUM 99999
#define MYNAME "zitai"

int main() {
    std::cout << "max number is " << MAXNUM << std::endl;
    // std::cout << "max number is " << 99999 << std::endl;
    // max number is 99999

    std::cout << "my name is " << MYNAME << std::endl;
    // std::cout << "my name is " << "zitai" << std::endl;
    // my name is zitai

    return 0;
}