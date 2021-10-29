#include "RegexLexer.h"
#include <set>
std::unique_ptr<kaleido::Token> kaleido::RegexLexer::nextToken() const {
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

std::regex kaleido::RegexLexer::IS_IDENTIFIER = std::regex("[a-zA-Z_][a-zA-Z0-9_]*");
std::regex kaleido::RegexLexer::IS_NUMBER = std::regex("[0-9]+\\.?[0-9]*");
std::regex kaleido::RegexLexer::IS_KEYWORD = std::regex("def|extern");
std::regex kaleido::RegexLexer::IS_OPERATOR = std::regex(R"(\+|\-|\*|\/|\(|\))");
std::regex kaleido::RegexLexer::IS_COMMENT = std::regex("^\\#.*");
kaleido::RegexLexer::RegexLexer(std::istream &input) : mInput(input) {
}
std::vector<std::unique_ptr<kaleido::Token>> kaleido::RegexLexer::tokenizeString(std::string &toTokenize) {
    // vector to store all the tokens
    std::vector<std::unique_ptr<Token>> toReturn;
    if (!toTokenize.empty()) {
        // highest priority is keywords
        if (std::regex_match(toTokenize, IS_KEYWORD)) {
            toReturn.push_back(std::make_unique<Token>(Token(toTokenize, TokenType::TOKEN_KEYWORD)));
            return toReturn;
        }
        // set to store all the regex match indices
        std::set<std::pair<std::smatch, TokenType>, decltype(&matchComparator)> matches(&matchComparator);
        // store all operator indices
        insertMatches(matches, toTokenize, IS_OPERATOR, TokenType::TOKEN_OPERATOR);
        // store all identifier indices
        insertMatches(matches, toTokenize, IS_IDENTIFIER, TokenType::TOKEN_IDENTIFIER);
        // store all number indices
        insertMatches(matches, toTokenize, IS_NUMBER, TokenType::TOKEN_NUMBER);
        toReturn.reserve(matches.size());
        for (const auto &match: matches) {
            toReturn.push_back(std::make_unique<Token>(Token(match.first.str(), match.second)));
        }
    }
    return toReturn;
}

std::vector<std::unique_ptr<kaleido::Token>> kaleido::RegexLexer::tokenize() const {
    std::vector<std::unique_ptr<Token>> toReturn;

}
bool kaleido::RegexLexer::matchComparator(const std::pair<std::smatch, TokenType> &a,
                                          const std::pair<std::smatch, TokenType> &b) {
    return a.first.position() < b.first.position();
}
void kaleido::RegexLexer::insertMatches(std::set<std::pair<std::smatch, TokenType>,
                                                 decltype(&matchComparator)> &matches,
                                        std::string &toTokenize,
                                        const std::regex &toApply,
                                        TokenType type) {
    auto iterationEnd = std::sregex_iterator();

    for (auto i = std::sregex_iterator(toTokenize.begin(), toTokenize.end(), toApply);
         i!=iterationEnd;
         ++i) {
        matches.insert({*i, type});
    }
}

