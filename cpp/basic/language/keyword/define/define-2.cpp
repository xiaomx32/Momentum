#include <iostream>

// #define 宏名(形参列表) 字符串

// 宏可以带有参数
// 宏定义中的参数为形式参数，在宏调用中的参数为实际参数
// 对带参数的宏，在调用中，不仅要宏展开，而且要用实参去代换形参

#define add_a(x, y) x + y
#define add_b(x, y) (x + y)
// 宏被定义为 (x + y), 加括号的原因是，宏定义只是在预处理阶段做了简单的文本替换
// 如果单纯的定义为 x + y，使用 5 * add(2, 3) 时，就会被替换为 5 * 2 + 3, 而非 5 * (2 + 3)
// 因此为表达式（甚至是每个参数）加上括号，可以避免出错

// 进阶：使用 do {...} while(0)
// do 能确保大括号里的逻辑能被执行，而 while(0) 能确保该逻辑只被执行一次，即与没有循环时一样
// 使用 do {...} while(0) 构造后的宏定义不会受到大括号、分号等的影响，总是会按你期望的方式调用运行

// 例如
// #define foo(x) do { bar(x); baz(x); } while (0)
// if (!feral)
//     foo(wolf);
// 扩展为：
// if (!feral)
//     do { bar(wolf); baz(wolf); } while (0);
// 语义上等价于：
// if (!feral) {
//     bar(wolf);
//     baz(wolf);
// }

int main() {
    std::cout << "1 plus 1 is " << add_a(1, 1) << std::endl;
    //std::cout << "1 plus 1 is " << 1 + 1 << std::endl;

    std::cout << "1 plus 1 is " << 5 * add_a(1, 1) << std::endl;
    //std::cout << "1 plus 1 is " << 5 * 1 + 1 << std::endl;

    std::cout << "1 plus 1 is " << 5 * add_b(1, 1) << std::endl;
    //std::cout << "1 plus 1 is " << 5 * (1 + 1) << std::endl;

    return 0;
}