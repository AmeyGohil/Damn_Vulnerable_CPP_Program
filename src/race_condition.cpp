// race condition occurs

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

int sharedData = 0;  // Shared data that is accessed by multiple threads
std::vector<int> sharedArray(100, 0);  // A shared array that can be modified concurrently

void increment() {
    for (int i = 0; i < 100; ++i) {
        sharedData++;  // Data race here when accessed by multiple threads

        // Simulating more complex data modification with an unpredictable pattern
        int idx = (i * 31) % 100;  // Random index calculation
        sharedArray[idx]++;  // Data race if accessed by multiple threads
    }
}

void complexTask() {
    for (int i = 0; i < 100; ++i) {
        int idx = (i * 29) % 100;  // Another random index calculation
        sharedArray[idx] += 2;  // More complex modification to the shared array
    }
}

int main() {
    // Create multiple threads that call the increment function
    std::thread t1(increment);
    std::thread t2(increment);
    std::thread t3(complexTask);
    std::thread t4(complexTask);

    // Wait for all threads to finish
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // Output final results
    std::cout << "Final value of sharedData: " << sharedData << std::endl;

    std::cout << "Final values of sharedArray: ";
    for (int val : sharedArray) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}


// safer option

// #include <iostream>
// #include <thread>
// #include <vector>
// #include <mutex>

// int sharedData = 0;  // Shared data that is accessed by multiple threads
// std::vector<int> sharedArray(100, 0);  // A shared array that can be modified concurrently
// std::mutex dataMutex;   // Mutex for sharedData
// std::mutex arrayMutex;  // Mutex for sharedArray

// void increment() {
//     for (int i = 0; i < 100; ++i) {
//         {
//             std::lock_guard<std::mutex> lock(dataMutex);  // Locking sharedData
//             sharedData++;  // Safe increment of sharedData
//         }

//         int idx = (i * 31) % 100;
//         {
//             std::lock_guard<std::mutex> lock(arrayMutex);  // Locking sharedArray
//             sharedArray[idx]++;  // Safe increment of sharedArray[idx]
//         }
//     }
// }

// void complexTask() {
//     for (int i = 0; i < 100; ++i) {
//         int idx = (i * 29) % 100;
//         {
//             std::lock_guard<std::mutex> lock(arrayMutex);  // Locking sharedArray
//             sharedArray[idx] += 2;  // Safe modification of sharedArray[idx]
//         }
//     }
// }

// int main() {
//     // Create multiple threads that call the increment function
//     std::thread t1(increment);
//     std::thread t2(increment);
//     std::thread t3(complexTask);
//     std::thread t4(complexTask);

//     // Wait for all threads to finish
//     t1.join();
//     t2.join();
//     t3.join();
//     t4.join();

//     // Output final results
//     std::cout << "Final value of sharedData: " << sharedData << std::endl;

//     std::cout << "Final values of sharedArray: ";
//     for (int val : sharedArray) {
//         std::cout << val << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
