# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(qmlTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Charts QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appqmlTest
    main.cpp
)

qt_add_qml_module(appqmlTest
    URI qmlTest
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES MyMessageBox.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqmlTest PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqmlTest
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqmlTest
    PRIVATE Qt6::Quick Qt6::Charts Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appqmlTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
