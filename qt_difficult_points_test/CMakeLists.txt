cmake_minimum_required(VERSION 3.16)

project(qt_difficult_points_test VERSION 0.1 LANGUAGES CXX)

# [1] 定义控制 GUI 测试的选项
option(ENABLE_GUI_TESTS "Enable GUI-related tests (requires Qt Widgets)" ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 新增：全局启用 SSE4.1 和 AVX 指令集
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")  # 仅对 GCC/Clang 生效
    add_compile_options(-msse4.1 -mavx -mavx2)       # 启用 SSE4.1 和 AVX
    message(STATUS "SSE4.1 和 AVX 指令集已全局启用 (-msse4.1 -mavx)")
elseif(MSVC)                                  # MSVC 编译器
    add_compile_options(/arch:AVX)            # MSVC 的 /arch:AVX 默认包含 SSE2
    message(STATUS "AVX 指令集已全局启用 (/arch:AVX)")
endif()

# [2] 动态查找 Qt 模块
if(ENABLE_GUI_TESTS)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Concurrent Network Test)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Concurrent Network Test)
else()
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Concurrent Network Test)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Concurrent Network Test)
endif()

# [3] 定义核心源文件（所有情况都包含）
set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        customPage.h
        udpcommunicator.h udpcommunicator.cpp
        customlinechart.h customlinechart.cpp
        quadtreenode.h quadtreenode.cpp
        Test/calculator.h Test/calculator.cpp
        Test/calculatortest.h Test/calculatortest.cpp
        Test/datadrivencalculatortest.h Test/datadrivencalculatortest.cpp
        Test/asynctest.h Test/asynctest.cpp
)

# [4] 动态包含 GUI 测试文件
if(ENABLE_GUI_TESTS)
    list(APPEND PROJECT_SOURCES
            Test/signalstest.cpp
            Test/signalstest.h
        )
    message(STATUS "GUI tests enabled")
else()
    message(STATUS "GUI tests disabled")
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt_difficult_points_test
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Test/testquadtree/testquadtree.cpp Test/testquadtree/testquadtree.h
        quadtreenode2.h quadtreenode2.cpp
        datapoint.h
        quadtree_simd.h quadtree_simd.cpp
        quadtreenode3.h quadtreenode3.cpp
        customwidget.h customwidget.cpp customwidget.ui
        templateclass.hpp
        complexobject.h complexobject.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qt_difficult_points_test APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qt_difficult_points_test SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qt_difficult_points_test
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# [5] 根据选项定义编译宏
if(ENABLE_GUI_TESTS)
    target_compile_definitions(qt_difficult_points_test
        PRIVATE HAS_GUI_TESTS
    )
endif()

# [6] 动态链接 Qt 模块
if(ENABLE_GUI_TESTS)
    target_link_libraries(qt_difficult_points_test PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
        Qt${QT_VERSION_MAJOR}::Concurrent
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Test
    )
else()
    target_link_libraries(qt_difficult_points_test PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Sql
        Qt${QT_VERSION_MAJOR}::Concurrent
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Test
    )
endif()

# [7] 其他平台相关配置（保持原样）
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.qt_difficult_points_test)
endif()
set_target_properties(qt_difficult_points_test PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS qt_difficult_points_test
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt_difficult_points_test)
endif()
