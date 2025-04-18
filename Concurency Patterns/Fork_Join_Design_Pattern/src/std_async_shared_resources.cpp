#include <iostream>
#include <vector>
#include <future>
#include <mutex>

// Shared resource
std::vector<int> shared_data;
std::mutex data_mutex;

// Function to modify the shared resource
void modify_shared_data(int id)
{
    std::lock_guard<std::mutex> lock(data_mutex); // Lock the mutex
    shared_data.push_back(id);
    std::cout << "Task " << id << " added data.\n";
}

int main()
{
    const int numTasks = 10;
    std::vector<std::future<void>> futures;

    // Launch tasks asynchronously
    for (int i = 0; i < numTasks; ++i)
    {
        futures.push_back(std::async(std::launch::async, modify_shared_data, i));
    }

    // Wait for all tasks to complete
    for (auto& f : futures) {
        f.get();
    }

    // Print the contents of the shared resource
    std::cout << "Shared data: ";
    for (int value : shared_data)
    {
        std::cout << value << " ";
    }

    std::cout << std::endl;

    return 0;

}
