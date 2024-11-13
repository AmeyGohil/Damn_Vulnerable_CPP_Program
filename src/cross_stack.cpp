// Cross-stack Access occurs
//clang++ -std=c++17

#include <iostream>
#include <thread>

void threadFunction(int* data) {
    *data = 42;  // Cross-stack access if 'data' is from another thread's stack
}

int main() {
    int stackVar = 10;
    std::thread t(threadFunction, &stackVar);  // Passing the address of a stack variable
    t.join();

    std::cout << "stackVar after thread execution: " << stackVar << std::endl;  // Expecting 42
    return 0;
}

// //safer option clang++ -std=c++17

// #include <iostream>
// #include <thread>
// #include <memory>  // For std::shared_ptr

// void threadFunction(std::shared_ptr<int> data) {
//     *data = 42;  // Safe modification of the heap-allocated variable
// }

// int main() {
//     // Use std::shared_ptr to manage memory safely
//     auto stackVar = std::make_shared<int>(10);  // Initialize data on the heap

//     std::thread t(threadFunction, stackVar);  // Pass shared_ptr to thread
//     t.join();  // Wait for thread to complete

//     std::cout << "stackVar after thread execution: " << *stackVar << std::endl;  // Expecting 42
//     return 0;
// }
