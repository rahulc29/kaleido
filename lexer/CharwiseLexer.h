#ifndef KALEIDO_LEXER_CHARWISELEXER_H
#define KALEIDO_LEXER_CHARWISELEXER_H
#include "Lexer.h"
namespace kaleido {
    class CharwiseLexer : public Lexer {
    public:
        CharwiseLexer(std::istream &input);
    private:
        std::istream &mInput;
    };
}
#endif //KALEIDO_LEXER_CHARWISELEXER_H
