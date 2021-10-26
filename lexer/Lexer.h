#ifndef KALEIDO_LEXER_H
#define KALEIDO_LEXER_H

#include <string>
#include <memory>
#include <istream>
#include "Token.h"

namespace kaleido {
    class Lexer {
    public:
        Lexer(std::istream &input);
        std::unique_ptr<Token> nextToken() const;
    private:
        std::istream &mInput;
    };
}

#endif //KALEIDO_LEXER_H
