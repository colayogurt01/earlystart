cmake_minimum_required(VERSION 3.27)  # 设置CMake的最低版本要求
project(earlystart)                    # 定义项目名称

# 确保使用 Unicode 编译
add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_CXX_STANDARD 17)             # 设置C++标准为 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # 确保使用的C++标准是绝对的

# 添加包含目录
include_directories(${CMAKE_SOURCE_DIR}/Log)



# 指定服务程序的源文件
set(SOURCES_main
        main/main.cpp        # 主程序文件
        main/mainwork.cpp    # 其他源文件
        ../Log/log.cpp


)
# 指定测试的源文件
set(SOURCES_test
        main/test.cpp        # 主程序文件
        main/mainwork.cpp    # 其他源文件
        ../Log/log.cpp


)
# 指定安装服务程序的源文件
set(SOURCES_INSTALL
        install/install.cpp
        ../Log/log.cpp
)

# 指定卸载服务程序的源文件
set(SOURCES_UNINSTALL
        uninstall/uninstall.cpp
        ../Log/log.cpp
)
# 创建测试文件
add_executable(test ${SOURCES_test})
set_target_properties(test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 创建服务的可执行文件
add_executable(earlystart ${SOURCES_main})
set_target_properties(earlystart PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 安装程序的可执行文件
add_executable(installer ${SOURCES_INSTALL})
set_target_properties(installer PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 卸载服务的可执行文件
add_executable(uninstaller ${SOURCES_UNINSTALL})  # 使用 'uninstaller' 而不是 'uninstall' 避免与CMake关键字冲突
set_target_properties(uninstaller PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 如果需要链接库，可以在这里添加
 target_link_libraries(earlystart Wtsapi32.lib)
# target_link_libraries(installer <libraries>)
# target_link_libraries(uninstall <libraries>)
