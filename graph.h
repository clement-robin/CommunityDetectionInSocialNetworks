#include <iostream>
#include <time.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {

    public:
        // Fonction de base pour le graphe
        Graph();
        Graph(int nb_som);
        //void afficher_graph_matrice();
        void afficher_graph_liste();
        void afficher_cliqueMax(); 
        void ajout_arete(int a, int b);
        void ajout_sommet();
        void suppr_sommet(int sommet);

        //Generation d'un graphe
        void genere_arete_probabilite(float p);
        void genere_graph_triangle();

        // Calcul sur le graph
        //int calcul_degre_sommet_matrice(int s);
        int calcul_degre_sommet_liste(int s);

        // Setters et Getters
        int getDegresTotal();
        int getNombreAretes();
        int getNombreSommets();
        int getNombreCliqueMax();
        map <int,vector<int>>getListeAdjacence();
        vector<int> getResultCliques();
        vector<int> getOrdreDegenerescence();
        map <int,vector<int>> getListeCliqueMax();

        void setResultCliques(vector<int> resultcliques);
        void setOrdreDegenerescence(vector<int> ordredegenerescence);

        void AddListeCliqueMax(vector<int>clique);
        
        // BronKerbosch
        void BronKerbosch(vector<int> R, vector<int> P, vector<int> X);

        // BronKerboschPivot
        void BronKerboschPivot(vector<int> R, vector<int> P, vector<int> X);

        // BronKerboschDegenerescence
        vector <int> triOrdreDegenerescence();
        void genOrdreDegenerescence();
        void BronKerboschDegenerescence();

    private:
        int nombre_sommets;
        //int ** matrice_adjacence;
        int degres_total;
        int nombre_cliqueMax;
        map <int,vector<int>>liste_adjacence;
        map <int,vector<int>>liste_cliqueMax;
        vector<int> result_cliques;
        vector<int> ordre_degenerescence;
        
};

void test_probabilite(int s, int nb, float p);
int demande_nombre();
Graph genere_barabasi_albert();
map<int,vector<int>> Algorithm1(Graph g);
map<int,vector<int>> Algorithm2(Graph g);