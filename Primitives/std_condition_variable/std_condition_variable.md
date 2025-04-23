Condition variables in C++ are synchronization primitives used to block a thread until a particular condition is met. They are typically used in conjunction with mutexes to manage access to shared resources and ensure thread safety.

Here's a brief overview of how condition variables work:

1. **Initialization**: You create a condition variable using `std::condition_variable`.
2. **Waiting**: A thread can wait for a condition variable using `wait()` or `wait_for()`. This will block the thread until the condition is met.
3. **Notification**: Another thread can notify waiting threads using `notify_one()` or `notify_all()`. This signals that the condition has been met and allows waiting threads to proceed.

Here's a simple example to illustrate:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });
    std::cout << "Thread " << id << '\n';
}

void set_ready() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();
}

int main() {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(print_id, i);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    set_ready();

    for (auto& th : threads) th.join();
}
```

In this example, the `print_id` function waits for the `ready` condition to be true before printing the thread ID. The `set_ready` function sets the `ready` condition to true and notifies all waiting threads.

Sure! Let's explore a couple more examples to deepen your understanding of condition variables in C++.

### Example 1: Producer-Consumer Problem

In this classic synchronization problem, we have a producer thread that generates data and a consumer thread that processes it. Condition variables help coordinate the producer and consumer.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> dataQueue;
bool done = false;

void producer() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        dataQueue.push(i);
        cv.notify_one();  // Notify the consumer
    }
    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    cv.notify_one();  // Notify the consumer that production is done
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !dataQueue.empty() || done; });
        while (!dataQueue.empty()) {
            int data = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << data << '\n';
        }
        if (done) break;
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();
}
```

In this example, the producer thread generates data and pushes it into a queue. The consumer thread waits for data to be available in the queue or for the production to be done. The condition variable `cv` is used to notify the consumer when new data is available or when production is complete.

### Example 2: Thread Pool

A thread pool is a collection of worker threads that process tasks from a queue. Condition variables can be used to manage the task queue and notify worker threads when new tasks are available.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    void enqueueTask(std::function<void()> task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop;

    void workerThread();
};

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back(&ThreadPool::workerThread, this);
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();
    for (std::thread &worker : workers) {
        worker.join();
    }
}

void ThreadPool::enqueueTask(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.push(task);
    }
    cv.notify_one();
}

void ThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]{ return !tasks.empty() || stop; });
            if (stop && tasks.empty()) return;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}

