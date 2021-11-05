#include "graph.h"

using namespace std;

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
    degres_total+=2;
}

int Graph::getDegresTotal()
{
    return degres_total;
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


int Graph::getNombreArretes()
{
    return degres_total/2;
}

int Graph::getNombreSommets()
{
    return nombre_sommets;
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
        /*cout << i << "," << s << endl;*/
        if(matrice_adjacence[s][i]==1)
        {
            compteur++;
        }
    }
    return compteur;
}

void Graph::ajout_sommet()
{
    nombre_sommets = nombre_sommets+1;
    int **tab = new int*[nombre_sommets];
    for(int i = 0; i < nombre_sommets; ++i) {
        tab[i] = new int[nombre_sommets];
    }

    for(int i=0; i<nombre_sommets-1; i++) {
        for(int j=0; j<nombre_sommets-1; j++) {
            tab[i][j]=matrice_adjacence[i][j];
        }
    }
    for(int i=nombre_sommets-1; i<nombre_sommets; i++) {
        for(int j=nombre_sommets-1; j<nombre_sommets; j++) {
            tab[i][j]=0;
        }
    }

    matrice_adjacence = tab;
}

Graph genere_barabasi_albert()
{
    int ans = 0;

    Graph g1 = Graph();
    g1.genere_graph_triangle();

    cout << "Tapez un nombre m positif (-1 pour arreter)" << endl; // (nb d'arrete max a ajouter lors d'une generation)
    cin >> ans;

    while (ans != -1)
    {
        g1.ajout_sommet();
        for (int j = 0; j < g1.getNombreSommets()-1; j++)
        {
            float p = float (g1.calcul_degre_sommet(j)) / float (g1.getDegresTotal()) * 100;
            float random = float(rand()%100);
            //cout << "r: " << random << ", p: " << p << endl;
            if(random <= p && ans>0) {
                g1.ajout_arrete(g1.getNombreSommets()-1,j);
                ans--;
            }
        }
        cout << "Tapez un nombre m positif (-1 pour arreter)" << endl; // (nb d'arrete max a ajouter lors d'une generation)
        cin >> ans;
    }
    return g1;
}


void test_probabilite(int sommets, int nombre_test, float proba)
{
    float valeur_test = 0.0;

    for(int i=0; i<nombre_test ; i++){
        Graph g = Graph(sommets);
        g.genere_arrete_probabilite(proba);
        float nb_arrete_max = float((sommets*(sommets-1))/2);
        valeur_test += float(g.getNombreArretes()/nb_arrete_max);
    }
    valeur_test = (valeur_test/nombre_test);
    cout << nombre_test << " tests - proba attendue : " << proba << " obtenue : " << valeur_test << endl;  
    float taux_erreur= (abs(valeur_test-proba)/proba)*100;
    cout << "taux d'erreur : " << taux_erreur << "%" << endl;
}



int main() {
    srand(time(NULL));

    Graph g = Graph();
    g = genere_barabasi_albert();
    g.afficher_graph();

    return 0;
}
