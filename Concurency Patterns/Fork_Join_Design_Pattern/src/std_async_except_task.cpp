#include <iostream>
#include <future>
#include <stdexcept>

// Function that may throw an exception
int risky_compute(int x)
{
    if (x < 0) throw std::runtime_error("Negative input not allowed");

    return x * x;

}

int main()
{
    // Launch the function asynchronously
    std::future<int> result = std::async(std::launch::async, risky_compute, -5);

    try
    {
        // Get the result, which will rethrow the exception if one was thrown
        int value = result.get();
        std::cout << "Result: " << value << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
