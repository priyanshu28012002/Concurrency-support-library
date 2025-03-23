To get the thread ID for each of the three threads, you can use the `std::this_thread::get_id()` function in C++11 and later, which returns a `std::thread::id` representing the current thread's ID. You can display this ID to differentiate the threads.

Here’s an example using **`std::thread`** to get and print the thread IDs for three threads. I’ll also include **`pthread`** and **`std::jthread`** versions for comparison.

### Example with `std::thread` (C++11 and later)

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void worker(int id) {
    std::cout << "Thread " << id << " started with thread ID: " << std::this_thread::get_id() << "\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << id << " is working\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    }
    std::cout << "Thread " << id << " finished with thread ID: " << std::this_thread::get_id() << "\n";
}

int main() {
    std::thread t1(worker, 1);  // Thread 1
    std::thread t2(worker, 2);  // Thread 2
    std::thread t3(worker, 3);  // Thread 3

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
```

### Output:

```
Thread 1 started with thread ID: 140639502942976
Thread 2 started with thread ID: 140639494550272
Thread 3 started with thread ID: 140639486157568
Thread 1 is working
Thread 2 is working
Thread 3 is working
...
Thread 1 finished with thread ID: 140639502942976
Thread 2 finished with thread ID: 140639494550272
Thread 3 finished with thread ID: 140639486157568
```

### Key Points:
- The function `std::this_thread::get_id()` is used to get the **unique ID** for the current thread.
- The thread IDs printed above are **platform-dependent** and are generally unique for each thread within a process.

---

### Example with `pthread` (POSIX Threads)

If you’re using **`pthread`**, you can get the thread ID using the `pthread_self()` function.

```cpp
#include <pthread.h>
#include <iostream>
#include <unistd.h>

void* worker(void* arg) {
    pthread_t thread_id = pthread_self();  // Get the thread ID
    std::cout << "Thread " << *(int*)arg << " started with thread ID: " << thread_id << "\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << *(int*)arg << " is working\n";
        usleep(100000);  // Simulate work (100ms)
    }
    std::cout << "Thread " << *(int*)arg << " finished with thread ID: " << thread_id << "\n";
    return nullptr;
}

int main() {
    pthread_t t1, t2, t3;
    int id1 = 1, id2 = 2, id3 = 3;

    pthread_create(&t1, nullptr, worker, &id1);
    pthread_create(&t2, nullptr, worker, &id2);
    pthread_create(&t3, nullptr, worker, &id3);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);

    return 0;
}
```

### Output:

```
Thread 1 started with thread ID: 139772453430016
Thread 2 started with thread ID: 139772445037312
Thread 3 started with thread ID: 139772436644608
Thread 1 is working
Thread 2 is working
Thread 3 is working
...
Thread 1 finished with thread ID: 139772453430016
Thread 2 finished with thread ID: 139772445037312
Thread 3 finished with thread ID: 139772436644608
```

### Key Points:
- **`pthread_self()`** returns the thread ID for the calling thread.
- The thread ID is a `pthread_t`, which is typically a pointer or a unique identifier based on the system.

---

### Example with `std::jthread` (C++20)

In `std::jthread`, you can use `std::this_thread::get_id()` just like with `std::thread` to get the thread ID.

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void worker(int id) {
    std::cout << "Thread " << id << " started with thread ID: " << std::this_thread::get_id() << "\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << id << " is working\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    }
    std::cout << "Thread " << id << " finished with thread ID: " << std::this_thread::get_id() << "\n";
}

int main() {
    std::jthread t1(worker, 1);  // Thread 1
    std::jthread t2(worker, 2);  // Thread 2
    std::jthread t3(worker, 3);  // Thread 3

    // No need to manually join, as `std::jthread` will join automatically at the end of scope
    return 0;
}
```

### Output:

