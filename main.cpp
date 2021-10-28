#include <gtest/gtest.h>
#include <fstream>
#include "lexer/Lexer.h"
using namespace kaleido;

TEST(LexerTest, IdentifierTest) {
    std::istringstream input("def _bar 123\n"
                             "def __123 90.21");
    Lexer lexer(input);
    EXPECT_EQ(lexer.nextToken()->value(), "def");
    EXPECT_EQ(lexer.nextToken()->type(), TokenType::TOKEN_IDENTIFIER);
    EXPECT_EQ(lexer.nextToken()->type(), TokenType::TOKEN_NUMBER);
    // skip next token
    lexer.nextToken();
    auto weirdButValidIdentifier = lexer.nextToken();
    EXPECT_EQ(weirdButValidIdentifier->type(), TokenType::TOKEN_IDENTIFIER);
    EXPECT_EQ(weirdButValidIdentifier->value(), "__123");
    EXPECT_EQ(lexer.nextToken()->type(), TokenType::TOKEN_NUMBER);
}

TEST(LexerTest, OperatorTest) {
    std::istringstream input("def baz ( 3 + ( 4 / 5 ) )");
    Lexer lexer(input);
    // ignore first two
    lexer.nextToken();
    lexer.nextToken();
    EXPECT_EQ(lexer.nextToken()->type(), TokenType::TOKEN_OPERATOR);
    lexer.nextToken(); // ignore `3`
    EXPECT_EQ(lexer.nextToken()->value(), "+");
    EXPECT_EQ(lexer.nextToken()->type(), TokenType::TOKEN_OPERATOR);
    lexer.nextToken(); // ignore `4`
    EXPECT_EQ(lexer.nextToken()->value(), "/");
    lexer.nextToken(); // ignore `5`
    EXPECT_EQ(lexer.nextToken()->value(), ")");
    EXPECT_EQ(lexer.nextToken()->value(), ")");
}

TEST(LexerTest, CommentsTest) {
    std::istringstream input("# This is a comment\n"
                             "# This is also a comment\n"
                             "#This too is a comment\n"
                             "# The lexer should ignore this\n"
                             "def foo 9\n"
                             "def bar 14\n"
                             "# This should also be ignored\n"
                             "#Soshouldthis\n"
                             "def baz 69");
    Lexer lexer(input);
    auto first = lexer.nextToken();
    EXPECT_EQ(first->value(), "def");
    for (auto i = 0; i < 7; i++) {
        lexer.nextToken();
    }
    auto last = lexer.nextToken();
    EXPECT_EQ(last->value(), "69");
}

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