#include "Function.h"
kaleido::ast::Function::Function(std::unique_ptr<Prototype> prototype, std::unique_ptr<TreeNode> body) :
    mPrototype(std::move(prototype)), mBody(std::move(body)) {

}
const kaleido::ast::Prototype &kaleido::ast::Function::prototype() const {
    return *mPrototype;
}
const kaleido::ast::TreeNode &kaleido::ast::Function::body() const {
    return *mBody;
}
