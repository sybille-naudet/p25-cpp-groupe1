
struct Stack {
    int size;
    int nb;
    int* tab;
    Stack (int s) : nb(0){
        size = s;
        tab = new int[size];
    }

    ~Stack (){
        delete [] tab;
    }

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