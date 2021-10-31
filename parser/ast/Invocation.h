#ifndef KALEIDO_PARSER_AST_INVOCATION_H
#define KALEIDO_PARSER_AST_INVOCATION_H
#include "TreeNode.h"
namespace kaleido::ast {
    class Invocation : public TreeNode {
    public:
        Invocation(std::string toInvoke, std::vector<std::shared_ptr<TreeNode>> args);
    private:
        std::string mToInvoke;
        std::vector<std::shared_ptr<TreeNode>> mArgs;
    };
}
#endif //KALEIDO_PARSER_AST_INVOCATION_H
