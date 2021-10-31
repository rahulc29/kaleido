#ifndef KALEIDO_PARSER_AST_VARIABLE_H
#define KALEIDO_PARSER_AST_VARIABLE_H
#include "TreeNode.h"
namespace kaleido::ast {
    class Variable : public TreeNode {
    public:
        explicit Variable(const std::string &&name = "");
        explicit Variable(std::string name = "");
    private:
        std::string mName;
    };
}
#endif //KALEIDO_PARSER_AST_VARIABLE_H