```
Thread 1 started with thread ID: 140639502942976
Thread 2 started with thread ID: 140639494550272
Thread 3 started with thread ID: 140639486157568
Thread 1 is working
Thread 2 is working
Thread 3 is working
...
Thread 1 finished with thread ID: 140639502942976
Thread 2 finished with thread ID: 140639494550272
Thread 3 finished with thread ID: 140639486157568
```

### Key Points:
- **`std::this_thread::get_id()`** works exactly the same way in `std::jthread` as in `std::thread`.
- **Automatic Joining:** `std::jthread` automatically joins the thread when it goes out of scope.

---

### Comparison of Thread ID Retrieval

| Feature               | `std::thread` (C++11)     | `pthread` (POSIX)            | `std::jthread` (C++20)        |
|-----------------------|---------------------------|------------------------------|------------------------------|
| **Function for Thread ID** | `std::this_thread::get_id()` | `pthread_self()`             | `std::this_thread::get_id()`  |
| **Thread ID Type**     | `std::thread::id`          | `pthread_t`                  | `std::thread::id`             |
| **Platform Dependency**| OS-dependent               | OS-dependent                 | OS-dependent                  |

### Conclusion:
- **`std::this_thread::get_id()`** is the standard function used in **`std::thread`** and **`std::jthread`** to retrieve the thread ID.
- **`pthread_self()`** is used in **`pthread`** (POSIX threads) to get the thread ID.
- Each of these functions returns a type that represents the thread ID, but the actual type and formatting of the ID are platform-specific.

In all three cases, thread IDs are used primarily for debugging or logging purposes and don’t directly influence thread behavior. The actual **thread scheduling** (priority, execution, etc.) is handled by the OS’s scheduler.

Sure! Here’s how you can use `std::this_thread::sleep_for()` and `std::this_thread::sleep_until()` with **`std::thread`**, **`std::jthread`**, and **`pthread`**.

### 1. **Using `std::thread` (C++11 and later)**

**`std::this_thread::sleep_for()`** and **`std::this_thread::sleep_until()`** are available in `std::thread`, so we can use both functions to pause the execution of a thread in the C++ Standard Library.

#### Example: `std::thread` with `sleep_for` and `sleep_until`

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void worker(int id) {
    std::cout << "Thread " << id << " started.\n";
    
    // Sleep for 2 seconds using sleep_for
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Thread " << id << " woke up after 2 seconds.\n";
    
    // Sleep until a specific time point (3 seconds from now)
    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(3);
    std::this_thread::sleep_until(end_time);
    std::cout << "Thread " << id << " woke up at the time point.\n";
}

int main() {
    std::thread t1(worker, 1);  // Thread 1
    std::thread t2(worker, 2);  // Thread 2

    t1.join();
    t2.join();

    return 0;
}
```

### Output:

```
Thread 1 started.
Thread 2 started.
Thread 1 woke up after 2 seconds.
Thread 1 woke up at the time point.
Thread 2 woke up after 2 seconds.
Thread 2 woke up at the time point.
```

### 2. **Using `std::jthread` (C++20)**

In `std::jthread`, you can use **`std::this_thread::sleep_for()`** and **`std::this_thread::sleep_until()`** just like `std::thread`. Additionally, `std::jthread` automatically joins the thread when it goes out of scope, which simplifies thread management.

#### Example: `std::jthread` with `sleep_for` and `sleep_until`

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void worker(int id) {
    std::cout << "Thread " << id << " started.\n";
    
    // Sleep for 2 seconds using sleep_for
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Thread " << id << " woke up after 2 seconds.\n";
    
    // Sleep until a specific time point (3 seconds from now)
    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(3);
    std::this_thread::sleep_until(end_time);
    std::cout << "Thread " << id << " woke up at the time point.\n";
}

int main() {
    std::jthread t1(worker, 1);  // Thread 1
    std::jthread t2(worker, 2);  // Thread 2

    // No need to manually join since std::jthread automatically joins on scope exit.
    return 0;
}
```

