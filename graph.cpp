#include "graph.h"

using namespace std;

// méthodes de la classe Triplet 


Lien::Lien()
{}

Lien::Lien(int d, int a)
{
    sommet_depart = d;
    sommet_arrive = a;
}

void Lien::afficher_lien() 
{
    cout << "[" << sommet_depart << "-" << sommet_arrive << "]";
}

// méthodes de la classe Graph

Graph::Graph()
{}

Graph::Graph(int nb_som, int * som, int nb_transi, Lien * transi)
{
    nombre_sommets = nb_som;
    sommets = som;
    nombre_transitions = nb_transi;
    transitions = transi;
}

void Graph::afficher_graph()
{
    cout << "Graph :" << endl << "Sommets = ";
    for(int i=0; i<nombre_sommets; i++) {
        cout << sommets[i] << " ";
    }
    cout << endl << "D = ";
    for(int i=0; i<nombre_transitions; i++) {
        transitions[i].afficher_lien();
        cout << " ";
    }
    cout << endl;
}


int main() {
    
    Lien l= Lien(1,2);
    Lien l2= Lien(3,2);
    l.afficher_lien();
    l2.afficher_lien();
    int sommets[4] = {0,1,2,3};

    Lien tab[2] = {l,l2};

    Graph g = Graph(4, sommets,2,tab);
    g.afficher_graph();

    return 0;
}