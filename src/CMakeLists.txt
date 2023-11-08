cmake_minimum_required(VERSION 3.0)
project(Monitor-Inband-Getter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# 添加头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR})

# 将其他文件编译为静态库
add_library(my_lib STATIC
    Boost_process.cpp
    Info_Sender.cpp
    jsonPackage.cpp
    Procps.cpp
    tools.cpp
    Meminfo_Getter.cpp
    Diskinfo_Getter.cpp
)

# 添加可执行文件main
add_executable(main_executable
    main.cpp
)

# 添加可执行文件Info_Receiver
add_executable(info_receiver_executable
    Info_Receiver.cpp
)

# 链接静态库
target_link_libraries(main_executable my_lib)
target_link_libraries(info_receiver_executable my_lib)

target_link_libraries(main_executable procps z)
target_link_libraries(info_receiver_executable procps z)
