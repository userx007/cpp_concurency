/*

Aan example that demonstrates the use of all the interfaces of std::thread in C++.
The std::thread class provides several methods for managing threads, including starting, joining, detaching, and checking thread status.

Example: Using All Interfaces of std::thread
This example will cover the following interfaces:

Constructor                         : Creating a thread.
join()                              : Waiting for a thread to complete.
detach()                            : Detaching a thread to run independently.
joinable()                          : Checking if a thread is joinable.
get_id()                            : Getting the thread's ID.
hardware_concurrency()              : Getting the number of concurrent threads supported by the hardware.
Move Constructor and Move Assignment: Moving thread objects.


Detailed Explanation

--------------------
Constructor:
--------------------
Threads are created using the std::thread constructor, which takes a function and its arguments.

--------------------
join():
--------------------
The join() method is used to wait for threads to complete. It blocks the calling thread until the thread represented by the std::thread object finishes execution.

--------------------
detach():
--------------------
The detach() method allows a thread to run independently. Once detached, the thread cannot be joined.

--------------------
joinable():
--------------------
The joinable() method checks if a thread is joinable (i.e., it has not been joined or detached).

--------------------
get_id():
--------------------
The get_id() method returns the ID of the thread. This can be useful for debugging and logging.


--------------------
hardware_concurrency():
--------------------
The hardware_concurrency() method returns the number of concurrent threads supported by the hardware. This can help in deciding the number of threads to create for optimal performance.

--------------------
Move Constructor and Move Assignment:
--------------------
Threads can be moved using the move constructor and move assignment operator. This is useful for transferring ownership of a thread.


--------------------
This example demonstrates the use of all the interfaces of std::thread to manage and coordinate threads in a C++ program.

*/

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

// Function to be executed by threads
void thread_function(int id)
{
    std::cout << "Thread " << id << " started.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    std::cout << "Thread " << id << " completed.\n";
}

int main()
{
    // 1. Constructor: Creating threads
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.emplace_back(thread_function, i);
    }

    // 2. join(): Waiting for threads to complete
    for (auto& t : threads)
    {
        if (t.joinable()) {
            t.join();
        }
    }

    // 3. detach(): Detaching a thread to run independently
    std::thread detached_thread([] {
        std::cout << "Detached thread started.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
        std::cout << "Detached thread completed.\n";
    });

    detached_thread.detach();

    // 4. joinable(): Checking if a thread is joinable
    std::thread joinable_thread([] {
        std::cout << "Joinable thread started.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
        std::cout << "Joinable thread completed.\n";
    });

    if (joinable_thread.joinable())
    {
        joinable_thread.join();
    }

    // 5. get_id(): Getting the thread's ID
    std::thread id_thread([] {
        std::cout << "Thread with ID " << std::this_thread::get_id() << " started.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
        std::cout << "Thread with ID " << std::this_thread::get_id() << " completed.\n";
    });
    std::cout << "ID of id_thread: " << id_thread.get_id() << std::endl;
    id_thread.join();

    // 6. hardware_concurrency(): Getting the number of concurrent threads supported by the hardware
    unsigned int num_threads = std::thread::hardware_concurrency();
    std::cout << "Number of concurrent threads supported by the hardware: " << num_threads << std::endl;

    // 7. Move Constructor and Move Assignment
    std::thread move_thread([] {
        std::cout << "Move thread started.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
        std::cout << "Move thread completed.\n";
    });
    std::thread moved_thread = std::move(move_thread); // Move constructor
    if (moved_thread.joinable()) {
        moved_thread.join();
    }

    return 0;
}
