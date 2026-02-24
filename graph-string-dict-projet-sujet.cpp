// Un dernier projet sur les graphes.
// Vous devez représenter un graphe sous la forme de liste d'adjacence, constitué de sommets nommés
// et d'arêtes portant une valeur numérique (double) entre ces sommets.

// Dans un graphe sous la forme de liste d'adjacence:
//    - le graphe possède le vecteur de ses sommets;
//    - chaque sommet possède le vecteurs des arêtes dont il est le sommet de départ.

// Vous devez coder les class Vertex, Edge et Graph, avec les consignes suivantes:
//    0) ne mettez pas d'attributs en public
//       ne mettez pas de méthodes pour accéder aux attributs
//       mais utilisez friend au besoin

//    1) les sommets sont identifiés par leurs noms qui sont des std::string

//    2) vous devez utiliser des std::vector pour les listes de sommets et d'arêtes
//       a) Vous devez donc conserver une correspondance entre le nom d'un sommet et son indice dans le graphe
//          pour cela le graphe possède une std::unordered_map<std::string, int> comme montré ci-dessous

//    3) vous utilisez new et delete pour les Vertex et Edge dans le graphe.

//    4) vous devez proposer une méthode de la classe Graph qui lise un graphe écrit dans un fichier
//       comme exemple, regardez la fonction read_graph ci-dessous

//    5) vous devez implémenter un parcours de ce graphe en profondeur (déjà fait en cours)
//       pour stocker les sommets déjà visités utilisez un std::set

//    6) vos devez implémenter une méthode de Graph qui construit la matrice d'adjacence du graphe
//       vous stockez cette matrice comme attribut du graphe
//       utilisez votre class Matrix ou codez-en une

//    7) appliquez à cette matrice d'adjacence l'Algorithme de Floyd-Warshall
//  https://fr.wikipedia.org/wiki/AlgorithmedeFloyd-Warshall
// qui calcule les plus courts chemins entre tous les sommets d'un graphe

//   8) IA générative:
//    a) N'utilisez pas d'IA générative pour générer votre code sauf pour des choses
//       très ciblées/spécifique mais pas pour générer tout un code !
//    b) quand vous faites générer une partie très spécifique de code, vous devez:
//       i) indiquer que c'est de l'IA
//       ii) relire, debugger, tester et donc comprendre exactement tout le code
//       iii) ne pas laisser de construction c++ que vous ne maîtrisez pas

//   9) une fois le programme complètement codé,
//      i) utilisez une IA générative pour générer un code avec les mêmes contraintes que le vôtre
//         mettez ce code dans un fichier du même nom que celui du projet avec "_IA" avant le .cpp ou le .h
//      ii) relisez-le et notez dans le fichier les endroit que vous ne comprenez pas
//          ou qui sont très différents de ce que vous avez utilisé en cours
//      iii) demandez à l'IA de vous expliquer ces endroits et mettez l'explication dans votre fichier
//      Mettez dans votre repo ce ou ces fichiers aussi (avec donc _IA avant le '.' du suffixe '***_IA.cpp" ou "***_IA.h")

// Cette fonction read_triplet lit une suite de triplets:
//           from_1 to_1 value_1 from_2 to_2 value_2 ... from_n to_n value_n
//    où les value_i sont des doubles e.g. 3.14159
//    où from_i et to_i sont des mots SANS espace e.g. Le_Havre mais pas Le Havre ou "Le Havre"
// voir fichier graph0.gr

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>

class Vertex; //pour dire au compilateur que vertex existe, sinon ça ne marche pas

class Edge
{
    Vertex* arrivee;
    double poids;
    Edge(Vertex* dest, double p) {
        arrivee = dest;
        poids = p;

    }
    friend class Vertex;
    friend class Graph;
};
class Vertex
{
    std::string nom;
    std::vector<Edge*> listes_aretes; //vérifier
    Vertex(std::string n) {
        nom = n;
    }
    friend class Graph;
};

