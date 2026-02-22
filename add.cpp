#include <iostream>

int convertir(char str[]) {
    int res = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char a = str[i];
        res = res * 10 + a - '0';
    }
    return res;
}

int add(int a, int b) {
    return a + b;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "pas assez d'arguments" << std::endl;
    }
    else {
        int somme = 0;
        int i = 1;
        while (i < argc) {
            int nombre = convertir(argv[i]);
            somme = add(somme, nombre);
            i = i + 1;
        }

        std::cout << "résultat : " << somme << std::endl;
    }
    return 0;
}