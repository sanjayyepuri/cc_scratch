#include <cmath>
#include <concepts>
#include <iostream>

template <std::size_t V> struct Int {
  static constexpr std::size_t value = V;
};

template <typename T>
concept GreaterThanZero = T::value > 0;

template <typename T>
concept Hashable = requires(T a) {
  { std::hash<T>(a) } -> std::convertible_to<std::size_t>;
};

consteval auto divide(auto numerator, GreaterThanZero auto denominator)
    -> std::size_t {
  return decltype(numerator)::value / decltype(denominator)::value;
}

template <typename T>
concept HasFunction = requires(T a) {
  { a.function(0) } -> std::same_as<std::int32_t>;
};

template <typename T> class FunctionCallWrapper {
public:
  auto function_wrap(std::int32_t value) -> std::int32_t
    requires HasFunction<T>
  {
    return static_cast<T *>(this)->function(value);
  }
};

class Object : public FunctionCallWrapper<Object> {
public:
  auto function(std::int32_t value) -> std::int32_t { return value + 42; }
};

class BadObject : public FunctionCallWrapper<BadObject> {
public:
  auto function(double value) -> double { return std::floor(value) + 42; }
};

auto main() -> int {
  std::cout << divide(Int<0>{}, Int<1>{}) << std::endl;
  std::cout << divide(Int<10>{}, Int<2>{}) << std::endl;
  // std::cout << divide(Int<10>{}, Int<0>{}) << std::endl;

  auto obj = Object{};
  std::cout << obj.function_wrap(12) << std::endl;
  std::cout << obj.function(14) << std::endl;

  auto bad_obj = BadObject{};
  // std::cout << bad_obj.function_wrap(100) << std::endl;

  return 0;
}
