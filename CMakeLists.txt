cmake_minimum_required(VERSION 3.16)
project(QMaterialDesign VERSION 1.0.0 LANGUAGES CXX)

# 查找 Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# 设置包含目录和自动功能
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

# 定义导出宏
if(WIN32)
    add_definitions(-DQMATERIALDESIGN_EXPORTS)
endif()

# 添加头文件列表
set(HEADER_FILES
        include/MPushButton.h
        include/MLineEdit.h
        include/MCard.h
        include/MSlider.h
        include/MSwitch.h
        include/MCheckBox.h
        include/MRadioButton.h
        include/MProgressBar.h
)

# 添加源文件列表
set(SOURCE_FILES
        src/MPushButton.cpp
        src/MLineEdit.cpp
        src/MCard.cpp
        src/MSlider.cpp
        src/MSwitch.cpp
        src/MCheckBox.cpp
        src/MRadioButton.cpp
        src/MProgressBar.cpp
)

# 添加控件库
add_library(QMaterialDesign SHARED
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

# 设置版本信息
set_target_properties(QMaterialDesign PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        OUTPUT_NAME "QMaterialDesign"
        PUBLIC_HEADER "${HEADER_FILES}"
)

# 包含头文件
target_include_directories(QMaterialDesign PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 链接 Qt 模块
target_link_libraries(QMaterialDesign PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
)

# 安装目标
install(TARGETS QMaterialDesign
        EXPORT QMaterialDesignTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)

# 安装头文件目录
install(DIRECTORY include/ DESTINATION include)

# 生成包配置文件
include(CMakePackageConfigHelpers)

# 创建配置文件
configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/QMaterialDesignConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/QMaterialDesignConfig.cmake
        INSTALL_DESTINATION lib/cmake/QMaterialDesign
)

# 创建版本文件
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/QMaterialDesignConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

# 安装导出文件
install(EXPORT QMaterialDesignTargets
        FILE QMaterialDesignTargets.cmake
        NAMESPACE QMaterialDesign::
        DESTINATION lib/cmake/QMaterialDesign
)

# 安装配置文件
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QMaterialDesignConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QMaterialDesignConfigVersion.cmake
        DESTINATION lib/cmake/QMaterialDesign
)

# 添加示例
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples")
    add_subdirectory(examples)
endif()