#include <iostream>
#include <limits>

int add(int a, int b, int c){
    return a + b + c;
}

int main(int argc, char *argv[]){
    int i = 0 ;
    while (i < argc){
        std::cout << argv[i] <<std::endl;
        i = i + 1;

    }
    

    return 0;
}