cmake_minimum_required(VERSION 3.20)
project(kaleido)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 17)
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(kaleido lexer/Token.cpp lexer/Token.h lexer/Lexer.cpp lexer/Lexer.h main.cpp)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
target_link_libraries(kaleido gtest gtest_main)
llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(kaleido ${llvm_libs})