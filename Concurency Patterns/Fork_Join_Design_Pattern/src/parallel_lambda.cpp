#include <iostream>
#include <vector>
#include <future>

int main()
{
    // Create a large array of integers
    std::vector<int> arr(10000, 1); // Array of 10000 elements, all initialized to 1

    // Lambda function to compute the sum of elements in a range
    auto parallel_sum = &arr -> int
    {
        if (end - start < 1000) {
            int sum = 0;
            for (int i = start; i < end; ++i)
             {
                sum += arr[i];
            }
            return sum;
        }

        int mid = start + (end - start) / 2;
        auto left_future = std::async(std::launch::async, parallel_sum, start, mid);
        auto right_future = std::async(std::launch::async, parallel_sum, mid, end);

        return left_future.get() + right_future.get();
    };

    // Compute the sum using parallel computation
    int total_sum = parallel_sum(0, arr.size());

    std::cout << "Total sum: " << total_sum << std::endl;

    return 0;
}
