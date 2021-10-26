#ifndef KALEIDO_TOKEN_H
#define KALEIDO_TOKEN_H

#include <string>
#include <memory>

namespace kaleido {

    enum TokenType {
        // end of file
        TOKEN_EOF = -1,
        // keywords
        TOKEN_KEYWORD = -2,
        // identifiers
        TOKEN_IDENTIFIER = -3,
        // numeric constants
        TOKEN_NUMBER = -4
    };

    class Token {
    public:
        Token(std::string &value, const TokenType type);
        Token(std::string &&value, const TokenType type);
        TokenType type() const;
        const std::string &value() const;
        std::string &value();
        bool operator==(const Token &that);
        bool operator!=(const Token &that);
        static Token END_OF_FILE_TOKEN;
    protected:
        TokenType mTokenType;
        std::string mValue;
    };

}
#endif //KALEIDO_TOKEN_H
