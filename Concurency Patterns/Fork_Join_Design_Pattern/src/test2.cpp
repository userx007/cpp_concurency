#include <iostream>
#include <vector>
#include <future>

// Function to compute the sum of elements in a range
int parallel_sum(const std::vector<int>& arr, int start, int end)
{
    // Base case: if the range is small, compute directly
    if (end - start < 1000)
    {
        int sum = 0;
        for (int i = start; i < end; ++i)
        {
            sum += arr[i];
        }
        return sum;
    }

    // Recursive case: split the range and compute in parallel
    int mid = start + (end - start) / 2;
    auto left_future = std::async(std::launch::async, parallel_sum, std::ref(arr), start, mid);
    auto right_future = std::async(std::launch::async, parallel_sum, std::ref(arr), mid, end);

    // Join: wait for both halves to complete and combine results
    return left_future.get() + right_future.get();
}

int main()
{
    // Create a large array of integers
    std::vector<int> arr(10000, 1); // Array of 10000 elements, all initialized to 1

    // Compute the sum using parallel computation
    int total_sum = parallel_sum(arr, 0, arr.size());

    std::cout << "Total sum: " << total_sum << std::endl;

    return 0;
}
