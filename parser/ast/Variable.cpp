#include "Variable.h"
#include <utility>
kaleido::ast::Variable::Variable(std::string name) : mName(std::move(name)) {

}
kaleido::ast::Variable::Variable(const std::string &&name) : mName(name) {

}
const std::string &Variable::name() const {
    return mName;
}
