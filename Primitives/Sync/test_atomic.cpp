/*

6. Atomic Operations (std::atomic)
Atomic operations provide a way to perform thread-safe operations on shared data without using locks. 
They are useful for simple operations like incrementing counters.

Use Case: For simple atomic operations on shared data without using locks.
Example: Incrementing a counter or setting a flag.
Considerations: Provides lock-free thread safety for simple operations, reducing overhead.

*/

#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> atomic_counter(0);

void increment_counter()
{
    atomic_counter++;
}

int main()
{
    std::thread t1(increment_counter);
    std::thread t2(increment_counter);

    t1.join();
    t2.join();

    std::cout << "Counter: " << atomic_counter << std::endl;
    return 0;
}
