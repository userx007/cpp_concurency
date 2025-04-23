/*

Latches (std::latch)

Latches and barriers are synchronization primitives introduced in C++20 to help coordinate the execution of multiple threads. They provide mechanisms for threads to wait until certain conditions are met, making it easier to manage complex parallel tasks.

Latches (std::latch)
A latch is a simple synchronization primitive that acts as a countdown mechanism.
It allows threads to wait until a specified number of operations have been completed. Once the counter reaches zero, all waiting threads are released.

Key Characteristics:

Single-use: Once the counter reaches zero, the latch cannot be reused.
Countdown: The counter is initialized to a specific value and decremented by threads until it reaches zero.
Blocking: Threads can block on the latch until the counter is zero.

In this example, the latch is initialized with a counter of 3. Each task decrements the counter and waits until all tasks have completed.
Latches: Single-use countdown mechanism for synchronizing threads.

*/

#include <iostream>
#include <thread>
#include <latch>

std::latch latch(3); // Initialize latch with a counter of 3

void task(int id)
{
    std::cout << "Task " << id << " started.\n";
    latch.count_down(); // Decrement the counter
    latch.wait(); // Wait until the counter is zero
    std::cout << "Task " << id << " completed.\n";
}

int main()
{
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;

}
