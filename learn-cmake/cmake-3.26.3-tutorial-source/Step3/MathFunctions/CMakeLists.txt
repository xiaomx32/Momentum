add_library(MathFunctions mysqrt.cxx)

# TODO 1: State that anybody linking to MathFunctions needs to include the
# current source directory, while MathFunctions itself doesn't.
# Hint: Use target_include_directories with the INTERFACE keyword
# Remember INTERFACE means things that consumers require but the producer doesn't.
# INTERFACE 用于定义一个接口库（Interface Library）
# 接口库是一种特殊类型的库，它不包含实际的源代码或编译生成的目标文件
# 仅仅包含头文件和与其他目标库之间的依赖关系
# 接口库主要用于管理依赖关系，帮助组织和管理项目的模块化结构
target_include_directories(
    MathFunctions INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

message(
    "in MathFunctions/CMakeLists.txt,
    CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}"
)
# ${CMAKE_CURRENT_SOURCE_DIR}: ~/cmake-3.26.3-tutorial-source/Step3/MathFunctions