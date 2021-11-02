#include <iostream>
#define TAILLE 50

using namespace std;


class Lien {
    public:
        Lien();
        Lien(int d, int a);
        void afficher_lien();

    private:
        int sommet_depart;
        int sommet_arrive;
};

class Graph {
    public:
        Graph();
        Graph(int nb_som, int * som, int nb_transi, Lien * transi);
        void afficher_graph();  

    private:
        int nombre_sommets;
        int * sommets;
        int nombre_transitions;
        Lien * transitions;
};