### Output:

```
Thread 1 started.
Thread 2 started.
Thread 1 woke up after 2 seconds.
Thread 1 woke up at the time point.
Thread 2 woke up after 2 seconds.
Thread 2 woke up at the time point.
```

### 3. **Using `pthread` (POSIX Threads)**

In **POSIX threads**, we don’t have the standard `std::this_thread::sleep_for()` or `std::this_thread::sleep_until()` functions. However, we can use **`usleep()`** or **`nanosleep()`** to sleep for a specified amount of time.

- **`usleep()`** sleeps for microseconds (1 second = 1,000,000 microseconds).
- **`nanosleep()`** gives more control with nanosecond precision (1 second = 1,000,000,000 nanoseconds).

#### Example: `pthread` with `usleep` and `nanosleep`

```cpp
#include <pthread.h>
#include <iostream>
#include <unistd.h>  // for usleep()
#include <ctime>     // for nanosleep()

void* worker(void* arg) {
    int id = *((int*)arg);
    std::cout << "Thread " << id << " started.\n";
    
    // Sleep for 2 seconds using usleep (microseconds)
    usleep(2000000);  // 2 seconds
    std::cout << "Thread " << id << " woke up after 2 seconds.\n";
    
    // Sleep until a specific time point using nanosleep
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);  // Get the current time
    ts.tv_sec += 3;  // Add 3 seconds to the current time
    nanosleep(&ts, nullptr);  // Sleep until the new time
    std::cout << "Thread " << id << " woke up at the time point.\n";
    
    return nullptr;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    pthread_create(&t1, nullptr, worker, &id1);
    pthread_create(&t2, nullptr, worker, &id2);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    return 0;
}
```

### Output:

```
Thread 1 started.
Thread 2 started.
Thread 1 woke up after 2 seconds.
Thread 2 woke up after 2 seconds.
Thread 1 woke up at the time point.
Thread 2 woke up at the time point.
```

### Key Differences and Explanation:
1. **`std::thread` and `std::jthread`** (C++ Standard Library):
    - You can use **`std::this_thread::sleep_for()`** and **`std::this_thread::sleep_until()`** directly with both `std::thread` and `std::jthread`.
    - `std::this_thread::sleep_for()` sleeps for a specific duration, and `std::this_thread::sleep_until()` sleeps until a given time point.

2. **`pthread`** (POSIX Threads):
    - **`usleep()`** is used for sleeping in microseconds, but it’s considered outdated and less accurate than other methods.
    - **`nanosleep()`** offers better precision and allows you to specify the sleep time using a `timespec` structure (with seconds and nanoseconds).
    - There’s no equivalent of **`std::this_thread::sleep_for()`** or **`std::this_thread::sleep_until()`** in POSIX threads. You typically use **`usleep()`** or **`nanosleep()`** for sleep functionality.

### Comparison Summary:

| Feature                          | `std::thread` (C++11)          | `std::jthread` (C++20)        | `pthread` (POSIX)             |
|----------------------------------|--------------------------------|-------------------------------|------------------------------|
| **Function for Sleep**           | `std::this_thread::sleep_for()`<br> `std::this_thread::sleep_until()` | `std::this_thread::sleep_for()`<br> `std::this_thread::sleep_until()` | `usleep()`<br> `nanosleep()` |
| **Sleep Duration Unit**          | Any unit from `<chrono>` (e.g., `seconds`, `milliseconds`) | Any unit from `<chrono>` (e.g., `seconds`, `milliseconds`) | Microseconds for `usleep()`<br> Nanoseconds for `nanosleep()` |
| **Sleep Resolution**             | High (platform dependent)      | High (platform dependent)      | Depends on system (typically microseconds or nanoseconds) |
| **Thread Management**            | Manual join (`t.join()`)        | Automatic join (no `join()` needed) | Manual join (`pthread_join()`) |
| **Precision**                    | High                           | High                          | High (especially with `nanosleep()`) |

