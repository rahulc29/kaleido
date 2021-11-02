#ifndef KALEIDO_PARSER_TREENODE_H
#define KALEIDO_PARSER_TREENODE_H
#include "generator/Generator.h"
#include <vector>
#include <memory>
namespace kaleido::ast {
    // superclass of all tree nodes
    // purely virtual non-instantiable class
    class TreeNode {
    public:
        virtual void generate(const kaleido::gen::Generator &generator);
    };
}
#endif //KALEIDO_PARSER_TREENODE_H
