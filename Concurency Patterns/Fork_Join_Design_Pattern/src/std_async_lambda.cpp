#include <iostream>
#include <future>

int main()
{
    // Lambda function to compute the square of a number
    auto compute_square =  {
        return x * x;
    };

    // Launch the lambda function asynchronously
    std::future<int> result = std::async(std::launch::async, compute_square, 5);

    // Do other work while the lambda function runs
    std::cout << "Doing other work...\n";

    // Get the result of the lambda function
    int value = result.get(); // This will block until the function completes

    std::cout << "Result: " << value << std::endl;

    return 0;
}
