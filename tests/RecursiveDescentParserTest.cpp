#include "parser/RecursiveDescentParser.h"
#include "parser/ast/Function.h"
#include "parser/ast/Addition.h"
#include "lexer/RegexLexer.h"
#include "utils/PointerUtils.h"
#include <gtest/gtest.h>
#include "parser/ast/Multiplication.h"
#include "parser/ast/Division.h"
using namespace kaleido::parser;
using namespace kaleido;
using namespace kaleido::ast;
TEST(RecursiveDescentParserTest, TopLevelExpressions) {
    std::istringstream istream("3 + 4 * 5");
    std::unique_ptr<Lexer> toPass = std::make_unique<RegexLexer>(istream);
    RecursiveDescentParser parser(std::move(toPass));
    auto functionResult = dynamic_cast<Function *>(parser.parseTopLevelExpression().release());
    EXPECT_EQ(functionResult->prototype().name(), "");
    EXPECT_EQ(functionResult->prototype().args().size(), 0);
    const auto &expression = dynamic_cast<const BinaryExpression &>(functionResult->body());
    const auto &lhs = dynamic_cast<const Literal &>(expression.leftChild());
    const auto &rhs = dynamic_cast<const Multiplication &>(expression.rightChild());
    EXPECT_EQ(lhs.value(), 3);
    const auto &shouldBe4 = dynamic_cast<const Literal &>(rhs.leftChild());
    const auto &shouldBe5 = dynamic_cast<const Literal &>(rhs.rightChild());
    EXPECT_EQ(shouldBe4.value(), 4);
    EXPECT_EQ(shouldBe5.value(), 5);
}
TEST(RecursiveDescentParserTest, ParenthesesExpressions) {
    std::istringstream istream("( 3 + ( 5 / 6 ) )");
    std::unique_ptr<Lexer> toPass = std::make_unique<RegexLexer>(istream);
    RecursiveDescentParser parser(std::move(toPass));
    auto result = dynamic_cast<Function *>(parser.parseTopLevelExpression().release());
    const auto &expression = dynamic_cast<const BinaryExpression &>(result->body());
}