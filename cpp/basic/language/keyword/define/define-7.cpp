// 宏定义中的多行定义

#define MACRO(arg1, arg2) do { \
    // something
    (arg1); \
    (arg1); \
    // something
} while(0) /* (no trailing;) */