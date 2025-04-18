/*

Barriers (std::barrier)
A barrier is a reusable synchronization primitive that allows a group of threads to wait until all threads in the group have reached a certain point.
Once all threads have arrived, they are released simultaneously, and the barrier can be reused.

Key Characteristics:

Reusable: Unlike latches, barriers can be reused multiple times.
Thread Coordination: Blocks a group of threads until all threads have reached the barrier.
Completion Function: Optionally, a completion function can be executed when all threads reach the barrier.

In this example, the barrier is initialized with a count of 3 and a completion function that prints a message when all tasks reach the barrier. Each task waits at the barrier until all tasks have arrived.

Barriers: Reusable synchronization mechanism for coordinating a group of threads.

*/

#include <iostream>
#include <thread>
#include <barrier>

std::barrier barrier(3,  {
    std::cout << "All tasks have reached the barrier.\n";
});

void task(int id)
{
    std::cout << "Task " << id << " started.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id)); // Simulate work
    barrier.arrive_and_wait(); // Wait at the barrier
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