In summary:
- **C++ Standard Library (`std::thread` and `std::jthread`)** provides a more modern and easy-to-use API with `std::this_thread::sleep_for()` and `std::this_thread::sleep_until()`, which makes working with sleep and timing very convenient.
- **POSIX Threads (`pthread`)** requires using `usleep()` or `nanosleep()`, which are less intuitive and platform-specific but give you more control over the duration and precision of the sleep.



### Thread Priority in `std::thread`, `pthread`, and `std::jthread`

Thread priority refers to how the operating system decides which thread gets access to the CPU at any given time. High-priority threads are typically executed before low-priority threads, but the specific behavior is determined by the underlying operating system and its scheduler.

Each of these thread libraries (`std::thread`, `pthread`, and `std::jthread`) handles thread priority differently, as they rely on the underlying operating system’s thread scheduling mechanisms.

Here’s a detailed look at how thread priority works in each of these:

---

## **1. `std::thread` (C++ Standard Library)**

### **Thread Priority in `std::thread`:**

- **C++ Standard Library (`std::thread`)** does not provide a direct mechanism for setting thread priority. The standard C++ library abstracts thread management in such a way that it delegates thread scheduling to the underlying operating system.
  
- **Operating System Dependency:**
  - The actual priority behavior is managed by the OS’s scheduler (e.g., Linux, Windows, macOS), and you don’t have explicit control over the priority of a thread when using `std::thread` alone.
  
  - **Thread Scheduling:** On most systems, threads created by `std::thread` run at the **default priority** of the thread scheduler, meaning there is no way to assign different priorities to threads directly via the `std::thread` API.

### **How to Handle Priority in `std::thread`:**
While `std::thread` does not expose direct control over thread priorities, you can manage priorities through platform-specific APIs.

- **Windows (using `SetThreadPriority`):** On Windows, you can adjust the priority of a thread after creating it using the `SetThreadPriority` API.
  
- **Linux (using `pthread_setschedparam`):** On Linux, you can use `pthread_setschedparam` to set the priority of a thread after it’s created.

#### **Example: Setting Priority in Linux (using `pthread_setschedparam`)**
```cpp
#include <iostream>
#include <thread>
#include <pthread.h>
#include <unistd.h>

void worker() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Working in thread\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simulate work
    }
}

int main() {
    std::thread t(worker);

    // Set thread priority on Linux
    pthread_t native_handle = t.native_handle();
    sched_param sch_params;
    sch_params.sched_priority = 10; // Priority value (on Linux)
    if (pthread_setschedparam(native_handle, SCHED_FIFO, &sch_params) != 0) {
        std::cerr << "Failed to set thread priority!" << std::endl;
    }

    t.join();
    return 0;
}
```

### **Summary:**
- **`std::thread`** provides no direct priority control, but you can adjust priority through OS-specific extensions or APIs (e.g., `SetThreadPriority` on Windows or `pthread_setschedparam` on Linux).
- The priority of threads created with `std::thread` depends entirely on the OS’s scheduling policy.

---

## **2. `pthread` (POSIX Threads)**

### **Thread Priority in `pthread`:**

- **Direct Control:** The **POSIX threads library (`pthread`)** provides more direct control over thread priorities than `std::thread`. You can control the priority of threads by specifying the scheduling policy and priority parameters when creating or modifying a thread.

- **Thread Scheduling Policies:**
  - POSIX threads support several **scheduling policies**, such as:
    - `SCHED_FIFO`: First-in, first-out scheduling (real-time scheduling).
    - `SCHED_RR`: Round-robin scheduling (real-time scheduling).
    - `SCHED_OTHER`: Default, time-sharing scheduling policy (non-real-time).

  - **Priority Levels:** Under real-time policies (like `SCHED_FIFO` and `SCHED_RR`), thread priorities are specified as integer values (higher values denote higher priority). In the case of `SCHED_OTHER`, the priority might be less obvious, as the system scheduler handles time-sharing automatically.

