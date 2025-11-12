#include <iostream>
#include <stdexcept>
// Nous allons implémenter une pile d'entiers de manière très basique.
// Nous la complexifierons par la suite.

// La pile est constituée:
//    - d'un tableau d'entier, avec sa taille et son nombre d'éléments empilés
//    - des quatre fonctions: push, pop, top, print, is_empty et is_full
//      (qui testent si la pile est resp. vide ou pleine)
//      il faut les utiliser dans votre code de push et pop

void print(int tab[],int taille, int nb)
// cette fonction affiche les entiers empilés
{
    std::cout<<'[';
    for(int i=0;i<nb;i++){
        std::cout<<tab[i];
        if(i<nb-1){
            std::cout<<",";
        }
    }
    std::cout<<']'<<std::endl;
}

// renvoie true si la pile est vide, false sinon
bool is_empty(int tab[], int taille, int nb)
{
    if(nb==0){return true;}
    else {return false;}
}

// renvoie true si la pile est pleine, false sinon
bool is_full(int tab[], int taille,int nb)
{
    if(nb==taille) {return true;}
    else {return false;}
}

void push(int tab[], int taille, int& nb,int valeur)
// cette fonction ajoute un entier à la pile passé en argument
// elle doit s'assurer que la pile n'est pas pleine avant d'empiler
// elle lance une exception si problème
{
    if(is_full(tab, taille, nb)) {
        throw std::runtime_error("liste pleine");
    }
    tab[nb]=valeur;
    nb = nb+1;
}

int top(int tab[],int taille, int nb) // (cette fonction ne dépile pas)
// cette fonction retourne l'entier en haut de la pile (le dernier empilé)
// à la sortie de cette fonction l'élément retourné reste dans la pile
// elle doit s'assurer que la pile n'est pas vide avant de la dépiler
// elle lance une exception si problème
{
    if(is_empty(tab,taille,nb)){
        throw std::runtime_error("liste vide");
    }
    return tab[nb-1];
}

int pop(int tab[],int taille, int& nb) // (cette fonction dépile)
// cette fonction retourne l'entier en haut de la pile (le dernier empilé)
// à la sortie de cette fonction l'élément retourné n'est plus compté dans la pile
// elle doit s'assurer que la pile n'est pas vide avant de la dépiler
// elle lance une exception si problème
{
    if(is_empty(tab,taille,nb)){
        throw std::runtime_error("erreur liste vide");
    }
    nb=nb-1;
    return tab[nb];
}

// https://en.cppreference.com/w/cpp/header/stdexcept.html
// pour un exemple d'exception voir le fichier exception.cpp

int main()
{

    // on définit les 3 variables constituant la pile
    int taille = 5;
    int stack[taille];
    int nb = 0;

    // rajoutez aux blocks catch les erreurs
    // pouvant être déclenchées par les opérations sur la pile
    try
    {
        print(stack, taille, nb); // affiche [ [
        push(stack, taille, nb, -17);

        // on affiche l'élément en haut de pile
        std::cout << top(stack, taille, nb) << std::endl; // affiche -17

        print(stack, taille, nb); // affiche [-17 90 [

        int e = pop(stack, taille, nb);
        std::cout << e << std::endl;
        print(stack, taille, nb); // affiche [-17 [

        push(stack, taille, nb, 20);
        push(stack, taille, nb, -78);
        push(stack, taille, nb, -9);
        push(stack, taille, nb, -56);
        push(stack, taille, nb, -9);
        push(stack, taille, nb, 68);
    }
    catch(const std::runtime_error& e)
    {
        std::cout<<"erreur"<<std::endl;
    }
}
   
    