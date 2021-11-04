#include "graph.h"

using namespace std;

// méthodes de la classe Graph

Graph::Graph()
{
    nombre_sommets = 0;
    degres_total=0;
}

Graph::Graph(int nb_som)
{
    nombre_sommets = nb_som;
    degres_total=0;
    int **tab = new int*[nombre_sommets];
    for(int i = 0; i < nombre_sommets; ++i) {
        tab[i] = new int[nombre_sommets];
    }

    for(int i=0; i<nombre_sommets; i++) {
        for(int j=0; j<nombre_sommets; j++) {
            tab[i][j]=0;
        }
    }
    matrice_adjacence = tab;
}

void Graph::afficher_graph()
{
    cout << "Graph :" << endl << endl;
    for(int i=0; i<nombre_sommets; i++) {
        for(int j=0; j<nombre_sommets; j++) {
            cout << matrice_adjacence[i][j]<< " " ;
        }
        cout << endl;
    }
    cout << "Degres total = " << degres_total << endl;
}

void Graph::ajout_arrete(int a, int b) 
{
    matrice_adjacence[a][b]=1;
    matrice_adjacence[b][a]=1;
    degres_total++;
}

void Graph::genere_arrete_probabilite(float p)
{
    for(int i=0; i<nombre_sommets; i++) {
        for(int j=0; j<i+1; j++) {
            if(j!=i) {
                float random = float(rand()%100);
                if(random<p*100.0) {
                    this->ajout_arrete(i,j);
                }
            }
        }
    } 
}


void Graph::genere_graph_triangle()
{
    Graph g = Graph(3);
    nombre_sommets = 3;
    g.genere_arrete_probabilite(1.0);
    matrice_adjacence = g.matrice_adjacence;
    degres_total = g.degres_total;

}


int Graph::calcul_degre_sommet(int s)
{
    int compteur=0;
    for(int i=0; i<nombre_sommets ; i++) {
        cout << i << "," << s << endl;
        if(matrice_adjacence[s][i]==1)
        {
            compteur++;
        }
    }
    return compteur;
}


void Graph::genere_barabasi_albert(int arrete_max)
{
    Graph g = Graph();
    g.genere_graph_triangle();
/*  fixe nombre sommet
    (parcourt en triangle)
    boucle de 3 jusqua a (nouvelles arretes)
        ajout un noeud
        proba noeud arret avec le noeud n = degre noeud n / degre total
*/

    
}




int main() {
    srand(time(NULL));
    Graph g = Graph();
    g.genere_graph_triangle();

    g.afficher_graph();
    int val = g.calcul_degre_sommet(2);
    cout << "val = " << val << endl; 
    return 0;
}
