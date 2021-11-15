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
        virtual std::vector<std::unique_ptr<Token>> tokenize() const  = 0;
    };
}

#endif //KALEIDO_LEXER_H
