# 最低 CMake 版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(SnakeGame)

# 设置 C++ 标准为 C++11 或更高版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置头文件搜索路径
include_directories(
        ${PROJECT_SOURCE_DIR}/include    # 包含项目中的头文件
        ${PROJECT_SOURCE_DIR}/lib        # 包含 pdcurses 头文件（如 pdcwin.h 和 curses.h）
)

# 设置 pdcurses 库的路径
link_directories(${PROJECT_SOURCE_DIR}/lib)  # 链接 pdcurses 静态库目录

# 查找源文件
set(SOURCES
        src/start.cpp
        src/arena.cpp
        src/data.cpp
        src/View.cpp
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 链接 pdcurses 静态库
target_link_libraries(${PROJECT_NAME} -l:pdcurses.a)

# 如果需要在 Windows 上使用 UTF-8 兼容设置，可以添加：
if(MSVC)
    add_definitions(-D_UNICODE -DUNICODE)
endif()

# 可选：为 Windows 设置额外的编译选项以确保与终端兼容（例如：UTF-8 输出支持）
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
