#ifndef KALEIDO_PARSER_RECURSIVEDESCENTPARSER_H
#define KALEIDO_PARSER_RECURSIVEDESCENTPARSER_H
#include "Parser.h"
#include "parser/ast/Literal.h"
#include "lexer/Token.h"
using kaleido::ast::Literal;
using kaleido::ast::TreeNode;
using kaleido::Token;
namespace kaleido::parser {
    class RecursiveDescentParser : public Parser {
    public:
        RecursiveDescentParser(std::unique_ptr<Lexer> lexer);
        std::unique_ptr<TreeNode> parse() override;
        std::unique_ptr<TreeNode> parseLiteral();
        std::unique_ptr<TreeNode> parseParenthesized();
        std::unique_ptr<TreeNode> parseIdentifier();
        std::unique_ptr<TreeNode> parseExpression();
        std::unique_ptr<TreeNode> parsePrimary();
        virtual std::unique_ptr<TreeNode> parseBinaryOperationRhs(int minPrecedence, std::unique_ptr<TreeNode> lhs);
        std::unique_ptr<TreeNode> parsePrototype();
        std::unique_ptr<TreeNode> parseDefinition();
        std::unique_ptr<TreeNode> parseExtern();
        std::unique_ptr<TreeNode> parseTopLevelExpression();
    protected:
        static std::map<char, int> OPERATOR_PRECEDENCE;
        static int getPrecedence(const Token &token);
        std::vector<std::unique_ptr<Token>> mTokenStream = std::move(mLexer->tokenize());
        int mCurrentTokenIndex = 0;
        const Token &getNextToken() {
            return *mTokenStream[mCurrentTokenIndex++];
        }
        const Token &getCurrentToken() {
            return *mTokenStream[mCurrentTokenIndex];
        }
    };
}
#endif //KALEIDO_PARSER_RECURSIVEDESCENTPARSER_H
