# 运行方法：在 Step12 目录中运行 cpack --config MultiCPackConfig.cmake 命令
include("release/CPackConfig.cmake")

set(CPACK_INSTALL_CMAKE_PROJECTS
    "debug;Tutorial;ALL;/"
    "release;Tutorial;ALL;/"
)