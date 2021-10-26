#include "Token.h"

kaleido::TokenType kaleido::Token::type() const {
    return mTokenType;
}
std::string& kaleido::Token::value() {
    return mValue;
}
const std::string& kaleido::Token::value() const {
    return mValue;
}
kaleido::Token::Token(std::string& value, const kaleido::TokenType type) {
    mValue = value;
    mTokenType = type;
}
kaleido::Token::Token(std::string&& value, const kaleido::TokenType type) {
    mValue = value;
    mTokenType = type;
}
kaleido::Token kaleido::Token::END_OF_FILE_TOKEN = kaleido::Token("\0", kaleido::TOKEN_EOF);