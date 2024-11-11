#include <iostream>
#include <fstream>

int main() {
    std::ofstream file("sample_image.bin", std::ios::binary);
    
    // Define an example Image struct
    struct Image {
        char header[4] = {'I', 'M', 'G', '\0'};
        int width = 1024;
        int height = 768;
        char data[10] = {'D', 'A', 'T', 'A', '0', '1', '2', '3', '4', '5'};
    };
    
    Image img;
    
    // Write a few Image structs to the file
    for (int i = 0; i < 3; ++i) {
        file.write(reinterpret_cast<char*>(&img), sizeof(img));
    }
    
    file.close();
    std::cout << "sample_image.bin created successfully." << std::endl;
    return 0;
}
