
class Stack {
    private : 
    int size;
    int nb;
    int* tab;
    public : 
    Stack (int s) : nb(0){
        size = s;
        tab = new int[size];
    }

    ~Stack (){
        delete [] tab;
    }

    //constructeur de copie
    Stack(const Stack& m):
        size(m.size),
        nb(m.nb),
        tab(new int[m.size])
        {
            for (int i=0; i<nb; i++) {
                tab[i] = m.tab[i];
            }
        }
    //affectation
    Stack& operator=(const Stack& s) {
        if (this != &s) {
            delete[] tab;
            size = s.size;
            nb = s.nb;
            tab = new int[size];
            for (int i = 0; i < nb; i++) {
                tab[i] = s.tab[i];
            }
        }
        return *this;
    }


//fonctions codées à un cours précédent   
    bool is_full() {
        return nb >= size;
    }
    void push(int v) {
        if (is_full()){
            return;
        }
        tab[nb] = v;
        nb = nb + 1;
        }
};


int main(){
    Stack* ps = new Stack(2000);
    ps->push(-17);
    delete ps;
    ps;
    return 0;
}