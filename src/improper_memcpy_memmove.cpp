// Improper Use of 'memcpy' or 'memmove' occurs

#include <iostream>
#include <cstring>

int main() {
    // Vulnerable code with buffer overflow
    char buffer1[10] = "123456789";  // 9 characters plus null terminator
    char buffer2[5];  // Only 5 characters can fit in buffer2

    std::cout << "Before memcpy:" << std::endl;
    std::cout << "buffer1: " << buffer1 << std::endl;
    std::cout << "buffer2: " << buffer2 << std::endl;

    // Vulnerable memcpy causing buffer overflow
    memcpy(buffer2, buffer1, 10);  // This will overflow buffer2

    std::cout << "After memcpy:" << std::endl;
    std::cout << "buffer1: " << buffer1 << std::endl;
    std::cout << "buffer2: " << buffer2 << std::endl;

    return 0;
}

//safer option
// #include <iostream>
// #include <cstring>

// void safe_memcpy(char* dest, const char* src, size_t dest_size, size_t src_size) {
//     // Check if destination buffer is large enough to hold the source buffer data
//     if (src_size > dest_size) {
//         std::cerr << "Error: Source buffer is too large for the destination buffer!" << std::endl;
//         return;
//     }
//     memcpy(dest, src, src_size);  // Safe memcpy with size check
// }

// int main() {
//     char buffer1[10] = "123456789";  // 9 characters + null terminator
//     char buffer2[5];  // Only 5 characters can fit in buffer2

//     std::cout << "Before safe_memcpy:" << std::endl;
//     std::cout << "buffer1: " << buffer1 << std::endl;
//     std::cout << "buffer2: " << buffer2 << std::endl;

//     // Calculate the length of the data to be copied
//     size_t data_length = strlen(buffer1) + 1;  // Including the null terminator

//     // Use the safer memcpy function with a size check
//     safe_memcpy(buffer2, buffer1, sizeof(buffer2), data_length);

//     std::cout << "After safe_memcpy:" << std::endl;
//     std::cout << "buffer1: " << buffer1 << std::endl;
//     std::cout << "buffer2: " << buffer2 << std::endl;

//     return 0;
// }
