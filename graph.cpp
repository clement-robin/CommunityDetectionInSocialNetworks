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
 * @param nb_som nombre de sommets voulu pour notre graphe
 */
Graph::Graph(int nb_som)
{
    nombre_sommets = nb_som;
    degres_total = 0;
    nombre_cliqueMax = 0;

    for (int i = 0; i < nb_som; i++)
    {
        vector<int> v (0, {});
        liste_adjacence.insert ( std::pair <int,vector<int>>(i,v) );
    }
}

/**
 * Fonction d'affichage du Graph dans la console de sa liste d'adjacence
 */
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

/**
 * Fonction d'affichage du Graph dans la console de toutes les clique max du graphe
 */
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
 * @param a sommets 1
 * @param b sommets 2
 */
void Graph::ajout_arete(int a, int b) 
{
    map<int, vector<int>>::iterator iteratorCle;

    auto search = liste_adjacence.find(a);

    vector<int>::iterator iteratorValeur;
    iteratorValeur = search->second.end();
    search->second.insert(iteratorValeur, b);

    search = liste_adjacence.find(b);

    iteratorValeur = search->second.end();
    search->second.insert(iteratorValeur, a); 

    degres_total+=2;
}

/**
 * Fonction qui genere un Graph avec une probabilité d'avoir une arete entre 2 sommets donnes en parametres
 * a partir d'un graph sans arete
 * @param p probabilité entre 0 et 1 
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
 * Graphe complet a 3 sommets
 */
void Graph::genere_graph_triangle()
{
    Graph g = Graph(3);
    nombre_sommets = 3;
    g.genere_arete_probabilite(1.0);
    liste_adjacence = g.liste_adjacence;
    degres_total = g.degres_total;
}

/**
 * Fonction qui compte le nombre de degres pour un sommet donne en parametre du Graph
 * @param s sommet dont on souhaite connaitre le degre
 * @return int compteur : nombre de degre du sommet
 */
int Graph::calcul_degre_sommet_liste(int s)
{    
    auto search = liste_adjacence.find(s);
    return search->second.size();
}


/**
 * Fonction qui ajout un sommet a un Graph
 * @param 
 */
void Graph::ajout_sommet()
{
    nombre_sommets = nombre_sommets+1;
    vector<int> v (0, {});
    int s = liste_adjacence.size();

    liste_adjacence.insert ( std::pair <int,vector<int>>(s,v) );
}


// Supprimer un sommet dans un graphe;
void Graph::suppr_sommet(int sommet)
{
    auto search = liste_adjacence.find(sommet);

    degres_total = degres_total - (2*search->second.size());

    for (long unsigned int i = 0; i < search->second.size(); i++)
    {
        for (long unsigned int j = 0; j < liste_adjacence[search->second[i]].size(); j++) 
        {
            if (liste_adjacence[search->second[i]][j] == sommet)
            {
                liste_adjacence[search->second[i]].erase(liste_adjacence[search->second[i]].begin()+j);
            }     
        }   
    } 
    liste_adjacence.erase(sommet); 
}

/**
 * Getter du champ degres_total
 * @return int degres_total : nombre de degres total du Graph
 */
int Graph::getDegresTotal()
{
    return degres_total;
}

/**
 * Getter du champ degres_total/2 car un arete implique d'avoir 2 degres
 * @return int degres_total/2 : nombre d'arete total du Graph
 */
int Graph::getNombreAretes()
{
    return degres_total/2;
}

/**
 * Getter du champ nombre_sommets
 * @return int nombre_sommets : nombre de sommets du Graph
 */
int Graph::getNombreSommets()
{
    return nombre_sommets;
}

/**
 * Getter du champ nombre_cliqueMax
 * @return int nombre_cliqueMax : nombre de cliques max du Graph
 */
int Graph::getNombreCliqueMax()
{
    return nombre_cliqueMax;
}

/**
 * Fonction qui ajoute une clique à la liste des cliques max du Graph
 * @param clique liste de sommets formant une clique

 */
void Graph::AddListeCliqueMax(vector<int>clique)
{
    liste_cliqueMax.insert ( std::pair <int,vector<int>>(nombre_cliqueMax,clique) );
    nombre_cliqueMax++;
}

map <int,vector<int>> Graph::getListeAdjacence()
{
    return liste_adjacence;
}

vector<int> Graph::getResultCliques()
{
    return result_cliques;
}

vector<int> Graph::getOrdreDegenerescence()
{
    return ordre_degenerescence;
}

void Graph::setResultCliques(vector<int> resultcliques)
{
    result_cliques = resultcliques;
}

void Graph::setOrdreDegenerescence(vector<int> ordredegenerescence)
{
    ordre_degenerescence = ordredegenerescence;
}

map <int,vector<int>> Graph::getListeCliqueMax()
{
    return liste_cliqueMax;
}

/**
 * Fonction qui demande a l'utilisateur de saisir un nombre positif et qui le retourne
 * @return int ans : nombre saisi par l'utilisateur
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
 * a partir d'un graph triangle
 * @return Graph g1 : graphe généré selon la methode de Barabasi-Albert
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
 * @param sommets taille des graphes voulu
 * @param nombre_test nombre de graph que l'on souhaite generer
 * @param proba probabilité entre 0 et 1  
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





