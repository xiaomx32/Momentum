add_library(MathFunctions mysqrt.cxx)

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(
    MathFunctions INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# link our compiler flags interface library
target_link_libraries(MathFunctions tutorial_compiler_flags)

# TODO 1: Create a variable called installable_libs that is a list of all
# libraries we want to install (e.g. MathFunctions and tutorial_compiler_flags)
# Then install the installable libraries to the lib folder.
# Hint: Use the TARGETS and DESTINATION parameters
set(installable_libs MathFunctions tutorial_compiler_flags)
# TARGETS <target>：指定要安装的构建目标，可以是可执行文件、库文件或自定义的 CMake 目标
# 注意：install 命令安装一个 INTERFACE 库时，它实际上并不会在文件系统中生成任何文件
# INTERFACE 库是一种特殊类型的库，它不包含任何实际的二进制或源代码文件，仅用于传递接口信息给依赖的目标
# INTERFACE 库的作用是允许你定义一组接口（包括头文件路径、编译选项、链接选项等
# 然后将这些接口传递给依赖此库的其他目标。通过这种方式，INTERFACE 库可以用来共享接口定义和编译设置
# 而无需在文件系统中生成额外的库文件
install(
    TARGETS
        ${installable_libs}
    DESTINATION
        lib
)

# TODO 2: Install the library headers to the include folder.
# Hint: Use the FILES and DESTINATION parameters
install(
    FILES
        MathFunctions.h
    DESTINATION
        include
)
