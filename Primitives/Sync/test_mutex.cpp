/*

1. Mutex (std::mutex)
A mutex is used to protect shared data from being simultaneously accessed by multiple threads.
It provides exclusive ownership to a thread, ensuring that only one thread can access the protected resource at a time.

Use Case: When you need to protect shared data from being accessed by multiple threads simultaneously.
Example: Protecting a shared counter or a shared data structure.
Considerations: Simple and effective for mutual exclusion, but can lead to deadlocks if not used carefully.

*/

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void print_thread_id(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << id << std::endl;
}

int main() {
    std::thread t1(print_thread_id, 1);
    std::thread t2(print_thread_id, 2);

    t1.join();
    t2.join();

    return 0;
}
