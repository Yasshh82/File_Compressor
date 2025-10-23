cmake_minimum_required(VERSION 3.16)

project(FileCompressorGUI VERSION 0.1 LANGUAGES CXX)

# Enable Qt features
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt libraries
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# -----------------------------
#  Include your backend folders
# -----------------------------
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# -----------------------------
#  Add your project sources
# -----------------------------
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        # backend files
        src/Huffman.cpp
        src/LZW.cpp

        # Optional utility headers (not compiled, but for indexing)
        include/Huffman.hpp
        include/LZW.hpp
        include/Utils.hpp
)

# -----------------------------
#  Create the executable
# -----------------------------
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FileCompressorGUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
else()
    add_executable(FileCompressorGUI
        ${PROJECT_SOURCES}
    )
endif()

# -----------------------------
#  Link Qt libraries
# -----------------------------
target_link_libraries(FileCompressorGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.FileCompressorGUI)
endif()
set_target_properties(FileCompressorGUI PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# -----------------------------
#  Install settings
# -----------------------------
include(GNUInstallDirs)
install(TARGETS FileCompressorGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# -----------------------------
#  Qt 6 finalization
# -----------------------------
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FileCompressorGUI)
endif()
