#include <iostream>
struct Buffer
{
    int size;
    int compteur;
    double* tab;

    Buffer(int s) : size(s)
    {
        compteur = 0;
        tab = new double[s];
    }

    ~Buffer()
    {
        delete[] tab;
    }
};

struct Matrix
{
    int Ligne;
    int Colonne;
    Buffer* B;

    Matrix(int l, int c) : Ligne(l), Colonne(c)
    {
        int size = l*c;
        B = new Buffer(size);
        B->compteur += 1;
    }

    Matrix(int l, int c, Buffer* b) : Ligne(l), Colonne(c), B(b)
    {
        B->compteur += 1;
    } 

    ~Matrix()
    {
        B->compteur -= 1;
        if (B->compteur == 0)
        {
            delete B;
        }
    }

    void print()
    {
        for (int i = 0; i<Ligne; i++)
        {
            for(int j = 0; j<Colonne; j++)
            {
                std::cout<< B->tab[i*Colonne+j] << " ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }

    double get(int i, int j)
    {
        return B->tab[i*Colonne+j];
    }

    void set(int i, int j, double v)
    {
        B->tab[i*Colonne+j]=v;
    }

    Matrix reshape(int i, int j)
    {
        return Matrix(i, j, B);
    }
};

int main()
{
    Matrix m(4,3);
    m.set(0,0,17.3);
    double d = m.get(0,0);
    m.print();
    Matrix h = m.reshape(2,6);
    h.set(0,0,21.3);
    m.print();
    h.print();
    return 0;
}