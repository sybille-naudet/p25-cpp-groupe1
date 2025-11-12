//implémentation du code SWAP qui échange a et b

#include <iostream>

void swap(int& a, int& b){
    int t=a;
    a=b;
    b=t;
    
}

int main(){
    int i = 12;

    int j = 17;

    swap(i,j);

    std::cout<<std::boolalpha <<((i==17) and (j==12))<<std::endl;
}


//mécanisme de pile mais avec des fonctions

void print(){ //affichage du tableau qui vient d'être créé

}

void push(){

}

int pop(){

}

int main(){
    int size=5;
    int tab[size];
    int nb;
    print(tab,size,nb); // []
    push(tab,size,nb,-17);
    push(tab,size,nb,90);
    print(tab,size,nb); //[-17 90[
    int e=pop(tab,size,nb);
    std::cout<<e <<std::endl;
    print(tab,size,nb); //[-17[
    

}