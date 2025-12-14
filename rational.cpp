
#include <iostream>
struct Rational {
    const int num;
    int denom = 1;
    Rational (int n, int d) //liste d'initialisation
    {
        // corps du constructeur vide ici
    }
};

void print(Rational* r){
    std::cout << r->num << "/"<< r.denom <<std::endl;
}

int main(){
    Rational r(1,2); //constructor
    print(r);
    return 0;
}