### **How to Set Thread Priority in `pthread`:**
You can set thread priority using `pthread_setschedparam`, which allows you to specify the **scheduling policy** and **priority level** for the thread.

#### **Example: Setting Thread Priority in `pthread` (Linux)**
```cpp
#include <pthread.h>
#include <iostream>
#include <unistd.h>

void* worker(void* arg) {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Working in thread\n";
        usleep(500000);  // Simulate work (500 ms)
    }
    return nullptr;
}

int main() {
    pthread_t t1;
    pthread_create(&t1, nullptr, worker, nullptr);

    // Set the thread priority (using pthread_setschedparam)
    sched_param sch_params;
    sch_params.sched_priority = 10; // Set priority value (higher = higher priority)
    if (pthread_setschedparam(t1, SCHED_FIFO, &sch_params) != 0) {
        std::cerr << "Failed to set thread priority!" << std::endl;
    }

    pthread_join(t1, nullptr);
    return 0;
}
```

### **Summary:**
- **`pthread`** provides a way to **explicitly set thread priorities** using `pthread_setschedparam`.
- The **priority values** depend on the scheduling policy. Real-time scheduling policies (like `SCHED_FIFO` and `SCHED_RR`) allow explicit priority control, while `SCHED_OTHER` uses a time-sharing algorithm without direct priority control.

---

## **3. `std::jthread` (C++20)**

### **Thread Priority in `std::jthread`:**

- **C++20 `std::jthread`** is a higher-level abstraction for threads, and like `std::thread`, **it does not provide direct control over thread priority** in the standard C++ library.
  
- **Automatic Joining:** One of the key differences between `std::thread` and `std::jthread` is that `std::jthread` automatically joins when it goes out of scope. However, `std::jthread` does not expose an API for explicitly managing thread priorities.

- **Underlying Operating System:** The underlying thread scheduler (OS) determines the priority of the threads created by `std::jthread`. Therefore, to modify the priority, you would still need to use the OS-specific APIs, just like with `std::thread`.

### **How to Handle Priority in `std::jthread`:**
Similar to `std::thread`, you can control thread priority in `std::jthread` indirectly via OS-specific mechanisms, such as `pthread_setschedparam` on Linux or `SetThreadPriority` on Windows.

### **Example (Linux) Using `pthread_setschedparam` in `std::jthread`:**
```cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <pthread.h>

void worker() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Working in jthread\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::jthread t(worker);
    
    // Set thread priority (using pthread_setschedparam) on Linux
    pthread_t native_handle = t.native_handle();
    sched_param sch_params;
    sch_params.sched_priority = 20; // Priority value
    if (pthread_setschedparam(native_handle, SCHED_FIFO, &sch_params) != 0) {
        std::cerr << "Failed to set thread priority!" << std::endl;
    }

    // The jthread will automatically join at the end of the scope
    return 0;
}
```

### **Summary:**
- **`std::jthread`** behaves similarly to `std::thread` in terms of priority management, meaning it relies on the OS’s thread scheduling.
- You can adjust thread priority by using platform-specific APIs like `pthread_setschedparam` (Linux) or `SetThreadPriority` (Windows).

---

## **Summary of Thread Priority Support**

| Feature               | `std::thread`            | `pthread` (POSIX Threads)     | `std::jthread`               |
|-----------------------|--------------------------|------------------------------|-----------------------------|
| **Direct Priority Control** | No                    | Yes                          | No                          |
| **OS-specific APIs**  | Yes (Windows/Linux)       | Yes (Linux/macOS)            | Yes (via native handle)      |
| **Thread Scheduling** | OS default scheduling     | Custom scheduling (FIFO, RR, etc.) | OS default scheduling        |
| **Automatic Join**     | No                       | No                           | Yes                         |
| **Real-time Scheduling** | No                     | Yes (SCHED_FIFO, SCHED_RR)   | No                          |

