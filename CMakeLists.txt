cmake_minimum_required(VERSION 3.16)
project(MaterialDesignControls VERSION 1.0.0 LANGUAGES CXX)

# 查找 Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# 设置包含目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)

# 添加控件库
add_library(MaterialDesignControls STATIC
    src/MPushButton.cpp
    src/MLineEdit.cpp
    src/MCard.cpp
    src/MSlider.cpp
    src/MSwitch.cpp
    src/MCheckBox.cpp
    src/MRadioButton.cpp
    src/MProgressBar.cpp
)

# 包含头文件
target_include_directories(MaterialDesignControls PUBLIC include)

# 链接 Qt 模块
target_link_libraries(MaterialDesignControls PRIVATE
    Qt6::Core
    Qt6::Widgets
)

# 安装规则（可选）
install(TARGETS MaterialDesignControls DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/MaterialDesignControls)

# 添加示例（可选）
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples")
    add_subdirectory(examples)
endif()