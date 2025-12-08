cmake_minimum_required(VERSION 3.16)
project(SmartProject VERSION 0.1 LANGUAGES CXX)

# === Global options (safe defaults) ===
option(BUILD_TESTING "Build tests" ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Recommended: set default build type if not provided
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

# === Add library target ===
add_library(mylib STATIC
  lib/foo.cpp
)

# Public include directory for users of mylib
target_include_directories(mylib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>  # for installation
)

# Require C++20 for this target (modern approach)
target_compile_features(mylib PUBLIC cxx_std_20)

# Add compile definitions and options depending on compiler
target_compile_definitions(mylib PRIVATE MYLIB_INTERNAL=1)
target_compile_options(mylib PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# === Add executable and link library ===
add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE mylib)

# === Add tests using CTest / GoogleTest (example using FetchContent to bring in GoogleTest) ===
if(BUILD_TESTING)
  include(CTest)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  )
  FetchContent_MakeAvailable(googletest)

  add_executable(test_foo tests/test_foo.cpp)
  target_link_libraries(test_foo PRIVATE mylib gtest_main)
  add_test(NAME test_foo COMMAND test_foo)
endif()

# === Installation stanza (optional) ===
install(TARGETS mylib app
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include)