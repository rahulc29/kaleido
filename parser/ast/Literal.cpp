#include "Literal.h"
kaleido::ast::Literal::Literal(double value) : mValue(value) {

}
const double &kaleido::ast::Literal::value() const {
    return mValue;
}
