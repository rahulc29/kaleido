#ifndef KALEIDO_LEXER_REGEXLEXER_H
#define KALEIDO_LEXER_REGEXLEXER_H
#include <set>
#include "Lexer.h"
namespace kaleido {
    class RegexLexer : public Lexer {
    public:
        RegexLexer(std::istream &input);
        std::vector<std::unique_ptr<Token>> tokenize() const override;
        std::vector<std::unique_ptr<Token>> tokenizeString(std::string &toTokenize) const;
    private:
        static std::regex IS_IDENTIFIER;
        static std::regex IS_NUMBER;
        static std::regex IS_KEYWORD;
        static std::regex IS_OPERATOR;
        static std::regex IS_COMMENT;
        std::istream &mInput;
        static bool matchComparator(const std::pair<std::smatch, TokenType> &a,
                                    const std::pair<std::smatch, TokenType> &b);
        static void insertMatches(std::set<std::pair<std::smatch, TokenType>,
                                           decltype(&matchComparator)> &matches,
                                  std::string &toTokenize,
                                  const std::regex &toApply,
                                  TokenType type);

    };
}
#endif //KALEIDO_LEXER_REGEXLEXER_H
