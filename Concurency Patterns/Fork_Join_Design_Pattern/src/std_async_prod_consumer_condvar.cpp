/*

Detailed Explanation
Shared Resources:

data_queue: A queue to hold the produced data.
queue_mutex: A mutex to protect access to the queue.
data_cond: A condition variable to synchronize the producer and consumer.
Producer Function:

The producer generates data and pushes it into the queue.
After adding data to the queue, it notifies the consumer using data_cond.notify_one().
Consumer Function:

The consumer waits for data to be available in the queue using data_cond.wait().
Once data is available, it processes the data and removes it from the queue.
The consumer exits when it encounters a special value (-1 in this case).
Main Function:

The producer and consumer functions are launched asynchronously using std::async.
The main function waits for the producer to finish and then signals the consumer to exit by pushing a special value into the queue and notifying the consumer.
Key Points
Condition Variables: Used to block the consumer until data is available in the queue.
Mutex: Ensures that access to the shared queue is thread-safe.
Notification: The producer notifies the consumer when new data is available, and the main function notifies the consumer to exit.
This example demonstrates how to use condition variables with std::async to synchronize tasks and manage shared resources efficiently. Would you like to explore more advanced synchronization techniques or specific use cases?

*/


#include <iostream>
#include <queue>
#include <future>
#include <mutex>
#include <condition_variable>

// Shared resources
std::queue<int> data_queue;
std::mutex queue_mutex;
std::condition_variable data_cond;

// Producer function
void producer(int count)
{
    for (int i = 0; i < count; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
        std::lock_guard<std::mutex> lock(queue_mutex);
        data_queue.push(i);
        std::cout << "Produced: " << i << std::endl;
        data_cond.notify_one(); // Notify the consumer
    }
}

// Consumer function
void consumer(int id)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        data_cond.wait(lock, [] { return !data_queue.empty(); }); // Wait for data

        int data = data_queue.front();
        data_queue.pop();
        lock.unlock();

        std::cout << "Consumer " << id << " processed: " << data << std::endl;

        if (data == -1) break; // Exit condition
    }
}

int main()
{
    // Launch producer and consumer asynchronously
    auto producer_future = std::async(std::launch::async, producer, 10);
    auto consumer_future = std::async(std::launch::async, consumer, 1);

    // Wait for the producer to finish
    producer_future.get();

    // Signal the consumer to exit
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        data_queue.push(-1); // Special value to signal exit
        data_cond.notify_one();
    }

    // Wait for the consumer to finish
    consumer_future.get();

    return 0;

}
