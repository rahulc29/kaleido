#include "UnaryExpression.h"
kaleido::ast::UnaryExpression::UnaryExpression(const std::shared_ptr<TreeNode> child) {
    mChild = child;
}
kaleido::ast::TreeNode &kaleido::ast::UnaryExpression::child() {
    return *mChild;
}
const kaleido::ast::TreeNode &kaleido::ast::UnaryExpression::child() const {
    return *mChild;
}
