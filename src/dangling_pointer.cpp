//dangling pointer occurs

#include <iostream>

int main() {
    // Allocate memory for an integer and initialize it
    int* ptr = new int(10);

    // Deallocate the memory
    delete ptr;

    // Accessing the memory after deallocation (Dangling pointer)
    std::cout << *ptr << std::endl; // This is undefined behavior

    return 0;
}

// //safer option 1
// #include <iostream>

// int main() {
//     // Allocate memory for an integer and initialize it
//     int* ptr = new int(10);

//     // Deallocate the memory and set the pointer to nullptr
//     delete ptr;
//     ptr = nullptr;

//     // Attempting to dereference a null pointer will cause a clear error
//     if (ptr != nullptr) {
//         std::cout << *ptr << std::endl; // This won't be executed
//     } else {
//         std::cout << "Pointer is null, cannot access memory." << std::endl;
//     }

//     return 0;
// }

// //safer option using smart pointers
// #include <iostream>
// #include <memory>  // For std::unique_ptr

// int main() {
//     // Use a unique_ptr to automatically manage memory
//     std::unique_ptr<int> ptr = std::make_unique<int>(10);

//     // No need to manually delete; it's handled automatically
//     // The pointer will go out of scope and memory will be freed automatically

//     // Accessing the pointer is safe as long as it's not null
//     std::cout << *ptr << std::endl;

//     // No manual delete needed
//     return 0;
// }
