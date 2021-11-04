#include <iostream>
#include <time.h>


using namespace std;


class Graph {
    public:
        Graph();
        Graph(int nb_som);
        void afficher_graph(); 
        void ajout_arrete(int a, int b);
        void genere_arrete_probabilite(float p);
        void genere_graph_triangle();
        int calcul_degre_sommet(int s);
        void genere_barabasi_albert(int a);

    private:
        int nombre_sommets;
        int ** matrice_adjacence;
        int degres_total;
};


