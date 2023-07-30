// 宏定义中的特殊操作符("#"、"##"、"..." and "__VA_ARGS__")

// #
// 假如希望在字符串中包含宏参数本身，在宏的替换部分，# 符号用作一个预处理运算符
// 它把形参转换为形参对应的字符串
// 例如，如果 x 是一个宏参量，那么 #x 表示 "x"
// 该过程称为字符串化

#include <stdio.h>
#define PI(x) #x
#define PSQR_a(x) printf("the square of #x is %d.\n", (x) * (x))
#define PSQR_b(x) printf("the square of "#x" is %d.\n", (x) * (x))

int main() {
    const char* pi_a = PI(3.1415);// const char* pi_a = "3.1415";
    const char* pi_b = PI(3.1415f);// const char* pi_a = "3.1415f";

    int y = 4;
    PSQR_a(y);// printf("the square of #x is %d.\n", (y) * (y));
    PSQR_b(y);
    // g++ 13.1.1: printf("the square of ""y"" is %d.\n", (y) * (y));
    // cppinsights: printf("the square of y is %d.\n", (y) * (y));
    // 输出均为: the square of #x is 16.
    //          the square of y is 16.

    PSQR_a(2 + 4);// printf("the square of #x is %d.\n", (2 + 4) * (2 + 4));
    PSQR_b(2 + 4);
    // g++ 13.1.1: printf("the square of ""2 + 4"" is %d.\n", (2 + 4) * (2 + 4));
    // cppinsights: printf("the square of 2 + 4 is %d.\n", (2 + 4) * (2 + 4));
    // 输出均为: the square of #x is 36.
    //          the square of 2 + 4 is 36.
    return 0;
}