cmake_minimum_required(VERSION 3.8)
project(collected)

set(CMAKE_CXX_STANDARD 14)

set(GSL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gsl/include)

# for fmt printing lib
add_subdirectory(fmt EXCLUDE_FROM_ALL)
#include_directories(fmt)

set(QT_PATH "/usr/local/opt/qt5")

set(QT_LIB_DIR ${QT_PATH}/lib/cmake)

set(Qt5Core_DIR "${QT_LIB_DIR}/Qt5Core")
set(Qt5Gui_DIR "${QT_LIB_DIR}/Qt5Gui")
set(Qt5Multimedia_DIR "${QT_LIB_DIR}/Qt5Multimedia")
set(Qt5Widgets_DIR "${QT_LIB_DIR}/Qt5Widgets")
set(Qt5OpenGL_DIR "${QT_LIB_DIR}/Qt5OpenGL")

set(QT_LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Multimedia
        Qt5::Widgets
        Qt5::OpenGL
        )

set(QT_LIBRARIES_REQUIRED
        Qt5Core
        Qt5Gui
        Qt5Multimedia
        Qt5Widgets
        Qt5OpenGL
        )

foreach (QT_LIBRARIES_REQUIRED ${QT_LIBRARIES_REQUIRED})
    find_package(${QT_LIBRARIES_REQUIRED} REQUIRED)
endforeach ()

#find_package(Boost REQUIRED COMPONENTS system)
find_package(Boost COMPONENTS filesystem system)

include_directories(${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${GSL_INCLUDE_DIR})
# include_directories(${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${GSL_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
