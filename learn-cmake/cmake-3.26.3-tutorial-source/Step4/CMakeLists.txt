# 生成器表达式在构建系统生成期间进行评估，以生成特定于每个构建配置的信息
# 生成器表达式可用于启用条件链接、编译时使用的条件定义、条件包含目录等
# 这些条件可能基于构建配置、目标属性、平台信息或任何其他可查询信息
# 有不同类型的生成器表达式，包括逻辑表达式、信息表达式和输出表达式
# 生成器表达式的一个常见用法是有条件地添加编译器标志，例如用于语言级别或警告的标志
# 一个很好的模式是将此信息关联到允许此信息传播的 INTERFACE 目标

# TODO 4: Update the minimum required version to 3.15

cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(Tutorial VERSION 1.0)

# TODO 1: Replace the following code by:
# * Creating an interface library called tutorial_compiler_flags
#   Hint: use add_library() with the INTERFACE signature
# * Add compiler feature cxx_std_11 to tutorial_compiler_flags
#   Hint: Use target_compile_features()
# specify the C++ standard
# 创建一个名为 tutorial_compiler_flags 的接口库
# 使用 target_compile_features 命令为接口库添加编译器功能 cxx_std_11
# 目标：重构代码，使用 INTERFACE 库来指定 C++ 标准
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)

# TODO 5: Create helper variables to determine which compiler we are using:
# * Create a new variable gcc_like_cxx that is true if we are using CXX and
#   any of the following compilers: ARMClang, AppleClang, Clang, GNU, LCC
# * Create a new variable msvc_cxx that is true if we are using CXX and MSVC
# Hint: Use set() and COMPILE_LANG_AND_ID
# 生成器表达式在构建系统生成期间，基于条件进行动态计算和设置，以生成特定于每个生成配置的信息。
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,APPLEClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")


# TODO 6: Add warning flag compile options to the interface library
# tutorial_compiler_flags.
# * For gcc_like_cxx, add flags -Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused
# * For msvc_cxx, add flags -W3
# target_compile_options() 函数用于为特定目标设置编译选项
# 编译选项是传递给编译器的附加参数，用于控制编译过程中的行为和选项
# PRIVATE：只应用于当前目标
# PUBLIC：应用于当前目标及其使用该目标的目标
# INTERFACE：只应用于使用该目标的目标
target_compile_options(
    tutorial_compiler_flags INTERFACE
    "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
    "$<${msvc_cxx}:-W3>"
)

# TODO 7: With nested generator expressions, only use the flags for the
# build-tree
# Hint: Use BUILD_INTERFACE
target_compile_options(
    tutorial_compiler_flags INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# add the MathFunctions library
if(USE_MYMATH)
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
endif()

# add the executable
add_executable(Tutorial tutorial.cxx)

# TODO 2: Link to tutorial_compiler_flags
# 将可执行 Target 和 MathFunctions 库链接到新的 tutorial_compiler_flags 库
target_link_libraries(
    Tutorial PUBLIC
    ${EXTRA_LIBS}
    tutorial_compiler_flags
)

target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(
    Tutorial PUBLIC
    "${PROJECT_BINARY_DIR}"
)