cmake_minimum_required(VERSION 3.20)
project(kaleido)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 17)
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(kaleido lexer/Token.cpp lexer/Token.h lexer/Lexer.cpp lexer/Lexer.h main.cpp parser/ast/TreeNode.cpp parser/ast/TreeNode.h generator/Generator.cpp generator/Generator.h parser/ast/UnaryExpression.cpp parser/ast/UnaryExpression.h parser/ast/BinaryExpression.cpp parser/ast/BinaryExpression.h parser/ast/Negation.cpp parser/ast/Negation.h parser/ast/Addition.cpp parser/ast/Addition.h parser/ast/Multiplication.cpp parser/ast/Multiplication.h parser/ast/Division.cpp parser/ast/Division.h parser/ast/Subtraction.cpp parser/ast/Subtraction.h lexer/RegexLexer.cpp lexer/RegexLexer.h lexer/CharwiseLexer.cpp lexer/CharwiseLexer.h tests/LexerTest.cpp parser/ast/Literal.cpp parser/ast/Literal.h parser/ast/Variable.cpp parser/ast/Variable.h parser/ast/Invocation.cpp parser/ast/Invocation.h parser/ast/Prototype.cpp parser/ast/Prototype.h parser/ast/Function.cpp parser/ast/Function.h)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
include_directories(.)
target_link_libraries(kaleido gtest gtest_main)
llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(kaleido ${llvm_libs})