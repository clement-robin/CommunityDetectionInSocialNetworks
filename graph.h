#include <iostream>
#include <time.h>


using namespace std;


class Graph {
    public:
        // Fonction de base pour le graphe
        Graph();
        Graph(int nb_som);
        void afficher_graph(); 
        void ajout_arrete(int a, int b);
        void ajout_sommet();

        //Generation d'un graphe
        void genere_arrete_probabilite(float p);
        void genere_graph_triangle();

        // Calcul sur le graph
        int calcul_degre_sommet(int s);

        // Setters et Getters
        int getDegresTotal();
        int getNombreArretes();
        int getNombreSommets();


    private:
        int nombre_sommets;
        int ** matrice_adjacence;
        int degres_total;
};

void test_probabilite(int s, int nb, float p);
int demande_nombre();
Graph genere_barabasi_albert();

