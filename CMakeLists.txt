cmake_minimum_required(VERSION 2.8)
project(cmaketest)
if(POLICY CMP0037)
    cmake_policy(SET CMP0037 OLD)
endif()
#set(CMAKE_CXX_COMPILER "g++")
#add_compile_options(-Wall -std=c++11)
add_definitions(-Wall -std=c++11)
build_command(BUILD_COMMAND_LINE CONFIGURATION ${CMAKE_BUILD_TYPE})

message("build command:${BUILD_COMMAND_LINE}")

message("using compiler ${CMAKE_CXX_COMPILER}")
message("using compiler ${CMAKE_COMMAND}")

#link_directories(.)
#include_directories(.)

add_executable(test main.cpp)
#target_link_libraries(test iconv)

set(TEST_FILE "log.txt")
add_custom_command(OUTPUT  ${TEST_FILE}
  COMMAND echo "Generating log.txt file..."
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_FILE} ${TEST_FILE}
  DEPENDS ${TEST_FILE}
  COMMENT  "This is a test"
 )
add_custom_target(Test1 ALL DEPENDS ${TEST_FILE})


add_custom_command(TARGET Test1
  PRE_BUILD
  COMMAND echo "executing a fake command"
  COMMENT "This command will be executed before building target Test1"
 )
