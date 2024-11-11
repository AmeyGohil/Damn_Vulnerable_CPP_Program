# Creating Custom Input Files for DVCPPP

This guide shows how to create custom binary input files compatible with the `dvcppp` program. 

## Using `create_sample_input.cpp`

The `create_sample_input.cpp` script generates a `.bin` file with a predefined structure that `dvcppp` expects.

### Sample Structure of Input Files

The `.bin` input file should follow this structure:

- **Header**: A 4-byte character array (e.g., "IMG")
- **Width**: An integer representing the image width (e.g., 1024)
- **Height**: An integer representing the image height (e.g., 768)
- **Data**: A 10-byte character array (e.g., "DATA012345")

### Compiling and Running the Script

1. **Compile the script**:
    ```bash
    g++ create_sample_input.cpp -o create_sample_input
    ```
2. Run the script:
    ```bash
    ./create_sample_input sample_input.bin
    ```