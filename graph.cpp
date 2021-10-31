#include "graph.h"

using namespace std;

// méthodes de la classe Triplet 


Triplet::Triplet()
{}

Triplet::Triplet(int d, char c, int a)
{
    sommet_depart = d;
    valeur = c;
    sommet_arrive = a;
}

void Triplet::afficher_triplet() 
{
    cout << "[" << sommet_depart << "-" << valeur << "-" << sommet_arrive << "]";
}

// méthodes de la classe Graph

Graph::Graph()
{}

Graph::Graph(int * som, int init, int * accept, Triplet * transi)
{
    sommets = som;
    etat_initial = init;
    etats_accepteurs = accept;
    transitions = transi;
}

void Graph::afficher_graph()
{
    cout << "Graph :" << endl << "Q = ";
    for(int i=0; i<4; i++) {
        cout << sommets[i] << " ";
    }
    cout << endl << "s = " << etat_initial << endl << "F = ";
    for(int i=0; i<2; i++) {
        cout << etats_accepteurs[i] << " ";
    }
    cout << endl << "D = ";
    for(int i=0; i<2; i++) {
        transitions[i].afficher_triplet();
        cout << " ";
    }
    cout << endl;
}


int main() {
    
    Triplet t= Triplet(1,'a',2);
    Triplet t2= Triplet(3,'a',2);

    int sommets[4] = {0,1,2,3};
    int accepteurs[2] = {2,3};
    Triplet tab[2] = {t,t2};

    Graph g = Graph(sommets,0,accepteurs,tab);
    g.afficher_graph();

    return 0;
}