class Matrix {
    int taille;
    std::vector<std::vector<double>> grille;
public:
    Matrix(int t) {
        taille = t;
        for (int i = 0; i < taille; i++) {
            std::vector<double> ligne;
            for (int j = 0; j < taille; j++) {
                if (i == j) ligne.push_back(0);
                else ligne.push_back(999999); //on met un chiffre très grand
            }
            grille.push_back(ligne);
        }
    }
    void afficher() {
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                if (grille[i][j] >= 999999) std::cout << "infini ";
                else std::cout << grille[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    friend class Graph;
};

class Graph
{
    std::vector<Vertex*> sommets;
    std::unordered_map<std::string, int> index_noms;
    Matrix* mat_adj;
public:
    Graph() {
        mat_adj = nullptr;
    }

    //destructeur
    ~Graph() {
        for (int i = 0; i < (int)sommets.size(); i++) {
            for (int j = 0; j < (int)sommets[i]->listes_aretes.size(); j++) {
                delete sommets[i]->listes_aretes[j];
            }
            delete sommets[i];
        }
        if (mat_adj != nullptr) delete mat_adj;
    }
    void add_edge(const std::string &de, const std::string &vers, double valeur) {
        if (index_noms.find(de) == index_noms.end()) {
            index_noms[de] = (int)sommets.size();
            sommets.push_back(new Vertex(de));
        }
        if (index_noms.find(vers) == index_noms.end()) {
            index_noms[vers] = (int)sommets.size();
            sommets.push_back(new Vertex(vers));
        }
        int id_de = index_noms[de];
        int id_vers = index_noms[vers];
        sommets[id_de]->listes_aretes.push_back(new Edge(sommets[id_vers], valeur));
    }
    //on fait une fonction récursive pour coder dfs
    void dfs_rec(int actuel, std::set<int>& vus) {
        vus.insert(actuel);
        std::cout<<"visite : "<< sommets[actuel]->nom << std::endl;
        for (int i = 0; i < (int)sommets[actuel]->listes_aretes.size(); i++) {
            Vertex* v = sommets[actuel]->listes_aretes[i]->arrivee;
            int id_v = index_noms[v->nom];
            if (vus.find(id_v) == vus.end()) {
                dfs_rec(id_v, vus);
            }
        }
    }
    void dfs() {
        std::set<int> vus;
        if (sommets.size() > 0) dfs_rec(0, vus);
    }

    void construire_matrice() {
        int n = (int)sommets.size();
        if (mat_adj != nullptr) delete mat_adj;
        mat_adj = new Matrix(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (int)sommets[i]->listes_aretes.size(); j++) {
                Edge* e = sommets[i]->listes_aretes[j];
                int to = index_noms[e->arrivee->nom];
                mat_adj->grille[i][to] = e->poids;
            }
        }
    }

    //Floyd-Warshall 
    void floyd_warshall() {
        construire_matrice();
        int n = (int)sommets.size();
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (mat_adj->grille[i][k] + mat_adj->grille[k][j] < mat_adj->grille[i][j]) {
                        mat_adj->grille[i][j] = mat_adj->grille[i][k] + mat_adj->grille[k][j];
                    }
                }
            }
        }
        mat_adj->afficher();
    }
};

