#include "PointerUtils.h"
template<typename Derived, typename Base>
std::unique_ptr<Derived> kaleido::static_cast_unique_ptr(std::unique_ptr<Base> &&base_ptr) {
    auto derived = static_cast<Derived *>(base_ptr.release());
    return std::make_unique<Derived>(derived);
}
template<typename Derived, typename Base>
std::unique_ptr<Derived> kaleido::dynamic_cast_unique_ptr(std::unique_ptr<Base> &&base_ptr) {
    auto derived = dynamic_cast<Derived *>(base_ptr.get());
    if (derived != nullptr) {
        base_ptr.release();
        return std::make_unique<Derived>(derived);
    }
    return std::make_unique<Derived>(derived);
}
