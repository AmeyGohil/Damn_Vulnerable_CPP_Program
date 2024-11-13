// memory leak occurs
#include <iostream>

int main() {
    // Dynamically allocating memory
    int* ptr = new int(10);

    // Doing some operations (e.g., printing the value)
    std::cout << "Value: " << *ptr << std::endl;

    // Memory leak: No 'delete' statement to free allocated memory

    return 0;  // Memory allocated for 'ptr' is not freed, causing a memory leak
}

// //safer option 1

// #include <iostream>

// int main() {
//     // Dynamically allocating memory
//     int* ptr = new int(10);

//     // Doing some operations (e.g., printing the value)
//     std::cout << "Value: " << *ptr << std::endl;

//     // Properly deallocate memory to prevent memory leak
//     delete ptr;  // Release the memory allocated by 'new'

//     return 0;
// }

// // safer option 2 //clang++ -std=c++17 
// #include <iostream>
// #include <memory>  // For std::unique_ptr

// int main() {
//     // Using smart pointer (std::unique_ptr) for automatic memory management
//     std::unique_ptr<int> ptr = std::make_unique<int>(10);

//     // Doing some operations (e.g., printing the value)
//     std::cout << "Value: " << *ptr << std::endl;

//     // No need to manually delete ptr, it will be automatically freed
//     // when it goes out of scope.

//     return 0;
// }
