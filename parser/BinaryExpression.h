#ifndef KALEIDO_PARSER_BINARYEXPRESSION_H
#define KALEIDO_PARSER_BINARYEXPRESSION_H
#include "TreeNode.h"
namespace kaleido::ast {
    class BinaryExpression : public TreeNode {
    public:
        TreeNode &leftChild();
        const TreeNode &leftChild() const;
        TreeNode &rightChild();
        const TreeNode &rightChild() const;
    protected:
        std::shared_ptr<TreeNode> mLeftChild;
        std::shared_ptr<TreeNode> mRightChild;
    };
}
#endif //KALEIDO_PARSER_BINARYEXPRESSION_H