int main() {
    ThreadPool pool(4);

    for (int i = 0; i < 10; ++i) {
        pool.enqueueTask([i] {
            std::cout << "Task " << i << " is being processed\n";
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
}
```

In this example, the `ThreadPool` class manages a pool of worker threads that process tasks from a queue. The `enqueueTask` method adds a new task to the queue and notifies a worker thread using the condition variable `cv`. The worker threads wait for tasks to be available and process them as they are added to the queue.

These examples demonstrate how condition variables can be used to synchronize threads and manage shared resources effectively.

Let's break down the differences between `notify_one` and `notify_all`, and then discuss some common pitfalls with condition variables.

### `notify_one` vs `notify_all`

#### `notify_one`
- **Purpose**: Wakes up one of the threads that are waiting on the condition variable.
- **Use Case**: When you only need one thread to proceed, such as when a single resource becomes available.
- **Efficiency**: More efficient in scenarios where only one thread needs to be woken up, as it avoids the overhead of waking up multiple threads.

#### `notify_all`
- **Purpose**: Wakes up all the threads that are waiting on the condition variable.
- **Use Case**: When multiple threads need to be notified, such as when a significant state change occurs that all waiting threads should be aware of.
- **Efficiency**: Less efficient if only one thread can proceed, as it wakes up all waiting threads, which then compete for the resource and may go back to sleep.

### Common Pitfalls with Condition Variables

1. **Spurious Wakeups**:
   - **Issue**: Condition variables can experience spurious wakeups, where a thread wakes up without being notified.
   - **Solution**: Always use a loop to recheck the condition after waking up.
   ```cpp
   cv.wait(lock, []{ return condition; });
   ```

2. **Lost Wakeups**:
   - **Issue**: If a thread calls `notify_one` or `notify_all` before another thread starts waiting, the notification can be lost.
   - **Solution**: Ensure the condition variable is used in conjunction with a mutex and that the condition is checked within the mutex-protected block.

3. **Deadlocks**:
   - **Issue**: Improper use of mutexes and condition variables can lead to deadlocks.
   - **Solution**: Always acquire the mutex before waiting on the condition variable and release it as soon as possible after the condition is met.

4. **Resource Starvation**:
   - **Issue**: Using `notify_one` can lead to resource starvation if the same thread is always woken up.
   - **Solution**: Use `notify_all` in scenarios where fairness is important, or implement additional logic to ensure fair access.

5. **Incorrect Predicate**:
   - **Issue**: Using an incorrect or incomplete predicate can cause threads to wake up prematurely or not at all.
   - **Solution**: Ensure the predicate accurately reflects the condition that should be met for the thread to proceed.

### Example of Handling Spurious Wakeups

Here's an example that demonstrates how to handle spurious wakeups correctly:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });
    std::cout << "Worker thread proceeding\n";
}

void set_ready() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();
}

int main() {
    std::thread t(worker);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    set_ready();

    t.join();
}
```

In this example, the `worker` function uses a lambda predicate to check the `ready` condition, ensuring it handles spurious wakeups correctly.

Let's go through the methods of the `std::condition_variable` class in C++ and provide examples for each.

### Methods of `std::condition_variable`

1. **`wait`**
   - **Purpose**: Blocks the current thread until the condition variable is notified and the predicate returns true.
   - **Example**:
     ```cpp
     std::mutex mtx;
     std::condition_variable cv;
     bool ready = false;

     void worker() {
         std::unique_lock<std::mutex> lock(mtx);
         cv.wait(lock, []{ return ready; });
         std::cout << "Worker thread proceeding\n";
     }

     void set_ready() {
         std::unique_lock<std::mutex> lock(mtx);
         ready = true;
         cv.notify_all();
     }

     int main() {
         std::thread t(worker);
         std::this_thread::sleep_for(std::chrono::seconds(1));
         set_ready();
         t.join();
     }
     ```

2. **`wait_for`**
   - **Purpose**: Blocks the current thread until the condition variable is notified, the predicate returns true, or the specified timeout duration has elapsed.
   - **Example**:
     ```cpp
     std::mutex mtx;
     std::condition_variable cv;
     bool ready = false;

     void worker() {
         std::unique_lock<std::mutex> lock(mtx);
         if (cv.wait_for(lock, std::chrono::seconds(2), []{ return ready; })) {
             std::cout << "Worker thread proceeding\n";
         } else {
             std::cout << "Timeout occurred\n";
         }
     }

     void set_ready() {
         std::unique_lock<std::mutex> lock(mtx);
         ready = true;
         cv.notify_all();
     }

     int main() {
         std::thread t(worker);
         std::this_thread::sleep_for(std::chrono::seconds(1));
         set_ready();
         t.join();
     }
     ```

3. **`wait_until`**
   - **Purpose**: Blocks the current thread until the condition variable is notified, the predicate returns true, or the specified time point is reached.
   - **Example**:
     ```cpp
     std::mutex mtx;
     std::condition_variable cv;
     bool ready = false;

     void worker() {
         std::unique_lock<std::mutex> lock(mtx);
         auto timeout = std::chrono::system_clock::now() + std::chrono::seconds(2);
         if (cv.wait_until(lock, timeout, []{ return ready; })) {
             std::cout << "Worker thread proceeding\n";
         } else {
             std::cout << "Timeout occurred\n";
         }
     }

     void set_ready() {
         std::unique_lock<std::mutex> lock(mtx);
         ready = true;
         cv.notify_all();
     }

     int main() {
         std::thread t(worker);
         std::this_thread::sleep_for(std::chrono::seconds(1));
         set_ready();
         t.join();
     }
     ```

4. **`notify_one`**
   - **Purpose**: Wakes up one of the threads that are waiting on the condition variable.
   - **Example**:
     ```cpp
     std::mutex mtx;
     std::condition_variable cv;
     bool ready = false;

     void worker() {
         std::unique_lock<std::mutex> lock(mtx);
         cv.wait(lock, []{ return ready; });
         std::cout << "Worker thread proceeding\n";
     }

     void set_ready() {
         std::unique_lock<std::mutex> lock(mtx);
         ready = true;
         cv.notify_one();
     }

     int main() {
         std::thread t(worker);
         std::this_thread::sleep_for(std::chrono::seconds(1));
         set_ready();
         t.join();
     }
     ```

5. **`notify_all`**
   - **Purpose**: Wakes up all the threads that are waiting on the condition variable.
   - **Example**:
     ```cpp
     std::mutex mtx;
     std::condition_variable cv;
     bool ready = false;

     void worker() {
         std::unique_lock<std::mutex> lock(mtx);
         cv.wait(lock, []{ return ready; });
         std::cout << "Worker thread proceeding\n";
     }

     void set_ready() {
         std::unique_lock<std::mutex> lock(mtx);
         ready = true;
         cv.notify_all();
     }

     int main() {
         std::thread t(worker);
         std::this_thread::sleep_for(std::chrono::seconds(1));
         set_ready();
         t.join();
     }
     ```

These examples cover the primary methods of the `std::condition_variable` class. Each method plays a crucial role in synchronizing threads and managing shared resources effectively.

Let's dive into the parameters for the methods of `std::condition_variable` that take parameters.

### `wait`

```cpp
template< class Predicate >
void wait( std::unique_lock<std::mutex>& lock, Predicate pred );
```

- **Parameters**:
  - `lock`: A `std::unique_lock<std::mutex>` that must be locked by the calling thread. This lock is released while the thread is waiting and reacquired when the thread is awakened.
  - `pred`: A predicate (a callable object returning `bool`) that is repeatedly checked. The thread will continue to wait until `pred` returns `true`.

- **Example**:
  ```cpp
  std::mutex mtx;
  std::condition_variable cv;
  bool ready = false;

  void worker() {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, []{ return ready; });
      std::cout << "Worker thread proceeding\n";
  }

  void set_ready() {
      std::unique_lock<std::mutex> lock(mtx);
      ready = true;
      cv.notify_all();
  }

  int main() {
      std::thread t(worker);
      std::this_thread::sleep_for(std::chrono::seconds(1));
      set_ready();
      t.join();
  }
  ```

### `wait_for`

```cpp
template< class Rep, class Period, class Predicate >
bool wait_for( std::unique_lock<std::mutex>& lock,
               const std::chrono::duration<Rep,Period>& rel_time,
               Predicate pred );
```

- **Parameters**:
  - `lock`: A `std::unique_lock<std::mutex>` that must be locked by the calling thread.
  - `rel_time`: A `std::chrono::duration` object representing the maximum time to wait.
  - `pred`: A predicate that is repeatedly checked. The thread will continue to wait until `pred` returns `true` or the timeout duration has elapsed.

- **Returns**: `true` if the predicate returned `true`, `false` if the timeout occurred.

- **Example**:
  ```cpp
  std::mutex mtx;
  std::condition_variable cv;
  bool ready = false;

  void worker() {
      std::unique_lock<std::mutex> lock(mtx);
      if (cv.wait_for(lock, std::chrono::seconds(2), []{ return ready; })) {
          std::cout << "Worker thread proceeding\n";
      } else {
          std::cout << "Timeout occurred\n";
      }
  }

  void set_ready() {
      std::unique_lock<std::mutex> lock(mtx);
      ready = true;
      cv.notify_all();
  }

  int main() {
      std::thread t(worker);
      std::this_thread::sleep_for(std::chrono::seconds(1));
      set_ready();
      t.join();
  }
  ```

### `wait_until`

```cpp
template< class Clock, class Duration, class Predicate >
bool wait_until( std::unique_lock<std::mutex>& lock,
                 const std::chrono::time_point<Clock,Duration>& timeout_time,
                 Predicate pred );
```

- **Parameters**:
  - `lock`: A `std::unique_lock<std::mutex>` that must be locked by the calling thread.
  - `timeout_time`: A `std::chrono::time_point` object representing the time point to wait until.
  - `pred`: A predicate that is repeatedly checked. The thread will continue to wait until `pred` returns `true` or the specified time point is reached.

- **Returns**: `true` if the predicate returned `true`, `false` if the timeout occurred.

- **Example**:
  ```cpp
  std::mutex mtx;
  std::condition_variable cv;
  bool ready = false;

  void worker() {
      std::unique_lock<std::mutex> lock(mtx);
      auto timeout = std::chrono::system_clock::now() + std::chrono::seconds(2);
      if (cv.wait_until(lock, timeout, []{ return ready; })) {
          std::cout << "Worker thread proceeding\n";
      } else {
          std::cout << "Timeout occurred\n";
      }
  }

  void set_ready() {
      std::unique_lock<std::mutex> lock(mtx);
      ready = true;
      cv.notify_all();
  }

  int main() {
      std::thread t(worker);
      std::this_thread::sleep_for(std::chrono::seconds(1));
      set_ready();
      t.join();
  }
  ```

These methods allow you to wait for a condition with a timeout or until a specific time point, providing more control over thread synchronization.

### Return Values of Condition Variable Methods

#### `wait`
- **Return Value**: This method does not return a value directly. It simply blocks the thread until the condition is met and the predicate returns `true`.

#### `wait_for`
- **Return Value**: `bool`
  - `true`: The predicate returned `true` before the timeout duration elapsed.
  - `false`: The timeout duration elapsed before the predicate returned `true`.

#### `wait_until`
- **Return Value**: `bool`
  - `true`: The predicate returned `true` before the specified time point was reached.
  - `false`: The specified time point was reached before the predicate returned `true`.

### What Happens if `notify` is Called Before `wait`?

If `notify_one` or `notify_all` is called before a thread starts waiting on the condition variable, the notification can be lost. This means that the waiting thread might not be awakened as intended. To avoid this issue, it's crucial to ensure that the condition variable is used correctly in conjunction with a mutex and that the condition is checked within a mutex-protected block.

Here's an example to illustrate this:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });
    std::cout << "Worker thread proceeding\n";
}

void set_ready() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();
}

int main() {
    std::thread t(worker);

    // Simulate some work before setting the condition
    std::this_thread::sleep_for(std::chrono::seconds(1));
    set_ready();

    t.join();
}
```

In this example, the `set_ready` function sets the `ready` condition and calls `notify_all` after the worker thread has started waiting. This ensures that the notification is not lost.

To handle scenarios where `notify` might be called before `wait`, you can use a loop to check the condition:

```cpp
void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    while (!ready) {
        cv.wait(lock);
    }
    std::cout << "Worker thread proceeding\n";
}
```

This way, even if `notify` is called before `wait`, the thread will still check the condition and proceed correctly.

### Avoiding Deadlocks with Condition Variables

Deadlocks can occur when multiple threads are waiting for each other to release resources, leading to a situation where none of the threads can proceed. Here are some strategies to avoid deadlocks when using condition variables:

1. **Acquire Locks in a Consistent Order**:
   - Ensure that all threads acquire locks in the same order. This prevents circular wait conditions, which are a common cause of deadlocks.

2. **Use Timed Waits**:
   - Use `wait_for` or `wait_until` with a timeout to avoid indefinite waiting. This allows threads to periodically check for deadlock conditions and take corrective actions.

3. **Minimize Lock Holding Time**:
   - Hold locks for the shortest duration possible. Release locks as soon as the critical section is completed to reduce contention and the likelihood of deadlocks.

4. **Avoid Nested Locks**:
   - Avoid acquiring multiple locks simultaneously. If nested locks are necessary, ensure they are acquired in a consistent order.

5. **Check for Deadlock Conditions**:
   - Implement logic to detect and handle deadlock conditions. For example, if a thread has been waiting for too long, it can release its locks and retry.

### Role of Mutex in Condition Variables

A mutex (short for "mutual exclusion") is a synchronization primitive used to protect shared resources from concurrent access by multiple threads. In the context of condition variables, the mutex plays a crucial role in ensuring thread safety and preventing race conditions.

#### Key Roles of Mutex:

1. **Protect Shared Data**:
   - The mutex ensures that only one thread can access the shared data at a time. This prevents data corruption and ensures consistency.

2. **Coordinate with Condition Variables**:
   - The mutex is used in conjunction with condition variables to manage access to shared resources. When a thread waits on a condition variable, it releases the mutex, allowing other threads to modify the shared data.

3. **Prevent Race Conditions**:
   - By locking the mutex before accessing shared data, threads can prevent race conditions, where multiple threads attempt to read or write shared data simultaneously.

#### Example:

Here's an example that demonstrates the role of mutex in condition variables:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });
    std::cout << "Worker thread proceeding\n";
}

void set_ready() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();
}

int main() {
    std::thread t(worker);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    set_ready();

    t.join();
}
```

In this example:
- The `worker` function acquires the mutex using `std::unique_lock<std::mutex> lock(mtx)` before waiting on the condition variable.
- The `cv.wait(lock, []{ return ready; })` call releases the mutex while the thread is waiting and reacquires it when the thread is awakened.
- The `set_ready` function also acquires the mutex before modifying the shared `ready` variable and notifying the condition variable.

By using the mutex, we ensure that the shared `ready` variable is accessed safely and consistently by both the `worker` and `set_ready` functions.

