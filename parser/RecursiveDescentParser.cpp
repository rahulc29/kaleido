#include <iostream>
#include "RecursiveDescentParser.h"
#include "parser/ast/Variable.h"
#include "parser/ast/Invocation.h"
#include "parser/ast/Addition.h"
#include "parser/ast/Subtraction.h"
#include "parser/ast/Multiplication.h"
#include "parser/ast/Division.h"
#include "parser/ast/Prototype.h"
#include "parser/ast/Function.h"
using kaleido::ast::Variable;
using kaleido::ast::Invocation;
using kaleido::ast::Prototype;
using kaleido::ast::Function;
std::map<char, int> kaleido::parser::RecursiveDescentParser::OPERATOR_PRECEDENCE = {
    {'<', 1},
    {'+', 2},
    {'-', 2},
    {'*', 4}
};
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parse() {

}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parseLiteral() {
    // only kind of literal is double
    auto current = getCurrentToken();
    auto toReturn = std::make_unique<ast::Literal>(std::stod(current.value()));
    // eat the number literal
    getNextToken();
    return std::move(toReturn);
}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parseParenthesized() {
    getNextToken(); // eat '('
    auto inside = parseExpression();
    if (inside == nullptr) {
        // invalid on the inside means entire parenthesized is invalid
        return nullptr;
    }
    // parse expression will advance the stream till it hits a ')'
    if (getCurrentToken().value() != ")") {
        // if the next token is not a ')' we have a syntactic error
        std::cerr << "Expected ')'\n";
        return nullptr;
    }
    getNextToken(); // eat ')'
    return std::move(inside);
}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parseIdentifier() {
    auto identifier = getCurrentToken().value();
    auto current = getNextToken();
    if (current.value() != "(") {
        return std::make_unique<Variable>(current.value());
    }
    // function call
    current = getNextToken();
    std::vector<std::unique_ptr<ast::TreeNode>> args;
    if (current.value() != ")") {
        while (true) {
            if (auto arg = parseExpression()) {
                args.push_back(std::move(arg));
            } else {
                // even one null pointer in the args means invalid syntax
                return nullptr;
            }
            if (current.value() == ")") {
                break;
            }
            if (current.value() != ",") {
                std::cerr << "Expected only ')' and ',' in argument list\n";
                return nullptr;
            }
            getNextToken();
        }
    }
    getNextToken(); // eat ')'
    return std::make_unique<Invocation>(getCurrentToken().value(), std::move(args));
}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parseExpression() {
    auto lhs = parsePrimary();
    if (lhs == nullptr) {
        return nullptr;
    }
    return parseBinaryOperationRhs(0, std::move(lhs));
}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parsePrimary() {
    auto current = getCurrentToken();
    switch (current.type()) {
    case TOKEN_EOF:return nullptr;
    case TOKEN_KEYWORD:return nullptr;
    case TOKEN_IDENTIFIER:return parseIdentifier();
    case TOKEN_NUMBER:return parseLiteral();
    case TOKEN_OPERATOR:
        if (current.value() == "(") {
            return parseParenthesized();
        }
    case TOKEN_UNSPECIFIED:std::cerr << "Unexpected token " << current.value() << '\n';
        return nullptr;
    }
}
int kaleido::parser::RecursiveDescentParser::getPrecedence(const Token &token) {
    const auto &value = token.value();
    if (value.size() != 1) {
        return -1;
    }
    const auto maybeToReturn = OPERATOR_PRECEDENCE[value[0]];
    if (maybeToReturn <= 0) {
        return -1;
    }
    return maybeToReturn;
}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parseBinaryOperationRhs(int minPrecedence,
                                                                                           std::unique_ptr<TreeNode> lhs) {
    while (true) {
        auto tokenPrecedence = getPrecedence(getCurrentToken());
        if (tokenPrecedence < minPrecedence) {
            return lhs;
        }
        // worthy binary operator
        auto operatorToken = getNextToken(); // eat the operator
        auto rhs = parsePrimary(); // rhs must now be primary expression
        if (rhs == nullptr) {
            return nullptr;
        }
        // peek into next and decide how to group operators
        auto nextTokenPrecedence = getPrecedence(getCurrentToken());
        if (tokenPrecedence < nextTokenPrecedence) {
            rhs = parseBinaryOperationRhs(tokenPrecedence + 1, std::move(rhs));
            if (rhs == nullptr) {
                return nullptr;
            }
        }
        auto opCode = operatorToken.value()[0];
        switch (opCode) {
        case '+':lhs = std::make_unique<ast::Addition>(std::move(lhs), std::move(rhs));
            break;
        case '-':lhs = std::make_unique<ast::Subtraction>(std::move(lhs), std::move(rhs));
            break;
        case '*':lhs = std::make_unique<ast::Multiplication>(std::move(lhs), std::move(rhs));
            break;
        case '/':lhs = std::make_unique<ast::Division>(std::move(lhs), std::move(rhs));
            break;
        default:lhs = nullptr;
            break;
        }
    }
}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parsePrototype() {
    auto nameToken = getCurrentToken();
    // should be of the form id (id *)
    if (nameToken.type() != TOKEN_IDENTIFIER) {
        std::cerr << "Function prototype should start with identifier\n";
        return nullptr;
    }
    auto current = getNextToken();
    if (current.value() != "(") {
        std::cerr << "Function declaration is given by id([id]*)\n";
        return nullptr;
    }
    std::vector<std::string> args;
    current = getNextToken();
    while (current.type() == TOKEN_IDENTIFIER) {
        args.push_back(current.value());
        current = getNextToken();
    }
    if (current.value() != ")") {
        std::cerr << "Function declaration should end with ')'\n";
        return nullptr;
    }
    getNextToken(); // eat ')'
    return std::make_unique<Prototype>(nameToken.value(), std::move(args));
}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parseDefinition() {
    // def foo(a b c) a + (b * c)
    // functions are one expression only
    // current token must be 'def'
    getNextToken(); // eat the 'def'
    auto prototype = parsePrototype();
    // `prototypePtr` is a naked pointer that will be `null` iff
    // - `prototype` does not point to a `Prototype`
    // - `prototype` equals the null pointer
    auto prototypePtr = dynamic_cast<Prototype *>(prototype.get());
    if (prototype == nullptr || prototypePtr == nullptr) {
        return nullptr;
    }
    // release ownership from old pointer before creating new unique pointer
    prototype.release();
    std::unique_ptr<Prototype> toPassToMakeUnique(prototypePtr);
    // parse the single expression that makes up the function
    auto expression = parseExpression();
    if (expression == nullptr) {
        return nullptr;
    }
    return std::make_unique<Function>(std::move(toPassToMakeUnique), std::move(expression));
}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parseExtern() {
    // extern foo(a)
    // extern sin(a)
    // extern atan2(a b) etc
    getNextToken(); // eat the 'extern' keyword
    // extern functions only have a prototype 🥰
    return parsePrototype();
}
std::unique_ptr<TreeNode> kaleido::parser::RecursiveDescentParser::parseTopLevelExpression() {
    // top level expressions
    // 3 + 4 * 5
    // evaluated on the fly
    auto proto = std::make_unique<Prototype>("", std::vector<std::string>());
    auto expr = parseExpression();
    if (expr == nullptr) {
        return nullptr;
    }
    return std::make_unique<Function>(std::move(proto), std::move(expr));
}
kaleido::parser::RecursiveDescentParser::RecursiveDescentParser(std::unique_ptr<Lexer> lexer) : Parser(std::move(
    lexer)) {

}
