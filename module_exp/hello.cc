module;
#include <string>
#include <iostream>
#include <cstdint>

export module hello;

export auto hello(std::int32_t value) -> std::int32_t {
    std::cout << value << std::endl;
    return value;
}
