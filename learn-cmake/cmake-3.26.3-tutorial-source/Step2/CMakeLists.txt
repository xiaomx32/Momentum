cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO 7: Create a variable USE_MYMATH using option and set default to ON
# This gives users a variable which they can change when configuring their cmake build.
# This setting will be stored in the cache so that the user does not need to 
# set the value each time they run CMake on a build directory.
# USE_MYMATH option will be displayed in the cmake-gui and
# ccmake with a default value of ON that can be changed by the user.
# option 为项目提供一种控制编译选项
# option(<option_variable> "option_description" [initial_value])
# option_variable 变量名，用于标识这个选项，并存储用户选择的结果
# option_description 是对该选项的描述文字，会在 CMake 生成的配置界面或命令行中显示给用户
# initial_value 是可选的初始值，默认为 OFF
option(USE_MYMATH "Use tutorial provided math implemmention" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO 8: Use list() and APPEND to create a list of optional libraries
# called  EXTRA_LIBS and a list of optional include directories called
# EXTRA_INCLUDES. 
# Add the MathFunctions library and source directory to
# the appropriate lists.
# Only call add_subdirectory and only add MathFunctions specific values
# to EXTRA_LIBS and EXTRA_INCLUDES if USE_MYMATH is true.
if(USE_MYMATH)
    message(${USE_MYMATH})
    add_subdirectory(MathFunctions)

    # 向名为 EXTRA_LIBS 的（库）列表追加一个名为 MathFunctions 的元素
    list(APPEND EXTRA_LIBS MathFunctions)

    # 向名为 EXTRA_INCLUDES 的列表变量追加一个元素，
    # 该元素的值是主项目源代码目录下的 MathFunctions 子目录的路径
    # 这通常用于将需要包含的头文件目录添加到编译器的搜索路径中。
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

# TODO 2: Use add_subdirectory() to add MathFunctions to this project
# 添加子目录，此时会递归执行子目录下的 CMakeLists.txt
# add_subdirectory(MathFunctions)

# add the executable
add_executable(Tutorial tutorial.cxx)

# TODO 9: Use EXTRA_LIBS instead of the MathFunctions specific values
# in target_link_libraries.
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

# TODO 3: Use target_link_libraries to link the library to our executable
# 将 MathFunctions 库链接到可执行目标
# target_link_libraries(Tutorial PUBLIC MathFunctions)

# TODO 4: Add MathFunctions to Tutorial's target_include_directories()
# Hint: ${PROJECT_SOURCE_DIR} is a path to the project source. AKA This folder!
# 将 MathFunctions 子目录添加为包含目录，以便可以找到 MathFunctions.h 头文件
# target_include_directories(
#     Tutorial PUBLIC
#     "${PROJECT_BINARY_DIR}"
#     "${PROJECT_SOURCE_DIR}/MathFunctions"
# )

# TODO 10: Use EXTRA_INCLUDES instead of the MathFunctions specific values
# in target_include_directories.
target_include_directories(
    Tutorial PUBLIC
    "${PROJECT_BINARY_DIR}"
    ${EXTRA_INCLUDES}
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(
    Tutorial PUBLIC
    "${PROJECT_BINARY_DIR}"
)

# cmake -S ./Step2 -B ./Step2_build
# or
# cmake -S ./Step2 -B ./Step2_build -DUSE_MYMATH=OFF