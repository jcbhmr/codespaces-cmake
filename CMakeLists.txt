cmake_minimum_required(VERSION 3.31)

# Set experimental flag to enable `import std` support from CMake.
# This must be enabled before C++ language support.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
  # This specific value changes as experimental support evolves. See
  # `Help/dev/experimental.rst` in the CMake source corresponding to
  # your CMake build for the exact value to use.
  "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")

project(sampleapp LANGUAGES C CXX)

# Tell CMake that we explicitly want `import std`. This will initialize the
# property on all targets declared after this to 1
set(CMAKE_CXX_MODULE_STD 1)

option(BUILD_TESTING "Build the testing tree." OFF)
include(CTest)
option(BUILD_EXAMPLES "Build the examples tree." OFF)
option(BUILD_DOCS "Build the docs tree." OFF)

find_package(spdlog REQUIRED)

add_library(sampleapp)
target_sources(sampleapp PUBLIC FILE_SET CXX_MODULES FILES src/lib.cpp src/basic_ops.cpp src/stats/mod.cpp src/stats/one_var.cpp)
target_compile_features(sampleapp PUBLIC cxx_std_23)
target_link_libraries(sampleapp PRIVATE spdlog::spdlog)
add_library(sample-app::sampleapp ALIAS sampleapp)

add_executable(hello-world src/bin/hello-world.cpp)
target_compile_features(hello-world PRIVATE cxx_std_23)
target_link_libraries(hello-world PRIVATE sampleapp spdlog::spdlog)
add_executable(sample-app::hello-world ALIAS hello-world)

add_executable(goodbye-world src/bin/goodbye-world.cpp)
target_compile_features(goodbye-world PRIVATE cxx_std_23)
target_link_libraries(goodbye-world PRIVATE sampleapp spdlog::spdlog)
add_executable(sample-app::goodbye-world ALIAS goodbye-world)

if(BUILD_TESTING)
  create_test_sourcelist(TESTS_SRC_LIST tests-src src/greet.c)
  add_executable(tests-src tests-src src/lib.cpp src/add.cpp src/greet.c)
  target_compile_features(tests-src PRIVATE c_std_23)
  target_compile_features(tests-src PRIVATE cxx_std_23)
  target_compile_definitions(tests-src PRIVATE BUILD_TESTING=1)
  target_include_directories(sampleapp PRIVATE include/sampleapp)
  target_link_libraries(sampleapp PRIVATE spdlog::spdlog)
  add_test(NAME tests-src COMMAND tests-src)

  add_executable(tests-hello-goodbye tests/hello-goodbye.c)
  target_compile_features(tests-hello-goodbye PRIVATE c_std_23)
  target_link_libraries(tests-hello-goodbye PRIVATE sampleapp spdlog::spdlog)
  add_test(NAME tests-hello-goodbye COMMAND tests-hello-goodbye)
endif()

if(BUILD_EXAMPLES)
  add_executable(examples-adder examples/adder.cpp)
  target_compile_features(examples-adder PRIVATE cxx_std_23)
  target_link_libraries(examples-adder PRIVATE sampleapp spdlog::spdlog)
endif()

if(BUILD_DOCS)
  find_package(Doxygen)

  doxygen_add_docs(docs)
endif()
