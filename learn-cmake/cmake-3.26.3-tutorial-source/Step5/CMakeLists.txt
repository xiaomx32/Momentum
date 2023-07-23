# 通常，仅仅构建一个可执行文件是不够的，它还应该是可安装的
# 使用 CMake，我们可以使用 install() 命令指定
# 构建目标（例如可执行文件、库文件、头文件等）在构建完成后安装到系统或指定位置
# 目标：安装 Tutorial 可执行文件和 MathFunctions 库

# 具体命令行
# 先构建和编译项目：cmake -S . -B build && cmake --build build
# 然后执行安装命令：cmake --install build
# 对于多配置平台，使用 --config 参数指定配置：cmake --install build --config Release
# 如果使用 IDE，只需构建 INSTALL 目标。您可以从命令行构建相同的安装目标：
#     cmake --build build --target install --config Debug

# CMake 变量 CMAKE_INSTALL_PREFIX 用于确定将安装文件的根目录
# 如果使用 cmake --install 命令，可以通过 --prefix 参数覆盖安装前缀：
# cmake --install build --prefix "/home/myuser/installdir"

cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(Tutorial VERSION 1.0)

# specify the C++ standard
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
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
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS} tutorial_compiler_flags)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(
    Tutorial PUBLIC
    "${PROJECT_BINARY_DIR}"
)

# CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT 变量用于确定
# CMAKE_INSTALL_PREFIX 变量是否已初始化为默认值
# 如果是则为 TRUE，否则为 FALSE
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX is set to default: ${CMAKE_INSTALL_PREFIX}."
    )
    set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}")
    message(
        STATUS
        "But now CMAKE_INSTALL_PREFIX is set Manually by PROJECT_BINARY_DIR: 
        ${CMAKE_INSTALL_PREFIX}."
    )
else()
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX is set to default: ${CMAKE_INSTALL_PREFIX}."
    )
endif()
# TODO 3: Install Tutorial in the bin directory
# Hint: Use the TARGETS and DESTINATION parameters
install(
    TARGETS
        Tutorial
    DESTINATION
        bin
)
# TODO 4: Install TutorialConfig.h to the include directory
# Hint: Use the FILES and DESTINATION parameters
install(
    FILES
        "${PROJECT_BINARY_DIR}/TutorialConfig.h"
    DESTINATION
        include
)


# CTest 提供了一种轻松管理项目测试的方法
# CTest 是 CMake 的一个组件，用于执行测试套件并生成测试报告
# 通常，在运行测试时，CTest 只会显示测试结果（通过/失败），而不会显示任何警告信息
# 使用 CTest 为我们的可执行文件创建单元测试
# CTestTestfile.cmake 是一个由 CTest 自动生成的文件，用于定义测试套件和测试用例
# 使用方法：
# 1、进入 build 目录：cd build
# 2、在命令行中运行命令：ctest -W 或 ctest -N
# ctest -W 是用于启用警告输出的 CTest 命令选项。它告诉 CTest 将测试的警告信息包含在测试运行的输出中

# ctest -N 会显示测试套件中可用的测试列表，而不会运行实际的测试。
# 这样可以让你查看测试套件中的每个测试的名称，以便了解有哪些测试可供选择或执行

# TODO 5: Enable testing
# 启用测试
enable_testing()

# TODO 6: Add a test called Runs which runs the following command:
# $ Tutorial 25
# 它运行传入参数 25 的 Tutorial 可执行文件
# 此测试将验证应用程序是否运行、没有出现段错误或以其他方式崩溃，并且返回值为零
add_test(NAME Runs COMMAND Tutorial 25)


# TODO 7: Add a test called Usage which runs the following command:
# $ Tutorial
# Make sure the expected output is displayed.
# Hint: Use the PASS_REGULAR_EXPRESSION property with "Usage.*number"
# 使用 PASS_REGULAR_EXPRESSION 测试属性来验证测试的输出是否包含某些字符串
# 在这种情况下，验证在提供的参数数量不正确时是否打印了用法消息。
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(
    Usage
        PROPERTIES
    PASS_REGULAR_EXPRESSION
        "Usage:.*number"
)

# TODO 8: Add a test which runs the following command:
# $ Tutorial 4
# Make sure the result is correct.
# Hint: Use the PASS_REGULAR_EXPRESSION property with "4 is 2"
add_test(NAME StandardUse COMMAND Tutorial 4)
set_tests_properties(
    StandardUse
        PROPERTIES
    PASS_PEGULAR_EXPRESSION
        "4 is 2"
)

# TODO 9: Add more tests. Create a function called do_test to avoid copy +
# paste. Test the following values: 4, 9, 5, 7, 25, -25 and 0.0001.
# 创建一个名为 do_test 的函数，来运行应用程序并验证计算的平方根对于给定输入是否正确
function(do_test target arg result)
    add_test(
        NAME
            Comp${arg}
        COMMAND
            ${target} ${arg}
    )
    set_tests_properties(
        Comp${arg}
            PROPERTIES
        PASS_REGULAR_EXPRESSION
            ${result}
    )
endfunction()

# do a bunch of result based tests
do_test(Tutorial 4 "4 is 2")
do_test(Tutorial 9 "9 is 3")
do_test(Tutorial 5 "5 is 2.236")
do_test(Tutorial 7 "7 is 2.645")
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is (-nan|nan|0)")
do_test(Tutorial 0.0001 "0.0001 is 0.01")