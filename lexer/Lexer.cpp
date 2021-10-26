#include "Lexer.h"
#include "Token.h"

std::unique_ptr<kaleido::Token> kaleido::Lexer::nextToken() const {
    // TODO : Implement better tokenization algorithm
    std::string nextPotentialToken;
    // check for end of file before requesting string processing from stream
    if (mInput.peek()==EOF) {
        return std::make_unique<Token>(Token::END_OF_FILE_TOKEN);
    }
    mInput >> nextPotentialToken;
    std::unique_ptr<Token> toReturn;
    if (!nextPotentialToken.empty()) {
        // firstly, ignore the comments
        if (nextPotentialToken[0]=='#') {
            // recursor input stream to next line
            mInput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return nextToken();
        }
        // check for keywords
        // only two keywords :P
        if (nextPotentialToken=="def" || nextPotentialToken=="extern") {
            toReturn = std::make_unique<Token>(Token(nextPotentialToken, TokenType::TOKEN_KEYWORD));
        }
        try {
            std::stod(nextPotentialToken);
            toReturn = std::make_unique<Token>(Token(nextPotentialToken, TokenType::TOKEN_NUMBER));
        } catch (std::invalid_argument &argument) {
            // if not a keyword and not a numeric
            // token must be an identifier
            toReturn = std::make_unique<Token>(Token(nextPotentialToken, TokenType::TOKEN_IDENTIFIER));
        }
    }
    return toReturn;
}

kaleido::Lexer::Lexer(std::istream &input) : mInput(input) {
}
