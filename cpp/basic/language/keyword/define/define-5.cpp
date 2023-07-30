// 可变参数宏 "..." 和 "__VA_ARGS__"
// 宏定义中参数列表的最后一个参数为省略号(...)
// 预定义宏 __VA_ARGS__ 表示可变参数部分，替换省略号所代表的字符串

#include <stdio.h>
// 宏定义中的可变参数传递给另一个宏
#define PR(...) printf(__VA_ARGS__)

// 宏展开为多条语句
#define LOG_ERROR(...) do { \
    fprintf(stderr, "Error: "); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
} while (0)

int main() {
    int wt = 1;
    int sp = 2;

    PR("hello\n");
    // printf("hello\n");

    PR("weight = %d, shipping = %d", wt, sp);
    // printf("weight = %d, shipping = %d", wt, sp);


    int errorCode = 404;
    LOG_ERROR("File not found: %d", errorCode);
    // do {
    //     fprintf(stderr, "Error: ");
    //     fprintf(stderr, "File not found: %d", errorCode);
    //     fprintf(stderr, "\n");
    // } while(0);

    return 0;
}