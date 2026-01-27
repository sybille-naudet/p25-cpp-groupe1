#include <vector>
#include <iostream>


// struct edge;
struct vertex;


struct edge {
    double value;
    vertex *begin;
    vertex *end;
    edge(vertex *b, vertex *e, double v) {
        begin=b;
        end=e;
        value=v;
    }
};


struct vertex { //sommet
    int name;
    std::vector<edge*> edge_;
    vertex(int vect) : name(vect) {}
    
    void add_edge(edge *empl) {
        edge_.push_back(empl);
    }
};

struct graph { //graphique
    std::vector<vertex*>v;

    void add_vertex(int i){
        if ((int)v.size() <= i) {
            for (int j=v.size(); j<=i; j=j+1) {
                v.push_back(new vertex(j));
            }
        }
    }

    void add_edge(int b, int e, double val){
        add_vertex(b);
        add_vertex(e);
        //crée arête + ajoute sur sommet de départ
        edge* new_edge=new edge(v[b], v[e], val);
        v[b]->add_edge(new_edge);

    }



    void print() {
        //boucle partout
        for (int i = 0; i < v.size(); i=i+1) {
            for (int j = 0; j < v[i]->edge_.size(); j++) {
                edge* e = v[i]->edge_[j];
                std::cout << e->begin->name;
                std::cout << " - ";
                std::cout << e->value;
                std::cout << " -> ";
                std::cout << e->end->name << std::endl;
            }
        }
    }
};



int main() {
    graph g;
    g.add_edge(2,5,17.9);
    g.add_edge(5,3,23.9);
    g.add_edge(3,4,16.9);
    g.add_edge(4,0,699.9);
    g.print();
}