#include "BinaryExpression.h"
kaleido::ast::TreeNode &kaleido::ast::BinaryExpression::leftChild() {
    return *mLeftChild;
}
const kaleido::ast::TreeNode &kaleido::ast::BinaryExpression::leftChild() const {
    return *mLeftChild;
}
kaleido::ast::TreeNode &kaleido::ast::BinaryExpression::rightChild() {
    return *mRightChild;
}
const kaleido::ast::TreeNode &kaleido::ast::BinaryExpression::rightChild() const {
    return *mRightChild;
}
kaleido::ast::BinaryExpression::BinaryExpression(std::unique_ptr<TreeNode> leftChild,
                                                 std::unique_ptr<TreeNode> rightChild) {
    mLeftChild = std::move(leftChild);
    mRightChild = std::move(rightChild);
}
char kaleido::ast::BinaryExpression::opCode() const {
    return mOpCode;
}
