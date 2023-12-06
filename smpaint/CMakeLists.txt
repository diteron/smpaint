cmake_minimum_required(VERSION 3.14)

if (WIN32)
    project(smpaint LANGUAGES CXX)
elseif(UNIX)
    project(smpaint)
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
set(SHAPES_DIR "${PROJECT_SOURCE_DIR}/shapes")
set(UI_DIR "${PROJECT_SOURCE_DIR}/ui")
set(PLUGINS_DIR "${PROJECT_SOURCE_DIR}/plugins")
set(CORE_DIR "${PROJECT_SOURCE_DIR}/core")

file(GLOB SRC_FILES
    "${SHAPES_DIR}/*.cpp"
    "${UI_DIR}/*.cpp"
    "${PLUGINS_DIR}/*.cpp"
    "${CORE_DIR}/*.cpp"
)

include_directories(${SHAPES_DIR}
                    ${UI_DIR}
                    ${PLUGINS_DIR}
                    ${CORE_DIR}
                    ${POINT_INCLUDE_DIRS})

#=========================== Executable setup ===========================#
if (WIN32) 
    add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
elseif(UNIX)
    add_executable(${PROJECT_NAME} ${SRC_FILES})
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE <QtWidgets>)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets
                                      POINT)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

# Expose project public includes to other subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${SHAPES_DIR}
                                 ${UI_DIR}
                                 ${PLUGINS_DIR}
                                 ${CORE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
