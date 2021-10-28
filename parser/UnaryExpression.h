#ifndef KALEIDO_PARSER_UNARYEXPRESSION_H
#define KALEIDO_PARSER_UNARYEXPRESSION_H
#include "TreeNode.h"
namespace kaleido::ast {
    class UnaryExpression : public TreeNode {
    public:
        UnaryExpression(const std::shared_ptr<TreeNode> child);
        TreeNode &child();
        const TreeNode &child() const;
    protected:
        std::shared_ptr<TreeNode> mChild;
        // always has size = 1
    };
}
#endif //KALEIDO_PARSER_UNARYEXPRESSION_H
