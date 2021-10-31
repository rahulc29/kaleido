#ifndef KALEIDO_PARSER_BINARYEXPRESSION_H
#define KALEIDO_PARSER_BINARYEXPRESSION_H
#include "TreeNode.h"
namespace kaleido::ast {
    class BinaryExpression : public TreeNode {
    public:
        BinaryExpression(std::shared_ptr<TreeNode> leftChild, std::shared_ptr<TreeNode> rightChild);
        TreeNode &leftChild();
        const TreeNode &leftChild() const;
        TreeNode &rightChild();
        const TreeNode &rightChild() const;
        char opCode() const;
    protected:
        char mOpCode;
        std::shared_ptr<TreeNode> mLeftChild;
        std::shared_ptr<TreeNode> mRightChild;
    };
}
#endif //KALEIDO_PARSER_BINARYEXPRESSION_H
