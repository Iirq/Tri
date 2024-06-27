# Works with 3.14 and tested through 3.29
cmake_minimum_required(VERSION 3.14...3.29)

# Project name and a few useful settings. Other commands can pick up the results
project(
  TriangleIntersection
  VERSION 0.1
  DESCRIPTION "simple triangle intersection routine"
  LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endif()

# FetchContent added in CMake 3.11, downloads during the configure step
# FetchContent_MakeAvailable was added in CMake 3.14; simpler usage
include(FetchContent)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

add_subdirectory(tests)
