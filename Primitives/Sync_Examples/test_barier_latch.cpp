/*

Combining barriers with latches can help coordinate complex parallel tasks by synchronizing different stages and ensuring that all threads reach certain points before proceeding. Here's an example that demonstrates how to use both std::latch and std::barrier to manage multi-stage parallel tasks.

Example: Multi-Stage Task Coordination with Latches and Barriers
In this example, we'll use latches to synchronize the completion of each stage and barriers to ensure that all threads reach certain synchronization points within each stage.

Detailed Explanation

--------------------
Initialization:
--------------------

Three latches are initialized, each with a counter of 3, corresponding to the three tasks in each stage.
Three barriers are initialized, each with a count of 3 and a completion function that prints a message when all tasks reach the barrier.

--------------------
Stage 1 Tasks:
--------------------

Each task in stage 1 simulates work and then waits at the stage1_barrier using arrive_and_wait().
After all tasks reach the barrier, the latch's counter is decremented using count_down().

--------------------
Stage 2 Tasks:
--------------------

Each task in stage 2 waits for the stage1_latch to reach zero using wait(), ensuring that all stage 1 tasks have completed.
After stage 1 is complete, stage 2 tasks simulate work, wait at the stage2_barrier, and decrement the stage2_latch counter.

--------------------
Stage 3 Tasks:
--------------------

Each task in stage 3 waits for the stage2_latch to reach zero using wait(), ensuring that all stage 2 tasks have completed.
After stage 2 is complete, stage 3 tasks simulate work, wait at the stage3_barrier, and decrement the stage3_latch counter.

--------------------
Main Function:
--------------------

Tasks for all three stages are launched in separate threads.
All threads are joined to ensure they complete before the program exits.
A final message is printed indicating that all stages have completed.
This example demonstrates how to use both latches and barriers to coordinate multi-stage parallel tasks, ensuring synchronization points within each stage and overall stage completion.

*/


#include <iostream>
#include <thread>
#include <latch>
#include <barrier>
#include <vector>

// Initialize latches for three stages
std::latch stage1_latch(3);
std::latch stage2_latch(3);
std::latch stage3_latch(3);

// Initialize barriers for synchronization points within each stage
std::barrier stage1_barrier(3,  {
    std::cout << "All tasks in Stage 1 have reached the barrier.\n";
});

std::barrier stage2_barrier(3,  {
    std::cout << "All tasks in Stage 2 have reached the barrier.\n";
});

std::barrier stage3_barrier(3,  {
    std::cout << "All tasks in Stage 3 have reached the barrier.\n";
});

void stage1_task(int id)
{
    std::cout << "Stage 1 Task " << id << " started.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id)); // Simulate work
    stage1_barrier.arrive_and_wait(); // Wait at the barrier
    stage1_latch.count_down(); // Decrement the stage 1 latch
    std::cout << "Stage 1 Task " << id << " completed.\n";
}

void stage2_task(int id)
{
    stage1_latch.wait(); // Wait for stage 1 to complete

    std::cout << "Stage 2 Task " << id << " started.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id)); // Simulate work
    stage2_barrier.arrive_and_wait(); // Wait at the barrier
    stage2_latch.count_down(); // Decrement the stage 2 latch
    std::cout << "Stage 2 Task " << id << " completed.\n";
}

void stage3_task(int id)
{
    stage2_latch.wait(); // Wait for stage 2 to complete

    std::cout << "Stage 3 Task " << id << " started.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id)); // Simulate work
    stage3_barrier.arrive_and_wait(); // Wait at the barrier
    stage3_latch.count_down(); // Decrement the stage 3 latch
    std::cout << "Stage 3 Task " << id << " completed.\n";
}

int main()
{
    std::vector<std::thread> stage1_threads;
    std::vector<std::thread> stage2_threads;
    std::vector<std::thread> stage3_threads;

    // Launch stage 1 tasks
    for (int i = 1; i <= 3; ++i)
    {
        stage1_threads.emplace_back(stage1_task, i);
    }

    // Launch stage 2 tasks
    for (int i = 1; i <= 3; ++i)
    {
        stage2_threads.emplace_back(stage2_task, i);
    }

    // Launch stage 3 tasks
    for (int i = 1; i <= 3; ++i)
    {
        stage3_threads.emplace_back(stage3_task, i);
    }

    // Join all threads
    for (auto& t : stage1_threads)
    {
        t.join();
    }

    for (auto& t : stage2_threads)
    {
        t.join();
    }

    for (auto& t : stage3_threads)
    {
        t.join();
    }

    std::cout << "All stages completed.\n";

    return 0;
}
