cmake_minimum_required(VERSION 3.14)

if (WIN32)
    project(smpcolorizer LANGUAGES CXX)
elseif(UNIX)
    project(smpcolorizer)
endif()

set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

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

include_directories(${point_INCLUDE_DIRS}
                    ${smpaint_INCLUDE_DIRS})

#=========================== Shared library setup ===========================#
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

if (WIN32)
	set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/bin/plugins)
else()
	set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin/plugins)
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE <QtWidgets>)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets
                                      point)

# Expose project public includes to other subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
