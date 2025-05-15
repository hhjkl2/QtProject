cmake_minimum_required(VERSION 3.16)

project(qt-proxy-model-full-example VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)


qt_add_executable(appqt-proxy-model-full-example
    main.cpp
)

qt_add_qml_module(appqt-proxy-model-full-example
    URI qt-proxy-model-full-example
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES order_model.h
        SOURCES status_filter_proxy.h
        SOURCES time_sort_proxy.h
        SOURCES async_order_proxy.h
        SOURCES order.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqt-proxy-model-full-example PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqt-proxy-model-full-example
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqt-proxy-model-full-example
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appqt-proxy-model-full-example
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
