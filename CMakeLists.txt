cmake_minimum_required(VERSION 3.16)

project(Gameserver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Network Charts)

qt_standard_project_setup()

qt_add_executable(appGameserver
    main.cpp
    DataReceiver.h DataReceiver.cpp
    ViewModel.h ViewModel.cpp
)

qt_add_qml_module(appGameserver
    URI Gameserver
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(appGameserver PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appGameserver
    PRIVATE Qt6::Quick Qt6::Network Qt6::Charts
)

install(TARGETS appGameserver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
