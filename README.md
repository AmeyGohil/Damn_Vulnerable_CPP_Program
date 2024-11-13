# Damn Vulnerable C++ Program (DVCPPP)

This repository contains a C++ program that is intentionally designed with several common vulnerabilities, including buffer overflows, use-after-free, double free, integer overflow, and more. The purpose of this project is to provide a safe environment for learning and testing exploitation techniques that are frequently encountered in real-world applications.

## **Vulnerabilities Included**

- **Buffer Overflow**: Writing outside the bounds of allocated memory.
- **Use-After-Free**: Accessing memory after it has been freed.
- **Double Free**: Calling `free()` on a memory address that has already been freed.
- **Integer Overflow/Underflow**: Overflowing or underflowing integers, causing unexpected behavior.
- **Memory Leaks**: Failing to free allocated memory, leading to resource exhaustion.
- **Out-of-Bounds Read/Write (OOBR/OOBW)**: Reading or writing past allocated buffer sizes.
- **Stack Overflow**: Excessive function calls causing the stack to exhaust its allocated space, resulting in a program crash or potentially exploitable behavior.

## **Features**

- Designed for educational purposes, this repository helps security enthusiasts and developers learn about common C++ vulnerabilities.
- Includes sample input file to help discover vulnerabilities in the program.

## **Installation**

To get started with the DVCPPP program, follow these steps:

### **Clone the Repository**

```bash
git clone https://github.com/your-username/Damn-Vulnerable-CPP-Program.git
cd Damn-Vulnerable-CPP-Program
```

### Build the Program

To compile the program, use the following command:

```bash
g++ -o dvcppp ./src/dvcppp.cpp
```

This will compile the `dvcppp.cpp` source file into an executable.

## Usage

To run the program with a sample input file:

```bash
./dvcppp input_dir/sample_input.bin
```

### Custom Input File
To create custom input files, refer to `input_dir/README.md` for instructions. The guide explains how to use the `create_sample_input.cpp` script to generate compatible `.bin` files for `dvcppp`. You can use any image file as well.

## Contributing

We welcome contributions! If you want to contribute to this project, please:

1. Fork the repository.
2. Create a new branch (git checkout -b feature-branch).
3. Commit your changes (git commit -am 'Add new vulnerability').
4. Push to your fork (git push origin feature-branch).
5. Create a pull request.

## Acknowledgments

- This project is inspired by the [Damn Vulnerable C Program (DVCP)](https://github.com/hardik05/Damn_Vulnerable_C_Program), which provides a similar environment for learning C-based vulnerabilities.
- Thanks to the open-source community for contributing to educational resources on secure coding practices.
