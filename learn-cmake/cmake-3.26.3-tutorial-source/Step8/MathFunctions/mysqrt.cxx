// 生成一个预计算值表以在 mysqrt 函数中使用
// 将创建表作为构建过程的一部分，然后将该表编译到我们的应用程序中

// 构建此项目时，它将首先构建 MakeTable 可执行文件
// 然后它将运行 MakeTable 以生成 Table.h
// 最后，它将编译包含 Table.h 的 mysqrt.cxx 以生成 MathFunctions 库

// 运行 Tutorial 可执行文件并验证它是否正在使用该表。


#include <iostream>
#include "MathFunctions.h"
#include "Table.h"

// a hack square root calculation using simple operations
double mysqrt(double x) {
    if (x <= 0) {
        return 0;
    }

    // use the table to help find an initial value
    // 使用生成的表
    // 首先，修改 mysqrt.cxx 以包含 Table.h
    // 接下来，我们可以重写 mysqrt 函数来使用该表
    double result = x;
    if (x >= 1 && x < 10) {
        std::cout << "Use the table to help find an initial value " << std::endl;
        result = sqrtTable[static_cast<int>(x)];
    }

    // do ten iterations
    for (int i = 0; i < 10; ++i) {
        if (result <= 0) {
            result = 0.1;
        }
        double delta = x - (result * result);
        result = result + 0.5 * delta / result;
        std::cout << "Computing sqrt of " << x << " to be " << result << std::endl;
    }

    return result;
}
