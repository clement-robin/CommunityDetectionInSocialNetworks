#include <iostream>
#include <time.h>


using namespace std;


class Graph {
    public:
        // fonction de base pour le graphe
        Graph();
        Graph(int nb_som);
        void afficher_graph(); 
        void ajout_arrete(int a, int b);
        void ajout_sommet();

        // generation d'un graphe
        void genere_arrete_probabilite(float p);
        void genere_graph_triangle();

        int calcul_degre_sommet(int s);

        // setters et getters
        int getDegresTotal();
        int getNombreArretes();
        int getNombreSommets();


    private:
        int nombre_sommets;
        int ** matrice_adjacence;
        int degres_total;
};

void test_probabilite(int s, int nb, float p);
Graph genere_barabasi_albert();

