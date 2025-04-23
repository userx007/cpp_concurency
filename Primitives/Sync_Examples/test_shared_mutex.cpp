/*

4. Shared Mutex (std::shared_mutex)

A shared mutex allows multiple threads to read shared data simultaneously while ensuring exclusive access for writing. 
This is useful for scenarios where read operations are frequent and write operations are rare.

Use Case: When multiple threads need to read shared data simultaneously, but only one thread should write.
Example: Read-heavy scenarios with occasional writes, like caching mechanisms.
Considerations: Allows multiple readers but only one writer, improving performance for read-heavy workloads.

*/

#include <iostream>
#include <thread>
#include <shared_mutex>

std::shared_mutex shared_mtx;
int shared_data = 0;

void reader()
{
    std::shared_lock<std::shared_mutex> lock(shared_mtx);
    std::cout << "Read data: " << shared_data << std::endl;
}

void writer()
{
    std::unique_lock<std::shared_mutex> lock(shared_mtx);
    shared_data++;
    std::cout << "Wrote data: " << shared_data << std::endl;
}

int main()
{
    std::thread t1(reader);
    std::thread t2(writer);
    std::thread t3(reader);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
