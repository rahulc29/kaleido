#include "Invocation.h"
#include <utility>
kaleido::ast::Invocation::Invocation(std::string toInvoke, std::vector<std::shared_ptr<TreeNode>> args)
    : mToInvoke(std::move(toInvoke)), mArgs(std::move(args)) {

}
