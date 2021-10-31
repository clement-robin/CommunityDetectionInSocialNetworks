#include <iostream>
#define TAILLE 50

using namespace std;


class Triplet {
    public:
        Triplet();
        Triplet(int d, char c, int a);
        void afficher_triplet();

    private:
        int sommet_depart;
        char valeur;
        int sommet_arrive;
};

class Graph {
    public:
        Graph();
        Graph(int * som, int init, int * accept, Triplet * transi);
        void afficher_graph();  

    private:
        int * sommets;
        int etat_initial;
        int * etats_accepteurs;
        Triplet * transitions;
};