add_library(MathFunctions mysqrt.cxx)

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(
    MathFunctions INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# link our compiler flags interface library
target_link_libraries(MathFunctions tutorial_compiler_flags)

# TODO 1: Include CheckCXXSourceCompiles
# include 命令用于包含外部 CMake 脚本文件
# 当你需要在一个 CMake 脚本中引入其他的 CMake 脚本时，可以使用 include 命令
# 它允许你将其他脚本的内容插入到当前脚本中，就像是将多个脚本文件合并为一个
# CMake 提供了一系列的模块，这些模块包含了一些常用的功能和检查，以帮助开发者更方便地进行构建和配置项目
# CheckCXXSourceCompiles 模块就是其中之一，用于检查给定的 C++ 源代码能否编译通过
# 这些模块通常位于 CMake 的安装目录下的 Modules 文件夹中，
# 对于不同的操作系统和安装方式，该路径可能会有所不同
# 在使用 include 命令时，CMake 会自动搜索这些模块，并加载相应的功能。
# 因此，你可以在 CMake 脚本中直接使用
# CheckCXXSourceCompiles 模块提供的函数 check_cxx_source_compiles，而无需额外安装或配置任何内容
# 如果你需要使用其他的模块，你可以通过 include 命令来引入它们
# 例如 include(FooModule)，其中 FooModule 是你想要引入的模块的名称
# 可以在 CMake 的官方文档中查找特定模块的功能和使用方式。
include(CheckCXXSourceCompiles)

# TODO 2: Use check_cxx_source_compiles with simple C++ code to verify
# availability of:
# * std::log
# * std::exp
# Store the results in HAVE_LOG and HAVE_EXP respectively.

# Hint: Sample C++ code which uses log:
# #include <cmath>
# int main() {
#   std::log(1.0);
#   return 0;
# }
# check_cxx_source_compiles 函数让我们在真正的源代码编译之前，
# 尝试编译具有所需依赖关系的简单代码
# 结果变量 HAVE_LOG 和 HAVE_EXP 表示这些依赖项是否可用
check_cxx_source_compiles(
    "
    #include <cmath>
    int main() {
        std::log(1.0);
        return 0;
    }
    "
    HAVE_LOG
)
check_cxx_source_compiles(
    "
    #include <cmath>
    int main() {
        std::exp(1.0);
        return 0;
    }
    "
    HAVE_EXP
)

# TODO 3: Conditionally on HAVE_LOG and HAVE_EXP, add private compile
# definitions "HAVE_LOG" and "HAVE_EXP" to the MathFunctions target.
#Hint: Use target_compile_definitions()

# target_compile_definitions 是 CMake 中的一个函数，用于向目标（target）添加预定义的编译器宏定义
# 在编译项目时，我们可能需要根据不同的条件定义一些宏，这些宏可以在源代码中使用，
# 影响编译过程中的条件判断和代码行为
# 从而根据需要进行条件编译
if(HAVE_LOG AND HAVE_EXP)
    target_compile_definitions(
        MathFunctions PRIVATE
        "HAVE_LOG" # 宏定义列表，每个宏定义可以是一个字符串，也可以是一个键值对
        "HAVE_EXP"
    )
endif()

# install libs
set(installable_libs MathFunctions tutorial_compiler_flags)
install(
    TARGETS
        ${installable_libs}
    DESTINATION
        lib
)
# install include headers
install(
    FILES
        MathFunctions.h
    DESTINATION
        include
)