### Conclusion:

- **`std::thread`** and **`std::jthread`** do not directly support thread priority in the C++ standard but can rely on OS-specific APIs for setting priority.
- **`pthread`** provides robust control over thread priority through different scheduling policies, making it suitable for applications requiring fine-grained control over thread behavior.
- For **real-time applications**, **POSIX threads** are better suited as they provide direct control over thread priority.

Here is a detailed breakdown of **`std::this_thread::yield()`** across **`std::thread`**, **`pthread`**, and **`std::jthread`**:

---

## **1. `std::this_thread::yield()`**

### **Function Used:**
- `std::this_thread::yield()` is part of the C++11 standard, available in the `<thread>` header.

### **Use Case:**
- The `yield()` function is used when a thread wants to **voluntarily yield the processor** to allow other threads of equal or higher priority to execute.
- It is useful in scenarios where threads are performing cooperative multitasking and want to allow others to run, especially in busy-wait loops.

### **Working:**
- The function **suggests** to the thread scheduler that the current thread is willing to yield its remaining time slice. It does not force the thread to stop but allows the operating system’s scheduler to decide whether to switch to another thread or keep running the current thread.
- It is a hint to the OS, but the behavior depends on the operating system’s scheduling policy.

### **Code Example (`std::thread`)**:
```cpp
#include <iostream>
#include <thread>
#include <chrono>

void worker(int id) {
    for (int i = 0; i < 10; ++i) {
        std::cout << "Thread " << id << " is working\n";
        
        if (id == 2) {
            std::cout << "Thread " << id << " is yielding...\n";
            std::this_thread::yield();  // Suggest to yield execution to other threads
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    }
}

int main() {
    std::thread t1(worker, 1);  // Thread 1
    std::thread t2(worker, 2);  // Thread 2 (will yield)
    std::thread t3(worker, 3);  // Thread 3

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
```
### **Output:**
```
Thread 1 is working
Thread 2 is working
Thread 3 is working
Thread 1 is working
Thread 2 is yielding...
Thread 3 is working
Thread 1 is working
Thread 2 is working
Thread 3 is working
...
```

### **Notes:**
- **Not a guarantee:** The `yield()` call doesn't guarantee that the other thread will run. The thread scheduling still depends on the system's thread scheduler.
- **Usage:** Often used in busy-wait loops or in cooperative multitasking scenarios to prevent one thread from monopolizing the CPU.

---

## **2. `pthread_yield()` (POSIX Threads)**

### **Function Used:**
- **`pthread_yield()`** (part of POSIX Threads) is used to give up the CPU for other threads.
- On most systems, `pthread_yield()` is essentially equivalent to **`sched_yield()`**, which is used to yield the current thread to the system's scheduler.

### **Use Case:**
- Used in POSIX thread applications when you need to **yield the CPU** to allow other threads to run. Typically, `pthread_yield()` is used in **real-time systems** or in **multi-threaded applications** where threads need to voluntarily give up their time slice.
- It can be used in place of `std::this_thread::yield()` when working with pthreads directly.

### **Working:**
- **`pthread_yield()`** works similarly to `std::this_thread::yield()`. It doesn't guarantee the thread will stop, but it suggests that the system should run another thread.
  
### **Code Example (`pthread`)**:
```cpp
#include <pthread.h>
#include <iostream>
#include <unistd.h>

void* worker(void* id) {
    for (int i = 0; i < 10; ++i) {
        std::cout << "Thread " << *(int*)id << " is working\n";
        
        if (*(int*)id == 2) {
            std::cout << "Thread " << *(int*)id << " is yielding...\n";
            pthread_yield();  // Suggest to yield execution to other threads
        }
        
        usleep(100000); // Simulate work (100ms)
    }
    return nullptr;
}

int main() {
    pthread_t t1, t2, t3;
    int id1 = 1, id2 = 2, id3 = 3;

    pthread_create(&t1, nullptr, worker, &id1);
    pthread_create(&t2, nullptr, worker, &id2);
    pthread_create(&t3, nullptr, worker, &id3);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);

    return 0;
}
```

