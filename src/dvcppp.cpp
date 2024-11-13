#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

struct Image {
    char header[4];
    int width;
    int height;
    char data[10];
};

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

    ProcessImage(argv[1]);
    return 0;
}
