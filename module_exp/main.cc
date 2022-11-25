// main.cc
#include <cstdint>
#include <iostream>

import hello; // import declaration

auto main() -> std::int32_t {
    auto point = lib::point_t {5, 5};

    point.x() += 10;
    std::cout << "x: " << point.x() << std::endl;
    std::cout << "y: " << point.y() << std::endl;

    std::cout << "mag: " << point.magnitude() << std::endl;

    hello(42);
    return 0;
}
