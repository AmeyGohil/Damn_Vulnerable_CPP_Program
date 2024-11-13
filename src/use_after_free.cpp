// use after free occurs
#include <iostream>

int main() {
    int* ptr = new int(10);  // Allocate memory
    std::cout << "Value before free: " << *ptr << std::endl;  // Output: 10

    delete ptr;  // Free the memory
    *ptr = 20;   // Use-after-free: accessing memory after it has been deleted

    return 0;
}

// // safe option1
// #include <iostream>

// int main() {
//     int* ptr = new int(10);  // Allocate memory
//     std::cout << "Value before free: " << *ptr << std::endl;  // Output: 10

//     delete ptr;  // Free the memory
//     ptr = nullptr;  // Nullify the pointer to prevent use-after-free

//     // Attempt to use ptr after freeing it will now be safe because it's nullptr
//     if (ptr != nullptr) {
//         *ptr = 20;   // This will not be executed because ptr is nullptr
//     }

//     return 0;
// }

// //safe option2 with clang++ -std=c++17
// #include <iostream>
// #include <memory>  // For std::unique_ptr

// int main() {
//     // Manual approach to creating a unique_ptr in pre-C++14 compilers
//     std::unique_ptr<int> ptr(new int(10));  // Allocate and initialize memory
//     std::cout << "Value before free: " << *ptr << std::endl;  // Output: 10

//     // No need to manually delete, unique_ptr will automatically free the memory
//     // when it goes out of scope.

//     return 0;
// }
