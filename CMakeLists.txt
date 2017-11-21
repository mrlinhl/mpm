project(mpm LANGUAGES CXX)

# Require C++11-compliant compiler; only available for CMake v. 3.1 and up
set(CMAKE_CXX_STANDARD 11)

cmake_minimum_required(VERSION 3.1)

SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

# General compile settings
IF (NOT CMAKE_BUILD_TYPE)
 SET(CMAKE_BUILD_TYPE "Debug")
 #SET(CMAKE_BUILD_TYPE "Release")
ENDIF (NOT CMAKE_BUILD_TYPE)

# GNU Specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

# CMake Modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Include directories
include_directories(
  ${mpm_SOURCE_DIR}/include/
  ${mpm_SOURCE_DIR}/external/
)

# mpm executable
SET(mpm_src
  src/main.cc
)
add_executable(mpm
  ${mpm_src}
)

# Unit test
SET(test_src
  ${mpm_SOURCE_DIR}/tests/test.cc
  ${mpm_SOURCE_DIR}/tests/node_test.cc
)   
add_executable(mpmtest
  ${test_src}
)
add_test(NAME mpmtest COMMAND $<TARGET_FILE:mpmtest>)
enable_testing()

# Coverage
find_package(codecov)
add_coverage(mpm)
add_coverage(mpmtest)