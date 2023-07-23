# 将适当的命令添加到 MathFunctions/CMakeLists.txt 文件以构建 MakeTable 可执行文件
# 然后将其作为构建过程的一部分运行
# 当计算 1, 2, 3, 4, 5, 6, 7, 8, 9 的平方根时，
# 会从 sqrtTable[] 数组中直接得出答案

add_executable(MakeTable MakeTable.cxx)

# 添加一个自定义命令，指定如何通过运行 MakeTable 来生成 Table.h
add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND
        MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS
        MakeTable
)

# 让 CMake 知道 mysqrt.cxx 依赖于生成的文件 Table.h
# 这是通过将生成的 Table.h 添加到库 MathFunctions 的源列表中来完成的
add_library(
    MathFunctions
    mysqrt.cxx
    ${CMAKE_CURRENT_BINARY_DIR}/Table.h
)
# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
# 将当前二进制目录添加到包含目录列表中，以便 table.h 可以被 mysqrt.cxx 找到和包含
target_include_directories(MathFunctions
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

# link our compiler flags interface library
target_link_libraries(MathFunctions tutorial_compiler_flags)

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
