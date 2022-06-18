cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

option(LIB_OPT "Compile shared libraries (ON) or static (OFF)" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message("<<========== ${CMAKE_SOURCE_DIR} ==========>>")
include(${CMAKE_SOURCE_DIR}/cmake/MakeLibrary.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/FetchEigen.cmake)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

project(GaussianUtils)
add_subdirectory(src)

option(BUILD_GaussianUtils_TESTS "" OFF)
if(BUILD_GaussianUtils_TESTS)
	project(GaussianUtils-Tests)
    add_subdirectory(tests)
endif()

