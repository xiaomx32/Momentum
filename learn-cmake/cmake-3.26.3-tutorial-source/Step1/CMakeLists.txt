# TODO 1: Set the minimum required version of CMake to be 3.10
cmake_minimum_required(VERSION 3.10...3.26 FATAL_ERROR) 

# TODO 2: Create a project named Tutorial
# CMake 在背后会定义 Tutorial_VERSION_MAJOR 和 Tutorial_VERSION_MINOR 变量
# TODO 7: Set the project version number as 1.0 in the above project command
project(
    Tutorial
    VERSION 1.0
)

# TODO 6: Set the variable CMAKE_CXX_STANDARD to 11
#         and the variable CMAKE_CXX_STANDARD_REQUIRED to True
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO 8: Use configure_file to configure and copy TutorialConfig.h.in to
#         TutorialConfig.h
# configure_file(), CMake 函数，用于生成配置文件
# 将输入文件复制到给定的输出文件中，并用 CMakeLists.txt 文件中
# VAR 的当前值替换这些变量
# 通过使用 configure_file() 函数会估值输入文件并替换指定的 CMake 变量
configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO 3: Add an executable called Tutorial to the project
# Hint: Be sure to specify the source file as tutorial.cxx
add_executable(Tutorial tutorial.cxx)

# TODO 9: Use target_include_directories to include ${PROJECT_BINARY_DIR}
# 指定可执行目标应该在哪寻找包含目录
target_include_directories(Tutorial PUBLIC
    "${PROJECT_BINARY_DIR}"
)