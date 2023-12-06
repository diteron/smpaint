cmake_minimum_required(VERSION 3.14)

if (WIN32)
    project(smp LANGUAGES CXX)
elseif(UNIX)
    project(smp)
endif()

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(SEND_ERROR "In-source builds are not allowed.")
endif ()

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
	set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

add_subdirectory(point)
add_subdirectory(smpaint)
add_subdirectory(mirrorreflect)
add_subdirectory(shapescaler)
add_subdirectory(smpcolorizer)
