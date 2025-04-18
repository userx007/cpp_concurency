/*
Example that demonstrates the use of all the methods of std::latch in C++20. The methods we'll cover are:

count_down():       Decrements the latch's counter.
wait():             Blocks the calling thread until the latch's counter reaches zero.
arrive_and_wait():  Decrements the latch's counter and then waits until the counter reaches zero.
is_ready():         Checks if the latch's counter has reached zero.

Example: Coordinating Multiple Tasks
In this example, we'll create a scenario where multiple tasks need to be coordinated using a latch. We'll use all the methods of std::latch to manage the synchronization.


Detailed Explanation


--------------------
Initialization:
--------------------
The latch is initialized with a counter of 3, meaning it will require three count_down() calls to reach zero.


--------------------
Task Function:
--------------------
Each task simulates some work by sleeping for a duration.
The task then calls count_down() to decrement the latch's counter.
After decrementing the counter, the task calls wait() to block until the latch's counter reaches zero.


--------------------
Final Task:
--------------------
The final task uses arrive_and_wait() to decrement the latch's counter and wait until the counter reaches zero.


--------------------
Main Function:
--------------------
Multiple tasks are launched in separate threads.
The final task is also launched in a separate thread.
All threads are joined to ensure they complete before the program exits.
After all tasks are completed, is_ready() is used to check if the latch's counter has reached zero.
This example demonstrates how to use all the methods of std::latch to coordinate multiple tasks and ensure they proceed only when all tasks have reached a certain point.

*/

#include <iostream>
#include <thread>
#include <latch>
#include <vector>

// Initialize a latch with a counter of 3
std::latch latch(3);

void task(int id)
{
    std::cout << "Task " << id << " started.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id)); // Simulate work

    // Use count_down() to decrement the latch's counter
    latch.count_down();
    std::cout << "Task " << id << " completed and decremented the latch.\n";

    // Use wait() to block until the latch's counter reaches zero
    latch.wait();
    std::cout << "Task " << id << " proceeding after latch is ready.\n";

}


void final_task()
{
    // Use arrive_and_wait() to decrement the latch's counter and wait
    latch.arrive_and_wait();
    std::cout << "Final task proceeding after all tasks are ready.\n";

}

int main()
{
    std::vector<std::thread> threads;

    // Launch multiple tasks
    for (int i = 1; i <= 3; ++i)
    {
        threads.emplace_back(task, i);
    }

    // Launch the final task
    std::thread final(final_task);

    // Join all threads
    for (auto& t : threads)
    {
        t.join();
    }
    final.join();

    // Check if the latch is ready
    if (latch.is_ready())
    {
        std::cout << "All tasks have completed, and the latch is ready.\n";
    }
    else
    {
        std::cout << "Latch is not ready yet.\n";
    }

    return 0;

}
