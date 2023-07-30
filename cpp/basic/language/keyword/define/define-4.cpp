// ##
// 把两个语言符号组合成单个语言符号

#include <stdio.h>
#define XNAME(n) x##n
#define PXN(n) printf("x"#n" = %d\n", x##n)

int main() {
    int XNAME(1) = 12;// int x1 = 12;

    PXN(1);
    // g++ 13.1.1: printf("x""1"" = %d\n", x1);
    // cppinsights: printf("x1 = %d\n", x1);

    // 输出均为：x1 = 12
    return 0;
}