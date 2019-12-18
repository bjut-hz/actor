cmake_minimum_required(VERSION 3.9)

project(Actor)

option(ACTOR_BUILD_TESTS "Build Actor's unit tests" ON)
set(ACTOR_PUBLIC_INCLUDE_DIR "include/")

# This project requires C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )

# 编译器用来寻找include文件的目录
include_directories (
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}"
)




add_library(Actor "")
target_sources(Actor
  PRIVATE
    "${ACTOR_PUBLIC_INCLUDE_DIR}/actor.h"
    "${ACTOR_PUBLIC_INCLUDE_DIR}/basic.h"
    "${ACTOR_PUBLIC_INCLUDE_DIR}/context.h"
    "${ACTOR_PUBLIC_INCLUDE_DIR}/handle.h"
    "${ACTOR_PUBLIC_INCLUDE_DIR}/message_queue.h"
    "${ACTOR_PUBLIC_INCLUDE_DIR}/message.h"
    "${ACTOR_PUBLIC_INCLUDE_DIR}/name_service.h"

    "${PROJECT_SOURCE_DIR}/src/actor.cc"
    "${PROJECT_SOURCE_DIR}/src/context.cc"
    "${PROJECT_SOURCE_DIR}/src/handle.cc"
    "${PROJECT_SOURCE_DIR}/src/message_queue.cc"

)

if(ACTOR_BUILD_TESTS)
  # enable_testing()
  function(actor_test test_file)
    get_filename_component(test_target_name "${test_file}" NAME_WE)
  
    add_executable("${test_target_name}" "")
    target_sources("${test_target_name}"
      PRIVATE
        "${test_file}"
    )
    target_link_libraries("${test_target_name}" Actor)
  
    add_test(NAME "${test_target_name}" COMMAND "${test_target_name}")
  endfunction(actor_test)

  actor_test("${PROJECT_SOURCE_DIR}/simple_test.cc")
endif(ACTOR_BUILD_TESTS)

install(
  FILES
)