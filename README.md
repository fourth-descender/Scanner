# Scanner

A simple project that tokenizes `.c1` files, intended for future extension into a compiler.

## Building The Scanner

### Manual Build

1. Create the build folder (if it doesn't exist).
    ```bash
    mkdir -p build
    ```

2. Configure using `cmake`.
    ```bash
    cmake -S . -B build
    ```

3. Build using `cmake`.
    ```bash
    cmake --build build
    ```

### Using Makefile

Alternatively, you can use the provided `Makefile` to automate the process:

```bash
make all
```
This command builds the scanner and the test executable required for make test. 

To run the tests:
```bash
make test
```
To clean up generated files:
```bash
make clean
```

### Additional Information
* The Makefile simplifies the build process. You can execute make without any arguments, and it will default to make all.
* Ensure that you have cmake installed on your system.
* The scanner executable is placed in the bin folder, while the test executable is located in the test/bin folder.

## Using The Scanner
To use the scanner, simply feed it a `c1` file and an output name for the resulting `.txt` file. For example, 
```bash
bin/compiler test_cases/test1.c1 output1.txt
```
This command generates `output1.txt` in the results folder.