#include "Prototype.h"
kaleido::ast::Prototype::Prototype(std::string name, std::vector<std::string> args)
    : mName(std::move(name)), mArgs(std::move(args)) {

}
const std::string &kaleido::ast::Prototype::name() const {
    return mName;
}
