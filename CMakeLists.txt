#############################################################################
# LibreMines                                                                #
# Copyright (C) 2020-2021  Bruno Bollos Correa                              #                                                                         #
# This program is free software: you can redistribute it and/or modify      #
# it under the terms of the GNU General Public License as published by      #
# the Free Software Foundation, either version 3 of the License, or         #
# (at your option) any later version.                                       #
#                                                                           #
# This program is distributed in the hope that it will be useful,           #
# but WITHOUT ANY WARRANTY; without even the implied warranty of            #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
# GNU General Public License for more details.                              #
#                                                                           #
# You should have received a copy of the GNU General Public License         #
# along with this program.  If not, see <http://www.gnu.org/licenses/>.     #
#############################################################################

message(STATUS "Using CMake version ${CMAKE_VERSION}")
cmake_minimum_required(VERSION 3.1.0)
project(libremines
    VERSION "1.4.0"
    DESCRIPTION "A Qt based Minesweeper game"
    HOMEPAGE_URL "https://github.com/Bollos00/LibreMines"
    LANGUAGES "CXX"
)

# Save the variables of the project (see file `include/cmake/libreminesconfig.h.in`) on
#  the file ${PROJECT_BINARY_DIR}/libreminesconfig.h
configure_file(${PROJECT_SOURCE_DIR}/include/libreminesconfig.h.in ${PROJECT_BINARY_DIR}/libreminesconfig.h)
include_directories(${PROJECT_BINARY_DIR})

if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "Using default build type Release")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
string(COMPARE EQUAL "${CMAKE_CXX_STANDARD}" "" no_cmake_cxx_standard_set)
if(no_cmake_cxx_standard_set)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    message(STATUS "Using default C++ standard ${CMAKE_CXX_STANDARD}")
else()
    message(STATUS "Using user specified C++ standard ${CMAKE_CXX_STANDARD}")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME}
    src/common.cpp
    src/common.h
    src/main.cpp
    src/libreminespreferencesdialog.cpp
    src/libreminespreferencesdialog.h
    src/libreminespreferencesdialog.ui
    src/libreminesgameengine.cpp
    src/libreminesgameengine.h
    src/libreminesgui.cpp
    src/libreminesgui.h
    src/libreminesscore.cpp
    src/libreminesscore.h
    src/libreminesscoresdialog.cpp
    src/libreminesscoresdialog.h
    src/libreminesviewscores.cpp
    src/libreminesviewscores.h
    src/qkeyinput.cpp
    src/qkeyinput.h
    src/qlabel_adapted.cpp
    src/qlabel_adapted.h
    src/qpushbutton_adapted.cpp
    src/qpushbutton_adapted.h
    share/facesreaction.qrc
    share/icons.qrc
    share/minefield_icons.qrc
)

include_directories(src)
include_directories(include)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DEPRECATED_WARNINGS)

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060000)
# disables all the APIs deprecated before Qt 6.0.0


# Add the Qt dependencies according to the option `USE_QT6`
if(USE_QT6)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
    find_package(Qt6 REQUIRED COMPONENTS Core)
    find_package(Qt6 REQUIRED COMPONENTS Svg)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Svg)
else()
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt5 REQUIRED COMPONENTS Core)
    find_package(Qt5 REQUIRED COMPONENTS Svg)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Svg)
endif()

# create install target
include(GNUInstallDirs)

# Install the executable
install(
    TARGETS
    ${PROJECT_NAME}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # set include path for installed library target
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install the desktop entry and the icon
install(FILES share/desktop_entry/libremines.desktop DESTINATION share/applications)
install(FILES share/icons/libremines.svg DESTINATION share/icons/hicolor/scalable/apps)
