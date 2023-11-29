#include "scanner.hpp"

int main (int argc, const char *argv[]) {

    if (argc < 3) {
        printf("%s\n", "Please feed the compiler both"
                " input and output files respectively!");
        return 1;
    };
    
    if (argc == 3) {
        printf("%s\n", "Scanning...");
        scanner scanner(argv[1], argv[2]);
        scanner.scan();
        scanner.write();
    };
    
    return 0;
};