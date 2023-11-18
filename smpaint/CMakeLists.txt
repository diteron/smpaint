cmake_minimum_required(VERSION 3.14)

if (WIN32)
    project(smpaint LANGUAGES CXX)
elseif(UNIX)
    project(smpaint)
endif()

set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

#=================== INCLUSION OF Project Files ====================#
set(SHAPES_DIR "${CMAKE_SOURCE_DIR}/shapes")
set(UI_DIR "${CMAKE_SOURCE_DIR}/ui")
set(CORE_DIR "${CMAKE_SOURCE_DIR}")

include_directories(${SHAPES_DIR})
include_directories(${UI_DIR})
include_directories(${CORE_DIR})

file(GLOB SRC_FILES
    "${SHAPES_DIR}/*.cpp"
    "${SHAPES_DIR}/*.h"
    "${UI_DIR}/*.cpp"
    "${UI_DIR}/*.h"
    "${CORE_DIR}/*.cpp"
    "${CORE_DIR}/*.h"
)

#=================== SETUP EXECTUABLE ====================#
# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# Add the executable
if (WIN32) 
    add_executable(smpaint WIN32 ${SRC_FILES})
elseif(UNIX)
    add_executable(smpaint ${SRC_FILES})
endif()

# Add precompiled headers
target_precompile_headers(smpaint PRIVATE <QtWidgets>)

# Add the target includes for smpaint 
target_include_directories(smpaint PRIVATE ${SHAPES_DIR})
target_include_directories(smpaint PRIVATE ${UI_DIR})
target_include_directories(smpaint PRIVATE ${CORE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(smpaint Qt6::Widgets)