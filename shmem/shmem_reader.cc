#include <sys/mman.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string_view>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

struct HelloBuffer
{
    std::int32_t value;
};

auto main() -> int
{
    std::cout << "hello, world!" << std::endl;

    auto fd = shm_open("hello.mem", O_RDWR, 0600);
    if (fd == -1)
    {
        std::cout << "failed to open shared memory file" << std::endl;
        return -1;
    }
    if (ftruncate(fd, sizeof(HelloBuffer)) == -1)
    {
        std::cout << "failed to truncate shared memory file" << std::endl;
    }

    auto *mem = static_cast<HelloBuffer *>(mmap(nullptr, sizeof(HelloBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    if (mem == MAP_FAILED)
    {
        std::cout << "failed to memory map file" << std::endl;
    }

    while (true)
    {
        std::this_thread::sleep_for(100ms);
        std::cout << "reader: " << mem->value << std::endl;
    }

    shm_unlink("hello.mem");

    return 0;
}