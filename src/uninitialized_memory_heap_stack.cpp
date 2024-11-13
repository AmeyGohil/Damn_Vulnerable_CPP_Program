// uninitialized memory heap stack occurs
#include <iostream>

int main() {
    // Vulnerable Code
    int* heapVar = new int;    // Uninitialized heap memory
    int stackVar;              // Uninitialized stack variable
    
    // Use of uninitialized memory leads to unpredictable behavior
    int value = *heapVar + stackVar;  // Undefined behavior: heapVar and stackVar are uninitialized
    
    std::cout << "Value: " << value << std::endl;

    delete heapVar;  // Free the allocated heap memory
    return 0;
}

// //safer option

// #include <iostream>

// int main() {
//     // Safer Option: Initialize variables before using them
    
//     // Initialize heap memory using 'new' and explicitly set a value
//     int* heapVar = new int(0);  // Heap memory initialized to 0
    
//     // Initialize stack variable
//     int stackVar = 0;  // Stack variable initialized to 0
    
//     // Now, both variables are initialized, and we can safely use them
//     int value = *heapVar + stackVar;  // Safe access, no uninitialized memory
    
//     std::cout << "Value: " << value << std::endl;  // Outputs: Value: 0
    
//     delete heapVar;  // Free the allocated heap memory
//     return 0;
// }

