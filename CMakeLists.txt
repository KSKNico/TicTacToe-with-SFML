# Semi-recent, I don't want to deal with outdated distro BS
cmake_minimum_required(VERSION 3.15)

# Forbid in-source builds
if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "In-source builds are disabled.
    Please create a subfolder and use `cmake ..` inside it.
    NOTE: cmake will now create CMakeCache.txt and CMakeFiles/*.
          You must delete them, or cmake will refuse to work.")
endif()

list(APPEND SOURCE_FILES "TicTacToe/Drawing.cpp" "TicTacToe/Game.cpp" "TicTacToe/main.cpp")

project(tic-tac-toe VERSION 0.1
                  DESCRIPTION "A simple TicTacToe game with configureable dimensions and win conditions"
                  LANGUAGES CXX)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics network)

target_link_libraries(${PROJECT_NAME} fml-system sfml-window sfml-graphics sfml-network)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})

# We want ISO C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -pedantic -Werror)
# Apparently cmake is so broken that C++17 doesn't actually get passed to the compiler without this
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Boilerplate for setting the build type
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()