#include "graph.h"

using namespace std;

/**
 * Constructeur par defaut de la classe Graph
 */
Graph::Graph()
{
    nombre_sommets = 0;
    degres_total = 0;
    nombre_cliqueMax = 0;
}

/**
 * Constructeur de la classe Graph
 * Parametre(s) : nb_som - nombre de sommets voulu pour notre graphe
 */
Graph::Graph(int nb_som)
{
    nombre_sommets = nb_som;
    degres_total = 0;
    nombre_cliqueMax = 0;

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

    for (int i = 0; i < nb_som; i++)
    {
        vector<int> v (0, {});
        liste_adjacence.insert ( std::pair <int,vector<int>>(i,v) );
    }
}

/**
 * Fonction d'affichage du Graph dans la console avec sa matrice d'adjacence et le nombre de degres totals
 */
void Graph::afficher_graph_matrice()
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

void Graph::afficher_graph_liste()
{
    map<int, vector<int>>::iterator p;

    cout << "Graph :" << endl << endl;
    for(p = liste_adjacence.begin(); p != liste_adjacence.end(); p++)
    {
        cout << p->first << " : ";
        for (long unsigned int i = 0; i < p->second.size(); i++)
        {
            cout << p->second[i] << " ";
        }
        cout << endl;
        
    }
    cout << endl;
}

/* affichage liste_cliqueMax */

