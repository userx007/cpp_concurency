#include <iostream>
#include <thread>
#include <vector>

// Function to be executed by each thread
void task(int id)
{
    std::cout << "Task " << id << " is running.\n";
}

int main()
{
    const int numTasks = 4;
    std::vector<std::thread> threads;

    // Fork: Create threads
    for (int i = 0; i < numTasks; ++i)
    {
        threads.emplace_back(task, i);
    }

    // Join: Wait for all threads to complete
    for (auto& t : threads)
    {
        t.join();
    }

    std::cout << "All tasks completed.\n";

    return 0;
}
