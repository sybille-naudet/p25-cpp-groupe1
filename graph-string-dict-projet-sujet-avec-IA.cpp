#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <set>
#include <limits>

// Valeur pour représenter l'infini dans la matrice
const double INF = std::numeric_limits<double>::infinity();

class Edge;
class Graph;

class Vertex {
    std::string name;
    std::vector<Edge*> edges;

    Vertex(std::string n) : name(n) {}
    ~Vertex(); // Sera défini plus tard pour supprimer les Edges

    friend class Graph;
};

class Edge {
    int to_index; // Indice du sommet de destination dans le vecteur du Graph
    double weight;

    Edge(int to, double w) : to_index(to), weight(w) {}

    friend class Graph;
    friend class Vertex;
};

class Matrix {
    std::vector<std::vector<double>> data;
    int size;

public:
    Matrix(int s) : size(s), data(s, std::vector<double>(s, INF)) {
        for(int i = 0; i < size; ++i) data[i][i] = 0;
    }

    void set(int i, int j, double val) { data[i][j] = val; }
    double get(int i, int j) const { return data[i][j]; }
    int getSize() const { return size; }
};

class Graph {
    std::vector<Vertex*> vertices;
    std::unordered_map<std::string, int> nameToIndex;
    Matrix* adjacencyMatrix;

public:
    Graph() : adjacencyMatrix(nullptr) {}
    ~Graph() {
        for (Vertex* v : vertices) delete v;
        delete adjacencyMatrix;
    }

    void addEdge(const std::string& from, const std::string& to, double weight) {
        int fromIdx = getOrAddVertex(from);
        int toIdx = getOrAddVertex(to);
        vertices[fromIdx]->edges.push_back(new Edge(toIdx, weight));
    }

    int getOrAddVertex(const std::string& name) {
        if (nameToIndex.find(name) == nameToIndex.end()) {
            nameToIndex[name] = vertices.size();
            vertices.push_back(new Vertex(name));
        }
        return nameToIndex[name];
    }

    // Parcours en profondeur (DFS)
    void DFS(int startIdx, std::set<int>& visited) {
        if (visited.find(startIdx) != visited.end()) return;
        
        visited.insert(startIdx);
        std::cout << "Visité : " << vertices[startIdx]->name << std::endl;

        for (Edge* e : vertices[startIdx]->edges) {
            DFS(e->to_index, visited);
        }
    }

    // Construction de la matrice et Floyd-Warshall
    void computeFloydWarshall() {
        int n = vertices.size();
        if (adjacencyMatrix) delete adjacencyMatrix;
        adjacencyMatrix = new Matrix(n);

        // Remplissage initial
        for (int i = 0; i < n; ++i) {
            for (Edge* e : vertices[i]->edges) {
                adjacencyMatrix->set(i, e->to_index, e->weight);
            }
        }

        // Cœur de l'algorithme
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    double dist = adjacencyMatrix->get(i, k) + adjacencyMatrix->get(k, j);
                    if (dist < adjacencyMatrix->get(i, j)) {
                        adjacencyMatrix->set(i, j, dist);
                    }
                }
            }
        }
    }
};

// Nettoyage des Edges dans le destructeur de Vertex
Vertex::~Vertex() {
    for (Edge* e : edges) delete e;
}