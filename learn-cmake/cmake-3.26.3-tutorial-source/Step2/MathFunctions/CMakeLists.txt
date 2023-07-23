# TODO 1: Add a library called MathFunctions
# Hint: You will need the add_library command
# add_library 是 CMake 中用于创建静态库或共享库的函数
# add_library(
#     <name> [STATIC | SHARED | MODULE]
#     [EXCLUDE_FROM_ALL]
#     source1 source2 ... sourceN
# )
# <name>：库的名称，可以是任意有效的标识符
# STATIC | SHARED | MODULE：可选参数，用于指定库的类型
# STATIC 表示静态库，SHARED 表示共享库（动态库），MODULE 表示模块库（在某些系统上的特殊类型）
# 如果未明确指定类型，默认为 STATIC
# EXCLUDE_FROM_ALL：可选参数，用于指定该库是否应该被排除在构建过程的默认目标之外

# 除了上述参数外，还需要指定要包含在库中的源文件列表，
# 这些源文件通过空格分隔并列在 add_library 命令后面
# 在 add_library 中添加源文件时，你可以在源文件名前面指定路径（相对或绝对路径都可以）

# 如果在 add_library 中没有指定源文件的路径，
# 那么 CMake 会默认在当前的 CMakeLists.txt 文件所在目录中寻找源文件

# 如果源文件与当前 CMakeLists.txt 文件不在同一个目录且没有使用路径指定源文件，
# CMake 将无法找到该源文件，并在构建过程中报错
add_library(MathFunctions mysqrt.cxx)