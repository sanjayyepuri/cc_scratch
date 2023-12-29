#include <compare>
#include <ios>
#include <iostream>

struct Point {
  int x, y;

  // The main benefit is that it is really easy to define ordering now.
  auto operator<=>(const Point &other) const = default;
};

auto main() -> int {
  double x = 12;
  double y = 4;

  std::cout << std::boolalpha << (std::partial_ordering::less == (x <=> y))
            << std::endl;
  std::cout << std::boolalpha
            << (std::partial_ordering::equivalent == (x <=> y)) << std::endl;
  std::cout << std::boolalpha << (std::partial_ordering::greater == (x <=> y))
            << std::endl;

  auto p1 = Point{1, 2};
  auto p2 = Point{2, 3};

  std::cout << std::boolalpha << (p1 < p2) << std::endl;

  return 0;
}