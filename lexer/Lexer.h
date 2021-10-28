#ifndef KALEIDO_LEXER_H
#define KALEIDO_LEXER_H

#include <string>
#include <memory>
#include <istream>
#include <regex>
#include "Token.h"

namespace kaleido {
    class Lexer {
    public:
        Lexer(std::istream &input);
        std::unique_ptr<Token> nextToken() const;
    private:
        std::istream &mInput;
        static std::regex IS_IDENTIFIER;
        static std::regex IS_NUMBER;
        static std::regex IS_KEYWORD;
        static std::regex IS_OPERATOR;
        static std::regex IS_COMMENT;
    };
}

#endif //KALEIDO_LEXER_H
