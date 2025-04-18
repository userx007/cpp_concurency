#include <iostream>
#include <future>
#include <stdexcept>

int risky_compute(int x)
{
    if (x < 0) throw std::runtime_error("Negative input not allowed");
    return x * x;
}

int main()
{
    std::future<int> result = std::async(std::launch::async, risky_compute, -5);

    try {
        int value = result.get();
        std::cout << "Result: " << value << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
