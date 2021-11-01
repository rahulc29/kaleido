#include "Parser.h"
kaleido::parser::Parser::Parser(std::unique_ptr<Lexer> lexer) : mLexer(std::move(lexer)) {

}
