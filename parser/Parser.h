#ifndef KALEIDO_PARSER_PARSER_H
#define KALEIDO_PARSER_PARSER_H
#include "lexer/Lexer.h"
#include "parser/ast/TreeNode.h"
using kaleido::ast::TreeNode;
namespace kaleido::parser {
    class Parser {
    public:
        explicit Parser(std::unique_ptr<Lexer> lexer);
        // pointer to the root of the tree
        virtual std::unique_ptr<TreeNode> parse() const = 0;
    protected:
        std::unique_ptr<Lexer> mLexer;
    };
}
#endif //KALEIDO_PARSER_PARSER_H
