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
        void afficher_graph_matrice();
        void afficher_graph_liste(); 
        void ajout_arete(int a, int b);
        void ajout_sommet();

        //Generation d'un graphe
        void genere_arete_probabilite(float p);
        void genere_graph_triangle();

        // Calcul sur le graph
        int calcul_degre_sommet_matrice(int s);
        int calcul_degre_sommet_liste(int s);

        // Setters et Getters
        int getDegresTotal();
        int getNombreAretes();
        int getNombreSommets();
        
        // BronKerbosch
        void BronKerbosch(vector<int> R, vector<int> P, vector<int> X);


    private:
        int nombre_sommets;
        int ** matrice_adjacence;
        int degres_total;
        map <int,vector<int>>liste_adjacence;
    
    public:
        vector<int> result_cliques;
};

void test_probabilite(int s, int nb, float p);
int demande_nombre();
Graph genere_barabasi_albert();

