#include <gtest/gtest.h>
#include <fstream>
#include <lexer/RegexLexer.h>
#include "lexer/Lexer.h"
using namespace kaleido;

TEST(LexerTest, IdentifierTest) {
    std::istringstream input("def _bar 123\n"
                             "def __123 90.21");
    RegexLexer lexer(input);
    auto tokens = std::move(lexer.tokenize());
    EXPECT_EQ(tokens[0]->value(), "def");
    EXPECT_EQ(tokens[1]->type(), TokenType::TOKEN_IDENTIFIER);
    EXPECT_EQ(tokens[2]->type(), TokenType::TOKEN_NUMBER);
    auto weirdButValidIdentifier = std::move(tokens[4]);
    EXPECT_EQ(weirdButValidIdentifier->type(), TokenType::TOKEN_IDENTIFIER);
    EXPECT_EQ(weirdButValidIdentifier->value(), "__123");
    EXPECT_EQ(tokens[5]->type(), TokenType::TOKEN_NUMBER);
}

TEST(LexerTest, OperatorTest) {
    std::istringstream input("def baz ( 3 + ( 4 / 5 ) )");
    RegexLexer lexer(input);
    auto tokens = std::move(lexer.tokenize());
    EXPECT_EQ(tokens[2]->type(), TokenType::TOKEN_OPERATOR);
    // ignore `3`
    EXPECT_EQ(tokens[4]->value(), "+");
    EXPECT_EQ(tokens[5]->type(), TokenType::TOKEN_OPERATOR);
    // ignore `4`
    EXPECT_EQ(tokens[7]->value(), "/");
    // ignore `5`
    EXPECT_EQ(tokens[9]->value(), ")");
    EXPECT_EQ(tokens[10]->value(), ")");
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
    RegexLexer lexer(input);
    auto tokens = std::move(lexer.tokenize());
    auto first = std::move(tokens[0]);
    EXPECT_EQ(first->value(), "def");
    auto last = std::move(tokens[8]);
    EXPECT_EQ(last->value(), "69");
}

TEST(LexerTest, KeywordIdentifierNumber) {
    std::istringstream input("def foo 3");
    RegexLexer lexer(input);
    auto tokens = std::move(lexer.tokenize());
    auto first = std::move(tokens[0]);
    auto second = std::move(tokens[1]);
    auto third = std::move(tokens[2]);
    EXPECT_EQ(first->type(), TokenType::TOKEN_KEYWORD);
    EXPECT_EQ(first->value(), "def");
    EXPECT_EQ(second->type(), TokenType::TOKEN_IDENTIFIER);
    EXPECT_EQ(second->value(), "foo");
    EXPECT_EQ(third->type(), TokenType::TOKEN_NUMBER);
    EXPECT_EQ(third->value(), "3");
}

TEST(LexerTest, NonPrettyOperatorExpressionTest) {
    std::istringstream input("def foo 3+(4*5)");
    RegexLexer lexer(input);
    std::string toTokenize = "3+(4*5)";
    auto tokens = std::move(lexer.tokenizeString(toTokenize));
    EXPECT_EQ(tokens[0]->value(), "3");
    EXPECT_EQ(tokens[1]->type(), TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[2]->type(), TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[3]->value(), "4");
    EXPECT_EQ(tokens[4]->value(), "*");
    EXPECT_EQ(tokens[5]->value(), "5");
    EXPECT_EQ(tokens[6]->type(), TokenType::TOKEN_OPERATOR);
}

TEST(LexerTest, NobufferTokenizationTest) {
    std::istringstream input("def foo 3+(4*5)");
    RegexLexer lexer(input);
    auto tokens = std::move(lexer.tokenize());
    EXPECT_EQ(tokens[0]->value(), "def");
    EXPECT_EQ(tokens[1]->type(), TokenType::TOKEN_IDENTIFIER);
    EXPECT_EQ(tokens[2]->value(), "3");
    EXPECT_EQ(tokens[3]->type(), TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[4]->type(), TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[5]->value(), "4");
    EXPECT_EQ(tokens[6]->value(), "*");
    EXPECT_EQ(tokens[7]->value(), "5");
    EXPECT_EQ(tokens[8]->type(), TokenType::TOKEN_OPERATOR);
}

using testing::Eq;
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}