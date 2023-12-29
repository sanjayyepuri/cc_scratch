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


// Attempting to constrain the template parameter T to ensure that the type has the
// required function. However, concepts do not work here. If FunctionCallWrapper is
// used as a CRTP the type T is not completely defined at the time the concept is
// evaluated.
//
// ```
// concepts/concepts.cc:51:23: error: constraints not satisfied for class template 'FunctionCallWrapper' [with T = Object]
// class Object : public FunctionCallWrapper<Object> {
//                       ^~~~~~~~~~~~~~~~~~~~~~~~~~~
// concepts/concepts.cc:42:11: note: because 'Object' does not satisfy 'HasFunction'
// template <HasFunction T> class FunctionCallWrapper {
//           ^
// concepts/concepts.cc:24:6: note: because 'a.function(0)' would be invalid: member access into incomplete type 'Object'
//   { a.function(0) } -> std::same_as<std::int32_t>;
//      ^
// concepts/concepts.cc:56:26: error: constraints not satisfied for class template 'FunctionCallWrapper' [with T = BadObject]
// class BadObject : public FunctionCallWrapper<BadObject> {
//                          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// concepts/concepts.cc:42:11: note: because 'BadObject' does not satisfy 'HasFunction'
// template <HasFunction T> class FunctionCallWrapper {
//           ^
// concepts/concepts.cc:24:6: note: because 'a.function(0)' would be invalid: member access into incomplete type 'BadObject'
//   { a.function(0) } -> std::same_as<std::int32_t>;
// ```
//
// This is user error.
template <HasFunction T> class FunctionCallWrapper {
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

  // concepts/concepts.cc:71:24: error: invalid reference to function 'function_wrap': constraints not satisfied
  //   std::cout << bad_obj.function_wrap(100) << std::endl;
  //                        ^
  // concepts/concepts.cc:45:14: note: because 'BadObject' does not satisfy 'HasFunction'
  //     requires HasFunction<T>
  //              ^
  // concepts/concepts.cc:24:24: note: because type constraint 'std::same_as<double, std::int32_t>' was not satisfied:
  //   { a.function(0) } -> std::same_as<std::int32_t>;
  //                        ^
  //
  // std::cout << bad_obj.function_wrap(100) << std::endl;

  return 0;
}
