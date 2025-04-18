/*

2. Recursive Mutex (std::recursive_mutex)
A recursive mutex allows the same thread to lock the mutex multiple times without causing a deadlock. 
This is useful in scenarios where a function that holds a lock calls another function that also tries to acquire the same lock.

Use Case: When the same thread needs to acquire the same mutex multiple times (e.g., in recursive functions).
Example: Recursive functions that need to lock the same resource.
Considerations: Slightly more overhead than std::mutex.

*/

#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rec_mtx;

void recursive_function(int count)
{
    if (count <= 0)
    {
        return;
    }

    std::lock_guard<std::recursive_mutex> lock(rec_mtx);
    std::cout << "Count: " << count << std::endl;

    recursive_function(count - 1);
}

int main()
{
    std::thread t(recursive_function, 5);

    t.join();

    return 0;
}
