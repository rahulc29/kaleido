#ifndef KALEIDO_PARSER_AST_PROTOTYPE_H
#define KALEIDO_PARSER_AST_PROTOTYPE_H
#include "TreeNode.h"
namespace kaleido::ast {
    class Prototype : public TreeNode {
    public:
        Prototype(std::string name, std::vector<std::string> args);
        const std::string &name() const;
        const std::vector<std::string> &args() const;
    private:
        std::string mName;
        std::vector<std::string> mArgs;
    };
}
#endif //KALEIDO_PARSER_AST_PROTOTYPE_H
