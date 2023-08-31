# 学习 C++ 宏的用法
## 关键字 define

调试小技巧：
+ 使用 `g++ -E main.cpp -o main.i` 命令，对代码只进行预处理，从而展开宏。
+ [https://cppinsights.io/](https://cppinsights.io/): 可以将代码中的宏定义展开。

g++ 版本：13.1.1

`define-1.cpp`: 关键字 `define` 的常规用法。

`define-2.cpp`: 带有参数的宏。

`define-3.cpp`: 符号 ‘#’ 的用法。

`define-4.cpp`: 符号 ‘##’ 的用法。

`define-5.cpp`: 符号 '...' 和 '__VA__ARGS__' 的用法。

`define-6.cpp`: 系统常见预定义宏。

`define-7.cpp`: 宏定义中的换行。

`define-8.cpp`: 宏的简单用法：实现条件编译。

`define-9.cpp`: 定义宏、取消宏。
