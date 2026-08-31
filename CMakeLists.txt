cmake_minimum_required(VERSION 3.21)

project(ActionExample
    VERSION 1.0.0
    DESCRIPTION "A small cross-platform Qt QAction example"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
include(CTest)

# Prefer Qt 6, but keep the example convenient for systems that still ship Qt 5.
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(actionexample_core STATIC
    src/counter.cpp
    src/counter.h
)
target_include_directories(actionexample_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(ActionExample
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
    )
else()
    add_executable(ActionExample
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
    )
endif()

target_link_libraries(ActionExample PRIVATE
    actionexample_core
    Qt${QT_VERSION_MAJOR}::Widgets
)

foreach(target actionexample_core ActionExample)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive- /utf-8)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endforeach()

set_target_properties(ActionExample PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_NAME "Action Example"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.actionexample"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
    MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
)

install(TARGETS ActionExample
    BUNDLE DESTINATION .
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

# Qt 6.3+ can assemble a self-contained install tree on all CI platforms.
if(QT_VERSION_MAJOR EQUAL 6 AND Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_generate_deploy_app_script(
        TARGET ActionExample
        OUTPUT_SCRIPT deploy_script
        NO_TRANSLATIONS
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT "${deploy_script}")
endif()

if(BUILD_TESTING)
    add_executable(counter_tests
        tests/counter_test.cpp
        src/counter.cpp
    )
    target_include_directories(counter_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
    if(MSVC)
        target_compile_options(counter_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(counter_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME counter-model COMMAND counter_tests)
endif()
