#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {

    if (argc < 2) {

        std::cerr << "not enough arguments" << std::endl;
        return -1;
    }
    int total = 0;
    int i = 1;
    while (i < argc) {
        total = total + std::atoi(argv[i]);
        i = i + 1;
    }
    std::cout << "résultat : " << total << std::endl;
    return 0;
 }