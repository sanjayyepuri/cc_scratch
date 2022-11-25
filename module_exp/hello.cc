module;
#include <string>
#include <iostream>
#include <cstdint>
#include <cmath>

export module hello;

auto magnitude_(std::int32_t x, std::int32_t y) -> std::int32_t {
    return x*x + y*y;
}

export auto hello(std::int32_t value) -> std::int32_t {
    std::cout << value << std::endl;
    return value;
}

export namespace lib {

class point_t {
public:
    point_t(std::int32_t x, std::int32_t y): x_(x), y_(y) {}

    auto magnitude() -> std::int32_t {
        return magnitude_(x_, y_);
    }

    auto x() -> std::int32_t& {
        return x_;
    }

    auto y() -> std::int32_t& {
        return y_;
    }

private:
    std::int32_t x_;
    std::int32_t y_;
};

} // namespace lib
