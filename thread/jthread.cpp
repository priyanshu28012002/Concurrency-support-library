// #include <iostream>
// #include <thread>

// void worker() {
//     for (int i = 0; i < 5; ++i) {
//         std::cout << "Working in thread\n";
//         std::this_thread::yield();  // Suggesting to yield execution
//     }
// }

// int main() {
//     std::thread t(worker);  // Create a new thread and start executing the worker function
//     t.join();  // Wait for the worker thread to finish
//     return 0;
// }

#include <iostream>
#include <thread>
#include <chrono>

void worker(int id) {
    // Start time for the thread
    auto starting = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10; ++i) {  // Increase iterations for more work
        if (id == 1) {
            std::cout << "Thread " << id << " is yielding...\n";
            std::this_thread::yield();  // Suggest to yield execution
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Reduced sleep time to 100ms
    }

    // End time after work is done
    auto ending = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(ending - starting);

    std::cout << "Thread " << id << " finished execution in " << duration.count() << " milliseconds\n";
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
