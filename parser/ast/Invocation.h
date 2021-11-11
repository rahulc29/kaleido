#ifndef KALEIDO_PARSER_AST_INVOCATION_H
#define KALEIDO_PARSER_AST_INVOCATION_H
#include "TreeNode.h"
namespace kaleido::ast {
    class Invocation : public TreeNode {
    public:
        Invocation(std::string toInvoke, std::vector<std::unique_ptr<TreeNode>> args);
        const std::string &toInvoke() const {
            return mToInvoke;
        }
        const std::vector<std::unique_ptr<TreeNode>> &args() const {
            return mArgs;
        }
    private:
        std::string mToInvoke;
        std::vector<std::unique_ptr<TreeNode>> mArgs;
    };
}
#endif //KALEIDO_PARSER_AST_INVOCATION_H