### **Output:**
```
Thread 1 is working
Thread 2 is working
Thread 3 is working
Thread 1 is working
Thread 2 is yielding...
Thread 3 is working
Thread 1 is working
Thread 2 is working
...
```

### **Notes:**
- **POSIX-specific:** `pthread_yield()` is available in POSIX-compliant systems, such as Linux and macOS.
- **Thread Scheduling:** The actual thread switch depends on the OS's scheduler and the system's load.

---

## **3. `std::jthread` (C++20)**

### **Function Used:**
- `std::jthread` is a new thread abstraction introduced in C++20, which **automatically joins** the thread at the end of its scope and provides several improvements over `std::thread`.
- `std::jthread` **uses `std::this_thread::yield()`** internally, allowing threads to give up their time slice.

### **Use Case:**
- Used when threads need to be managed with less boilerplate code. `std::jthread` automatically joins the thread at the end of its scope and can be used to handle **thread interruption**, which makes it a better choice in some cases compared to `std::thread`.
  
### **Working:**
- Similar to `std::thread`, but it has a feature of automatic joining and cancellation.
- **Yielding** in `std::jthread` is done using `std::this_thread::yield()` as part of its thread management, allowing threads to yield when necessary.

### **Code Example (`std::jthread`)**:
```cpp
#include <iostream>
#include <thread>
#include <chrono>

void worker(int id) {
    for (int i = 0; i < 10; ++i) {
        std::cout << "Thread " << id << " is working\n";
        
        if (id == 2) {
            std::cout << "Thread " << id << " is yielding...\n";
            std::this_thread::yield();  // Suggest to yield execution to other threads
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    }
}

int main() {
    std::jthread t1(worker, 1);  // Thread 1
    std::jthread t2(worker, 2);  // Thread 2 (will yield)
    std::jthread t3(worker, 3);  // Thread 3

    // No need to manually join the threads, as `std::jthread` will do it automatically.
    return 0;
}
```

### **Output:**
```
Thread 1 is working
Thread 2 is working
Thread 3 is working
Thread 1 is working
Thread 2 is yielding...
Thread 3 is working
Thread 1 is working
Thread 2 is working
...
```

### **Notes:**
- **Automatic Joining:** `std::jthread` automatically joins the thread at the end of its scope, so you do not need to manually join the threads like you do with `std::thread`.
- **Thread Interruption:** It allows for better management of thread interruption and cancellation, which is not available in `std::thread`.

---

## **Summary of Key Differences**

| Feature               | `std::this_thread::yield()` | `pthread_yield()`             | `std::jthread` (C++20)        |
|-----------------------|-----------------------------|------------------------------|------------------------------|
| **Thread Library**     | C++ Standard Library        | POSIX Threads                | C++20 Standard Library       |
| **Use Case**           | Yield to other threads      | Yield to other threads       | Automatic thread management  |
| **Function Name**      | `std::this_thread::yield()` | `pthread_yield()`            | Uses `std::this_thread::yield()` internally |
| **Automatic Join**     | No                          | No                           | Yes                          |
| **Interrupt Handling** | No                          | No                           | Yes (supports thread interruption) |
| **Thread Creation**    | `std::thread`               | `pthread_create()`           | `std::jthread`               |

### Conclusion:
- **`std::this_thread::yield()`** is a standard C++ function to suggest yielding execution, available in `std::thread` and `std::jthread`.
- **`pthread_yield()`** is used in POSIX threads to yield CPU time, and it behaves similarly to `std::this_thread::yield()`.
- **`std::jthread`** is a higher-level abstraction available in C++20, providing better thread management, including automatic joining and cancellation, and uses `std::this_thread::yield()` for yielding execution.