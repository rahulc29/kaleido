#include "CharwiseLexer.h"
std::unique_ptr<kaleido::Token> kaleido::CharwiseLexer::nextToken() const {

}
kaleido::CharwiseLexer::CharwiseLexer(std::istream &input) : mInput(input) {
}
