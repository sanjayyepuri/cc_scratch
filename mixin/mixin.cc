#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace internal {
class refcount_t {
 public:
  auto release() -> void { count_--; }

  auto add_reference() -> void { count_++; }

  auto debug_count() -> std::size_t { return count_; }

 private:
  std::size_t count_ = 0;
};
}  // namespace internal

/// There is an unused template parameter here which enables prevents reference
/// counted types from being in the same inheritance hiearchyreference counted
// types from being in the same inheritance hiearchy.
template <typename T>
class refcount_t : private internal::refcount_t {
 public:
  using internal::refcount_t::add_reference;
  using internal::refcount_t::debug_count;
  using internal::refcount_t::release;
};

class point_t : public refcount_t<point_t> {
 public:
  point_t(int x, int y) : x_(x), y_(y) {}

 private:
  std::int32_t x_, y_;
};

auto main() -> int {
  auto pt = point_t{12, 24};
  pt.add_reference();
  pt.add_reference();
  pt.release();
  std::cout << pt.debug_count() << std::endl;
  return 0;
}