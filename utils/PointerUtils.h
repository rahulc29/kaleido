#ifndef KALEIDO_UTILS_POINTERUTILS_H
#define KALEIDO_UTILS_POINTERUTILS_H
#include <memory>
namespace kaleido {
    template<typename Derived, typename Base>
    std::unique_ptr<Derived> static_cast_unique_ptr(std::unique_ptr<Base> &&base_ptr);
    template<typename Derived, typename Base>
    std::unique_ptr<Derived> dynamic_cast_unique_ptr(std::unique_ptr<Base> &&base_ptr);
}
#endif //KALEIDO_UTILS_POINTERUTILS_H
