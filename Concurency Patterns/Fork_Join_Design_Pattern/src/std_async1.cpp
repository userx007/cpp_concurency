#include <iostream>
#include <future>
#include <thread>

// Function to be run asynchronously
int compute(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate a long computation
    return x * x;
}

int main()
{
    // Launch the function asynchronously
    std::future<int> result = std::async(std::launch::async, compute, 5);

    // Do other work while the function runs
    std::cout << "Doing other work...\n";

    // Get the result of the asynchronous function
    int value = result.get(); // This will block until the function completes

    std::cout << "Result: " << value << std::endl;
    return 0;
}