Graph read_triplet(const std::string &filename)
{
    Graph g;
    std::cout << "read_triplet(" << filename << ")" << std::endl;

    // on essaie d'ouvrir le fichier en lecture
    // pour cela on crée un objet de type std::ifstream (input file stream)
    //    et le constructeur ouvre le fichier
    std::ifstream file(filename);

    if (not file.is_open())
    {
        // si le fichier n'a pas pu être ouvert, on s'en va e.g. par une exception
        throw std::runtime_error(std::string("file ") + filename + std::string(" not found"));
    }

    // si on est arrivé là c'est que le fichier est ouvert, on va le lire
    // on sait qu'il contient le graphe sur une ligne sous la forme de triplets: from to value
    // e.g. Paris Lyon 100 Paris Nice 200 Paris ...

    // from, to sont des strings et value un double
    // on réserve trois variables pour lire ces valeurs
    std::string from, to;
    double value;

    while (file >> from >> to >> value) // tant qu'on a un triplet (les 2 strings et l'int) à lire
    // notons que l'expression "file >> var" a comme valeur l'état du fichier après la lecture de var
    {
        std::cout << from << " " << to << " " << value << std::endl;
        g.add_edge(from, to, value);
        // là on l'affiche simplement l'arête, mais il faut l'ajouter au graphe !
        // g.add_vertex(from, to, value);
    }
    std::cout << std::endl;

    file.close(); // on ferme le fichier

    // Attention ça échouera si vous mettez un nom de ville avec un espace (ou une tabulation)
    // (même si vous mettez des " " autour), en effet
    //    - quand une std::string est lue, la lecture se fait jusqu'au premier espace
    //      si vous mettez "Le Havre" ça fera deux mots donc ça échouera
    //      il faudra mettre Le_Havre

    return g;
}

int main()
{

    // LECTURE DU GRAPHE
    Graph graph = read_triplet("graph0.gr");
    graph.dfs();

    // EXEMPLE D'UTILISATION D'UN DICTIONNAIRE STD::UNORDERED_MAP
    // voici un exemple d'utilisation d'un dictionnaire pour stocker:
    //    - comme clé les noms des sommets
    //    - comme valeur son indice dans le vector
    std::unordered_map<std::string, int> srt_to_indice;
    int i = 0;
    // "Paris" "Nice" 350.50
    srt_to_indice["Paris"] = i;
    i = i + 1;

    srt_to_indice["Nice"] = i;
    i = i + 1;

    // ou utilisez auto pour l'inférence de type (le type est généré)
    std::unordered_map<std::string, int>::iterator search_paris = srt_to_indice.find("Paris");
    if (search_paris != srt_to_indice.end())
        std::cout << "found Paris\n"
                  << search_paris->first << ' ' << search_paris->second << '\n';
    else
        std::cout << "Paris not found\n";

    auto search = srt_to_indice.find("Antibes");
    if (search != srt_to_indice.end())
        std::cout << "Antibes found\n"
                  << search->first << ' ' << search->second << '\n';
    else
        std::cout << "Antibes not found\n";

    // On accède à un l'indice d'un sommet
    std::cout << srt_to_indice["Paris"] << std::endl;

    // accès aux éléments du dictionnaire
    for (auto &e : srt_to_indice) // & pour éviter de recopier l'objet
    {
        std::cout << "key: " << e.first
                  << " value: " << e.second << std::endl;
    }

    // 2) accès par std::get<0> et std::get<1>
    // à préférer à first et second
    for (auto &e : srt_to_indice)
    {
        std::cout << "key: " << std::get<0>(e)
                  << " value: " << std::get<1>(e) << std::endl;
    }

    // EXEMPLE D'UTILISATION D'UN STD::SET
    std::set<int> visited;
    visited.insert(2);

    std::set<int>::iterator search_0 = visited.find(0);
    if (search_0 != visited.end())
        std::cout << "Found 0\n";
    else
        std::cout << "0 not found\n";

    std::set<int>::iterator search_2 = visited.find(2);
    if (search_2 != visited.end())
        std::cout << "found 2\n";
    else
        std::cout << "2 not found\n";

    return 0;
}

/*

mettre dans le fichier graph0.gr par exemple
Paris Lyon 100.56 Paris Nice 200.50 Paris Marseille 140.20 Paris Toulouse 200.8
Paris Le_Havre 120 Lyon Nice 80.50 Lyon Marseille 50
Marseille Nice 70 Marseille Toulouse 80 Toulouse Nice 100

*/