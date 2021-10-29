#include "RegexLexer.h"
#include <set>
std::regex kaleido::RegexLexer::IS_IDENTIFIER = std::regex("[a-zA-Z_][a-zA-Z0-9_]*");
std::regex kaleido::RegexLexer::IS_NUMBER = std::regex("[0-9]+\\.?[0-9]*");
std::regex kaleido::RegexLexer::IS_KEYWORD = std::regex("def|extern");
std::regex kaleido::RegexLexer::IS_OPERATOR = std::regex(R"(\+|\-|\*|\/|\(|\))");
std::regex kaleido::RegexLexer::IS_COMMENT = std::regex("^\\#.*");
kaleido::RegexLexer::RegexLexer(std::istream &input) : mInput(input) {
}
std::vector<std::unique_ptr<kaleido::Token>> kaleido::RegexLexer::tokenizeString(std::string &toTokenize) const {
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
    std::string nextPotentialToken;
    while (!mInput.eof()) {
        mInput >> nextPotentialToken;
        while (std::regex_match(nextPotentialToken, IS_COMMENT)) {
            mInput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mInput >> nextPotentialToken;
        }
        auto toAppend = std::move(tokenizeString(nextPotentialToken));
        // using std::vector<T>::insert() gives some error
        for (auto &i : toAppend) {
            toReturn.push_back(std::move(i));
        }
    }
    return toReturn;
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

