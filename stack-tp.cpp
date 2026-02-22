#include <iostream>
#include <stdexcept>
// Nous allons implémenter une pile d'entiers de manière très basique.
// Nous la complexifierons par la suite
// La pile est constituée:
//    - d'un tableau d'entier, avec sa taille et son nombre d'éléments empilés
//    - des quatre fonctions: push, pop, top, print, is_empty et is_full
//      (qui testent si la pile est resp. vide ou pleine)
//      il faut les utiliser dans votre code de push et pop

void print(int tab[],int taille, int nb) {
// cette fonction affiche les entiers empilés
    std::cout<<'[';
    for(int i=0; i<nb; i++) {
        std::cout<<tab[i];
        if(i<nb-1){
            std::cout<<",";
        }
    }
    std::cout<<']'<<std::endl;
}

// renvoie true si la pile est vide, false sinon
bool is_empty(int tab[], int taille, int nb) {
    if(nb==0){return true;}
    else {return false;}
}

// renvoie true si la pile est pleine, false sinon
bool is_full(int tab[], int taille,int nb)
{
    if(nb==taille) {return true;}
    else {return false;}
}

void push(int tab[], int taille, int& nb,int valeur) {
// cette fonction ajoute un entier à la pile passé en argument
// elle doit s'assurer que la pile n'est pas pleine avant d'empiler
// elle lance une exception si problème
    if (is_full(tab, taille, nb)) {
        throw std::runtime_error("liste pleine");
    }
    tab[nb]=valeur;
    nb = nb+1;
}

int top(int tab[],int taille, int nb) {
    if(is_empty(tab,taille,nb)) {
        throw std::runtime_error("liste vide");
    }
    return tab[nb-1];
}

int pop(int tab[],int taille, int& nb) {
    if(is_empty(tab,taille,nb)){
        throw std::runtime_error("erreur liste vide");
    }
    nb=nb-1;
    return tab[nb];
}

// https://en.cppreference.com/w/cpp/header/stdexcept.html
// pour un exemple d'exception voir le fichier exception.cpp

//code faux car ne garde pas en mémoire le tableau
//int* create_stack (int size){
//    int tab[size];
//    return tab;
//}


int* create_stack(int size){
    int* t = new int[size];
    return t;
}

void delete_stack(int* argv){
    delete[] argv;
}

int main() {
    int taille = 5;
    int* stack = create_stack(taille);
    int nb = 0;

    try {
        print(stack, taille, nb); 
        push(stack, taille, nb, -17);
        push(stack, taille, nb, 90);
        print(stack, taille, nb);
        std::cout << "Le sommet est : " << top(stack, taille, nb) << std::endl;
        int valeur_sortie = pop(stack, taille, nb);
        std::cout << "On a retire : " << valeur_sortie << std::endl;
        print(stack, taille, nb);

        //pour forcer l'erreur
        push(stack, taille, nb, 10);
        push(stack, taille, nb, 20);
        push(stack, taille, nb, 30);
        push(stack, taille, nb, 40);
        
        std::cout << "élément en trop" << std::endl;
        push(stack, taille, nb, 50); //exception
    }
    catch (const std::runtime_error& e) {
        std::cout << "Erreur : " << e.what() << std::endl;
    }
}