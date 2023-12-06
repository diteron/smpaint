cmake_minimum_required(VERSION 3.14)

if (WIN32)
    project(point LANGUAGES CXX)
elseif(UNIX)
    project(point)
endif()

set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

#===========================  ===========================#

#=========================== Qt setup ===========================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

#=========================== Project files ===========================#
file(GLOB SRC_FILES
    "*.cpp"
)

#=========================== Executable setup ===========================#
if (WIN32) 
    add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
elseif(UNIX)
    add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
endif()

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_precompile_headers(${PROJECT_NAME} PRIVATE <QtWidgets>)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

# Expose project public includes to other subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)