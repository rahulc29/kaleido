#include <sstream>
#include "Lexer.h"
#include "Token.h"

std::unique_ptr<kaleido::Token> kaleido::Lexer::nextToken() const {
    std::string nextPotentialToken;
    // check for end of file before requesting string processing from stream
    if (mInput.peek()==EOF) {
        return std::make_unique<Token>(Token::END_OF_FILE_TOKEN);
    }
    mInput >> nextPotentialToken;
    std::unique_ptr<Token> toReturn;
    if (!nextPotentialToken.empty()) {
        // firstly, ignore the comments
        if (std::regex_match(nextPotentialToken, IS_COMMENT)) {
            // recursor input stream to next line
            mInput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return nextToken();
        }
        // check for keywords
        if (std::regex_match(nextPotentialToken, IS_KEYWORD)) {
            toReturn = std::make_unique<Token>(Token(nextPotentialToken, TokenType::TOKEN_KEYWORD));
            return toReturn;
        }
        // check if number
        if (std::regex_match(nextPotentialToken, IS_NUMBER)) {
            toReturn = std::make_unique<Token>(Token(nextPotentialToken, TokenType::TOKEN_NUMBER));
            return toReturn;
        }
        // check for operators
        if (std::regex_match(nextPotentialToken, IS_OPERATOR)) {
            toReturn = std::make_unique<Token>(Token(nextPotentialToken, TokenType::TOKEN_OPERATOR));
            return toReturn;
        }
        // check for identifiers
        if (std::regex_match(nextPotentialToken, IS_IDENTIFIER)) {
            toReturn = std::make_unique<Token>(Token(nextPotentialToken, TokenType::TOKEN_IDENTIFIER));
            return toReturn;
        }
        // no regex matches
        toReturn = std::make_unique<Token>(Token(nextPotentialToken, TokenType::TOKEN_UNSPECIFIED));
    }
    return toReturn;
}

kaleido::Lexer::Lexer(std::istream &input) : mInput(input) {
}

std::regex kaleido::Lexer::IS_IDENTIFIER = std::regex("[a-zA-Z_][a-zA-Z0-9_]*");
std::regex kaleido::Lexer::IS_NUMBER = std::regex("[0-9]+\\.?[0-9]*");
std::regex kaleido::Lexer::IS_KEYWORD = std::regex("def|extern");
std::regex kaleido::Lexer::IS_OPERATOR = std::regex(R"(\+|\-|\*|\/|\(|\))");
std::regex kaleido::Lexer::IS_COMMENT = std::regex("^\\#.*");