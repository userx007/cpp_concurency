/*

5. Condition Variable (std::condition_variable)
A condition variable is used to block a thread until a specific condition is met.
It is typically used in conjunction with a mutex to synchronize access to shared data.

Use Case: When you need to block a thread until a specific condition is met.
Example: Producer-consumer scenarios where a consumer waits for data to be produced.
Considerations: Requires careful use with a mutex to avoid spurious wakeups and ensure thread safety.

*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex cv_mtx;
std::condition_variable cv;
bool ready = false;

void wait_for_ready()
{
    std::unique_lock<std::mutex> lock(cv_mtx);
    cv.wait(lock, [] { return ready; });
    std::cout << "Thread is ready\n";
}

void set_ready()
{
    std::lock_guard<std::mutex> lock(cv_mtx);
    ready = true;
    cv.notify_one();
}

int main() {
    std::thread t1(wait_for_ready);
    std::thread t2(set_ready);

    t1.join();
    t2.join();

    return 0;
}