void Graph::afficher_cliqueMax(){

    map<int, vector<int>>::iterator p;
    for(p = liste_cliqueMax.begin(); p != liste_cliqueMax.end(); p++)
    {
        cout << "clique "<< p->first << " : ";
        for (long unsigned int i = 0; i < p->second.size(); i++)
        {
            cout << p->second[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * Fonction qui ajoute une arete au Graph entre les 2 sommets donnes en paramatres
 * puis ajoute 2 degres totals en plus de ceux existants
 * Parametre(s) : a - sommets 1
 *                b - sommets 2
 */
void Graph::ajout_arete(int a, int b) 
{
    matrice_adjacence[a][b]=1;
    matrice_adjacence[b][a]=1;
    degres_total+=2;
    map<int, vector<int>>::iterator iteratorCle;

    auto search = liste_adjacence.find(a);

    vector<int>::iterator iteratorValeur;
    iteratorValeur = search->second.end();
    search->second.insert(iteratorValeur, b);

    search = liste_adjacence.find(b);

    iteratorValeur = search->second.end();
    search->second.insert(iteratorValeur, a); 
}

/**
 * Fonction qui genere un Graph avec une probabilité d'avoir une arete entre 2 sommets donnes en parametres
 * a partir d'un graph sans arete
 * Parametre(s) : p - probabilité entre 0 et 1 
 */
void Graph::genere_arete_probabilite(float p)
{
    for(int i=0; i<nombre_sommets; i++) {
        for(int j=0; j<i+1; j++) {
            if(j!=i) {
                float random = float(rand()%100);
                if(random<p*100.0) {
                    this->ajout_arete(i,j);
                }
            }
        }
    } 
}

/**
 * Fonction qui genere un Graph triangle :
 * Graph complet a 3 sommets
 */
void Graph::genere_graph_triangle()
{
    Graph g = Graph(3);
    nombre_sommets = 3;
    g.genere_arete_probabilite(1.0);
    matrice_adjacence = g.matrice_adjacence;
    liste_adjacence = g.liste_adjacence;
    degres_total = g.degres_total;
}

/**
 * Fonction qui compte le nombre de degres pour un sommet donne en parametre du Graph
 * Parametre(s) : s - sommet dont on souhaite connaitre le degre
 * return : compteur : nombre de degre du sommet
 */
int Graph::calcul_degre_sommet_matrice(int s)
{
    int compteur=0;
    for(int i=0; i<nombre_sommets ; i++) {
        if(matrice_adjacence[s][i]==1)
        {
            compteur++;
        }
    }
    return compteur;
}

/**
 * Fonction qui compte le nombre de degres pour un sommet donne en parametre du Graph
 * Parametre(s) : s - sommet dont on souhaite connaitre le degre
 * return : compteur : nombre de degre du sommet
 */
int Graph::calcul_degre_sommet_liste(int s)
{    
    auto search = liste_adjacence.find(s);
    return search->second.size();
}


/**
 * Fonction qui ajout un sommet a un Graph
 * Parametre(s) : p - probabilité entre 0 et 1 
 */
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

    vector<int> v (0, {});
    int s = liste_adjacence.size();

    liste_adjacence.insert ( std::pair <int,vector<int>>(s,v) );
}

/**
 * Getter du champ degres_total
 * return : degres_total - nombre de degres total du Graph
 */
int Graph::getDegresTotal()
{
    return degres_total;
}

/**
 * Getter du champ degres_total/2 car un arete implique d'avoir 2 degres
 * return : degres_total/2 - nombre d'arete total du Graph
 */
int Graph::getNombreAretes()
{
    return degres_total/2;
}

/**
 * Getter du champ nombre_sommets
 * return : nombre_sommets - nombre de nombre_sommets du Graph
 */
int Graph::getNombreSommets()
{
    return nombre_sommets;
}

int Graph::getNombreCliqueMax()
{
    return nombre_cliqueMax;
}

void Graph::AddListeCliqueMax(vector<int>clique)
{
    liste_cliqueMax.insert ( std::pair <int,vector<int>>(nombre_cliqueMax,clique) );
    nombre_cliqueMax++;
}

/**
 * Fonction qui demande a l'utilisateur de saisir un nombre positif et qui le retourne
 * return : ans - nombre saisi par l'utilisateur
 */
int demande_nombre()
{
    int ans = 0;
    cout << "Tapez un nombre m positif (-1 pour arreter)" << endl; // (nb d'aretes max a ajouter lors d'une generation)
    cin >> ans;
    return ans;
}

/**
 * Fonction qui genere un Graph avec une probabilité d'avoir une arete entre 2 sommets selon le modele de Barabasi-Albert
 * a partir d'un graph sans arete
 */
Graph genere_barabasi_albert()
{
    int ans = demande_nombre();

    Graph g1 = Graph();
    g1.genere_graph_triangle();

    while (ans != -1)
    {
        g1.ajout_sommet();
        for (int j = 0; j < g1.getNombreSommets()-1; j++)
        {
            float p = float (g1.calcul_degre_sommet_liste(j)) / float (g1.getDegresTotal()) * 100;
            float random = float(rand()%100);
            if(random <= p && ans>0) {
                g1.ajout_arete(g1.getNombreSommets()-1,j);
                ans--;
            }
        }
        ans = demande_nombre();
    }
    return g1;
}

/**
 * Fonction qui test si les probabilites sont bien respecte lors d'une generation de graph avec la fonction genere_arete_probabilite(p)
 * Cette fonction genere un nombre de Graph donne en parametre de taille donnee en parametre
 * le probabilite d'obtenir une arete entre 2 sommet est aussi donne en parametre
 * Le taux d'erreur entre la probabilite et le resultat est afficher
 * Parametre(s) : sommets - taille des graphes voulu
 *                nombre_test - nombre de graph que l'on souhaite generer
 *                proba - probabilité entre 0 et 1  
 */
void test_probabilite(int sommets, int nombre_test, float proba)
{
    float valeur_test = 0.0;

    for(int i=0; i<nombre_test ; i++){
        Graph g = Graph(sommets);
        g.genere_arete_probabilite(proba);
        float nb_aretes_max = float((sommets*(sommets-1))/2);
        valeur_test += float(g.getNombreAretes()/nb_aretes_max);
    }
    valeur_test = (valeur_test/nombre_test);
    cout << nombre_test << " tests - proba attendue : " << proba << " obtenue : " << valeur_test << endl;  
    float taux_erreur= (abs(valeur_test-proba)/proba)*100;
    cout << "taux d'erreur : " << taux_erreur << "%" << endl;
}





