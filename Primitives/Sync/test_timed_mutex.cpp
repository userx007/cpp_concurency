/*

3. Timed Mutex (std::timed_mutex)

A timed mutex allows a thread to attempt to acquire a lock for a specified duration. 
If the lock is not acquired within the duration, the thread can take alternative actions.

Use Case: When you need to attempt to acquire a lock for a specific duration.
Example: Trying to acquire a lock with a timeout to avoid indefinite blocking.
Considerations: Useful for avoiding deadlocks and managing time-sensitive tasks.

*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex timed_mtx;

void try_lock_for_duration()
{
    if (timed_mtx.try_lock_for(std::chrono::seconds(1)))
    {
        std::cout << "Lock acquired\n";
        timed_mtx.unlock();
    }
    else
    {
        std::cout << "Failed to acquire lock\n";
    }
}

int main()
{
    std::thread t1(try_lock_for_duration);
    std::thread t2(try_lock_for_duration);

    t1.join();
    t2.join();

    return 0;
}
