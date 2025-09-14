cmake_minimum_required(VERSION 3.16)
project(TestApp)
project(TestMPushButton)

# 设置库的安装路径
set(CMAKE_PREFIX_PATH "D:/QMaterialDesign;${CMAKE_PREFIX_PATH}")

# 查找Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# 查找你的库
find_package(QMaterialDesign REQUIRED)

# 添加可执行文件
add_executable(TestApp main.cpp)
add_executable(TestMPushButton MPushButton-Test.cpp)

# 链接库
target_link_libraries(TestApp PRIVATE
        Qt6::Core
        Qt6::Widgets
        QMaterialDesign::QMaterialDesign
)

target_link_libraries(TestMPushButton PRIVATE
        Qt6::Core
        Qt6::Widgets
        QMaterialDesign::QMaterialDesign
)

# Windows下自动复制DLL
if(WIN32)
    add_custom_command(TARGET TestMPushButton POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:QMaterialDesign::QMaterialDesign>
            $<TARGET_FILE_DIR:TestApp>
    )
endif()
