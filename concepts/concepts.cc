#include <iostream>

namespace concepts {

template <std::size_t V>
struct Int {
    static constexpr std::size_t value = V;
};

template <typename T>
concept GreaterThanZero = T::value > 0;

template <typename Numerator_, GreaterThanZero Denominator_>
void divide() { }

} // namespace concepts

auto main() -> int {
    concepts::divide<concepts::Int<10>, concepts::Int<0>>();
    return 0;
}
