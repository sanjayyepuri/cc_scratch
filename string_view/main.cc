#include <string_view>
#include <string>
#include <iostream>

struct string_tester {
    //const
    const char* const_pointer;
    std::string_view sv;

    // mutable
    std::string string;
    char* pointer;
};

auto main() -> int {
    constexpr auto my_sv = std::string_view{"hello, world!"};
    auto tester = string_tester{};

    tester.const_pointer = my_sv.data();
    tester.sv = my_sv;
    tester.string = my_sv;
    // tester.pointer = my_sv.data();

    std::printf("%p, %p, %p\n", tester.string.c_str(), my_sv.data(), tester.const_pointer);

    return 0;
}