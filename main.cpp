#include <gtest/gtest.h>
#include "lexer/Lexer.h"
using namespace kaleido;
TEST(LexerTest, KeywordIdentifierNumber) {
    std::istringstream input("def foo 3");
    Lexer lexer(input);
    auto first = lexer.nextToken();
    auto second = lexer.nextToken();
    auto third = lexer.nextToken();
    auto eof = lexer.nextToken();
    EXPECT_EQ(first->type(), TokenType::TOKEN_KEYWORD);
    EXPECT_EQ(first->value(), "def");
    EXPECT_EQ(second->type(), TokenType::TOKEN_IDENTIFIER);
    EXPECT_EQ(second->value(), "foo");
    EXPECT_EQ(third->type(), TokenType::TOKEN_NUMBER);
    EXPECT_EQ(third->value(), "3");
    EXPECT_EQ(eof->type(), TokenType::TOKEN_EOF);
}

using testing::Eq;
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}