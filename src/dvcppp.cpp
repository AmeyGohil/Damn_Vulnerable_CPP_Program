#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <vector>
#include <chrono>

struct Image {
    char header[4];
    int width;
    int height;
    char data[10];
};

// Example 1: Threading with Cross-Stack Variable Access (Race Condition)
void threadFunction(int* data) {
    *data = 42;  // Cross-stack access if 'data' is from another thread's stack
}

void threadingExample() {
    std::cout << "\n--- Threading Example: Cross-Stack Variable Access ---\n";
    
    // Threading example: cross-stack variable access
    int stackVar = 10;
    std::thread t(threadFunction, &stackVar);  // Passing the address of a stack variable
    t.join();

    std::cout << "stackVar after thread execution: " << stackVar << std::endl;  // Expecting 42
}`

// Example 2: Dangling Pointer
void danglingPointerExample() {
    std::cout << "\n--- Dangling Pointer Example ---\n";
    
    int* ptr = new int(10);  // Allocate memory for an integer and initialize it
    delete ptr;  // Deallocate the memory
    // Accessing the memory after deallocation (Dangling pointer)
    std::cout << *ptr << std::endl; // This is undefined behavior
}

// Example 3: Double Free
void doubleFreeExample() {
    std::cout << "\n--- Double Free Example ---\n";
    
    int* ptr2 = new int(10);  // Allocate memory
    std::cout << *ptr2 << std::endl;  // Output: 10
    delete ptr2;  // First deallocation
    delete ptr2;  // Second deallocation (double free)
}

// Example 4: Improper Use of 'memcpy' (Buffer Overflow)
void improperMemcpyExample() {
    std::cout << "\n--- Improper Use of 'memcpy' Example (Buffer Overflow) ---\n";
    
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
}

// Example 5: Memory Leak
void memoryLeakExample() {
    std::cout << "\n--- Memory Leak Example ---\n";
    
    int* ptr3 = new int(10);  // Dynamically allocating memory
    std::cout << "Value: " << *ptr3 << std::endl;  // Doing some operations (e.g., printing the value)
    // Memory leak: No 'delete' statement to free allocated memory
}

// Example 6: Mismatched Allocation/Deallocation
void mismatchedAllocationDeallocationExample() {
    std::cout << "\n--- Mismatched Allocation/Deallocation Example ---\n";
    
    int* array = new int[10];  // Allocate an array of 10 integers

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
}

// --- Race Condition ---
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

void raceConditionExample() {
    std::cout << "\n--- Race Condition Example ---\n";

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
}

// --- Uninitialized Memory ---
void uninitializedMemoryExample() {
    std::cout << "\n--- Uninitialized Memory Example ---\n";

    // Vulnerable Code
    int* heapVar = new int;    // Uninitialized heap memory
    int stackVar;              // Uninitialized stack variable

    // Use of uninitialized memory leads to unpredictable behavior
    int value = *heapVar + stackVar;  // Undefined behavior: heapVar and stackVar are uninitialized

    std::cout << "Value: " << value << std::endl;

    delete heapVar;  // Free the allocated heap memory
}

// --- Use After Free ---
void useAfterFreeExample() {
    std::cout << "\n--- Use After Free Example ---\n";

    int* ptr = new int(10);  // Allocate memory
    std::cout << "Value before free: " << *ptr << std::endl;  // Output: 10

    delete ptr;  // Free the memory
    *ptr = 20;   // Use-after-free: accessing memory after it has been deleted
}

void stack_operation() {
    char buff[0x1000];
    while (true) {
        // break;
        stack_operation();  // stack overflow due to infinite recursion
    }
}

int ProcessImage(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "\nCan't open file or file doesn't exist.\r\n";
        exit(0);
    }

    Image img;
    while (file.read(reinterpret_cast<char*>(&img), sizeof(img))) {
        std::cout << "\n\tHeader\twidth\theight\tdata\r\n";
        std::cout << "\n\t" << img.header << "\t" << img.width << "\t" << img.height << "\t" << img.data << "\r\n";

        // integer overflow
        int size1 = img.width + img.height;
        char* buff1 = new char[size1];

        // heap buffer overflow
        memcpy(buff1, img.data, sizeof(img.data));
        delete[] buff1;

        // double free
        if (size1 % 2 == 0) {
            delete[] buff1;  // double free vulnerability
        } else {
            // use after free
            if (size1 % 3 == 0) {
                buff1[0] = 'a';  // accessing memory after deletion (use-after-free)
            }
        }

        // integer underflow (negative value leading to large allocation)
        int size2 = img.width - img.height + 100;
        char* buff2 = new char[size2];

        // heap buffer overflow
        memcpy(buff2, img.data, sizeof(img.data));
        delete[] buff2;

        // divide by zero
        int size3 = img.width / img.height;
        char buff3[10];
        char* buff4 = new char[size3];
        memcpy(buff4, img.data, sizeof(img.data));

        // out of bounds read/write (OOBR and OOBW)
        char OOBR = buff3[size3];  // OOB read
        char OOBR_heap = buff4[size3];  // OOB read
        buff3[size3] = 'c';  // OOB write
        buff4[size3] = 'c';  // OOB write

        if (size3 > 10) {
            // memory leak here
            buff4 = nullptr;
        } else {
            delete[] buff4;
        }

        int size4 = img.width * img.height;

        if (size4 % 2 == 0) {
            // stack exhaustion (stack overflow)
            stack_operation();
        } else {
            // heap exhaustion
            char* buff5;
            do {
                buff5 = new char[size4];
            } while (buff5);
        }
    }
    file.close();
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "No input file\n";
        exit(-1);
    }

    // Call the image processing function
    ProcessImage(argv[1]);
    
    threadingExample();  // Threading with cross-stack variable access
    danglingPointerExample();  // Dangling pointer
    doubleFreeExample();  // Double free vulnerability
    improperMemcpyExample();  // Improper use of 'memcpy' (buffer overflow)
    memoryLeakExample();  // Memory leak
    mismatchedAllocationDeallocationExample(); // Mismatched allocation/deallocation
    raceConditionExample();    // Race condition demonstration
    uninitializedMemoryExample();  // Uninitialized memory demonstration
    useAfterFreeExample();    // Use after free demonstration

    return 0;
}
