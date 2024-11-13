//double free occurs
#include <iostream>

int main() {
    int* ptr = new int(10);  // Allocate memory
    std::cout << *ptr << std::endl;  // Output: 10

    delete ptr;  // First deallocation
    delete ptr;  // Second deallocation (double free)

    return 0;
}

// //safer option
// #include <iostream>

// int main() {
//     int* ptr = new int(10);  // Allocate memory
//     std::cout << *ptr << std::endl;  // Output: 10

//     delete ptr;  // First deallocation
//     ptr = nullptr;  // Set pointer to nullptr to avoid double free

//     // The second delete is safe now because the pointer is null
//     if (ptr != nullptr) {
//         delete ptr;  // This is a no-op because ptr is nullptr
//     }

//     return 0;
// }
