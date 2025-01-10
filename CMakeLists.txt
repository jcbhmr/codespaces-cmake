cmake_minimum_required(VERSION 3.31)

project(sampleapp LANGUAGES C CXX)

option(BUILD_TESTING "Build the testing tree." OFF)
include(CTest)
option(BUILD_EXAMPLES "Build the examples tree." OFF)
option(BUILD_DOCS "Build the docs tree." OFF)

find_package(spdlog REQUIRED)

add_library(sampleapp)
target_sources(sampleapp PUBLIC FILE_SET CXX_MODULES FILES src/lib.cpp src/add.cpp)
target_sources(sampleapp PRIVATE src/greet.c)
target_include_directories(sampleapp PUBLIC include/sampleapp)
target_link_libraries(sampleapp PRIVATE spdlog::spdlog)
add_library(sample-app::sampleapp ALIAS sampleapp)

add_executable(hello-world src/bin/hello-world.cpp)
target_link_libraries(hello-world PRIVATE sampleapp spdlog::spdlog)
add_executable(sample-app::hello-world ALIAS hello-world)

add_executable(goodbye-world src/bin/goodbye-world.cpp)
target_link_libraries(goodbye-world PRIVATE sampleapp spdlog::spdlog)
add_executable(sample-app::goodbye-world ALIAS goodbye-world)

if(BUILD_TESTING)
  create_test_sourcelist(TESTS_SRC_LIST tests-src src/greet.c)
  add_executable(tests-src tests-src src/lib.cpp src/add.cpp src/greet.c)
  target_compile_definitions(tests-src PUBLIC BUILD_TESTING=1)
  target_include_directories(sampleapp PUBLIC include/sampleapp)
  target_link_libraries(sampleapp PRIVATE spdlog::spdlog)
  add_test(NAME tests-src COMMAND tests-src)

  add_executable(tests-hello-goodbye tests/hello-goodbye.c)
  target_link_libraries(tests-hello-goodbye PRIVATE sampleapp spdlog::spdlog)
  add_test(NAME tests-hello-goodbye COMMAND tests-hello-goodbye)
endif()

if(BUILD_EXAMPLES)
  add_executable(examples-adder examples/adder.cpp)
  target_link_libraries(tests-hello-goodbye PRIVATE sampleapp spdlog::spdlog)
endif()

if(BUILD_DOCS)
  find_package(Doxygen)

  doxygen_add_docs(docs)
endif()
