// Mismatched Allocation/Deallocation occurs

#include <iostream>

int main() {
    // Allocate an array of 10 integers
    int* array = new int[10];

    // Code that uses the array (just for demonstration)
    for (int i = 0; i < 10; ++i) {
        array[i] = i * i;
    }

    // Output the array contents
    for (int i = 0; i < 10; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // Vulnerable delete - mismatched allocation/deallocation
    delete array;  // ERROR: Should use delete[] instead of delete

    return 0;
}

// //safer option
// #include <iostream>

// int main() {
//     // Allocate an array of 10 integers
//     int* array = new int[10];

//     // Code that uses the array (just for demonstration)
//     for (int i = 0; i < 10; ++i) {
//         array[i] = i * i;
//     }

//     // Output the array contents
//     for (int i = 0; i < 10; ++i) {
//         std::cout << array[i] << " ";
//     }
//     std::cout << std::endl;

//     // Correct delete[] to deallocate memory allocated with new[]
//     delete[] array;  // Correct deallocation

//     return 0;
// }
