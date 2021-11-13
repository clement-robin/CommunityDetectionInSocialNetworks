#include "bronkerbosch.h"

/**
 * La fonction BronKerbosch perlet de trouver toutes les cliques max du graphe
 * selon la méthode de Bron-Kerbosch
 * @param R une ensemble de sommet
 * @param P ensemble de sommet avec une partie de R
 * @param X ensemble de sommet avec aucun sommet de R
 */
void Graph::BronKerbosch(vector<int> R, vector<int> P, vector<int> X){

    if (P.empty() && X.empty()){
        AddListeCliqueMax(R);
    }

    vector<int> Pparcours = P;

    // Pour chaque sommet de P
    for (long unsigned int sommet = 0; sommet<Pparcours.size(); sommet++){

        vector<int> intersectionP = {};
        vector<int> intersectionX = {};
        vector<int> unionR = {};

        int v = Pparcours[sommet];
        auto search = liste_adjacence.find(v);
        
        // Pour chaque voisin de "sommet"
        for (long unsigned int i = 0; i<search->second.size(); i++)
        {   
            // Création de l'intersection P
            for (long unsigned int j = 0; j < P.size(); j++)
            {
                if (P[j] == search->second[i]){
                    intersectionP.push_back(P[j]);
                }
            }

            // Création de l'intersection X
            for (long unsigned int j = 0; j < X.size(); j++)
            {
                if (search->second[i] == X[j]){
                    intersectionX.push_back(X[j]);
                }
            }
        }

        unionR = R;
        unionR.push_back(v);
        BronKerbosch(unionR,intersectionP,intersectionX);
        P.erase(remove(P.begin(),P.end(),v),P.end());
        X.push_back(v);
    }
}


/**
 * La fonction BronKerboschPivot permet de trouver toutes les cliques max du graphe
 * selon la méthode de Bron-Kerbosch mais cette fois-ci en utilisant un pivot
 * @param R une ensemble de sommet
 * @param P ensemble de sommet avec une partie de R
 * @param X ensemble de sommet avec aucun sommet de R
 */
void Graph::BronKerboschPivot(vector<int> R, vector<int> P, vector<int> X)
{
    vector<int> PuX = {};
    vector<int> P_Nu = {};

    int u = -1;
    int val = 0;
    int max = 0;
    
    if (P.empty() && X.empty())
    {
        AddListeCliqueMax(R);
    }
    
    // Construire le vecteur PuX 
    for (long unsigned int i = 0; i < P.size(); i++)
    {
        PuX.push_back(P[i]);
    }
    for (long unsigned int i = 0; i < X.size(); i++)
    {   
        if(!count(P.begin(), P.end(), X[i])){
            PuX.push_back(X[i]);
        }
    }

    if (!P.empty()) 
    {
        u = P[0];
    }
    else if (!X.empty()) 
    {
        u = X[0];
    }

    // Choisir un sommet u dans P U X tel que le nombre de sommet en commun entre P et les voisins de u soit maximal
    for (long unsigned int i = 0; i < PuX.size(); i++)
    {
        auto search = liste_adjacence.find(PuX[i]);
        for (long unsigned int j = 0; j < search->second.size(); j++)
        {
            for (long unsigned int k = 0; k < P.size(); k++)
            {
                if (search->second[j]==P[k])
                {
                    val++;
                }
            }
        }
        if (val>max)
        {
            max = val;
            val = 0;
            u = PuX[i];
        }
    }

    // Creation de P \ N(u)
    bool ajout = true;
    auto search = liste_adjacence.find(u);
    for (long unsigned int i = 0; i < P.size(); i++)
    {
        for (long unsigned int j = 0; j < search->second.size(); j++)
        {
            if (P[i]==search->second[j])
            {
                ajout = false;
            }
        }
        if (ajout)
        {
            P_Nu.push_back(P[i]);
        }
        ajout = true;
    }

    // Pour chaque sommet de P \ N(u)
    for (long unsigned int sommet = 0; sommet<P_Nu.size(); sommet++){

        vector<int> intersectionP = {};
        vector<int> intersectionX = {};
        vector<int> unionR = {};

        int v = P_Nu[sommet];
        auto search = liste_adjacence.find(v);
        
        // Pour chaque voisin de "sommet"
        for (long unsigned int i = 0; i<search->second.size(); i++)
        {   
            // Création de l'intersection P
            for (long unsigned int j = 0; j < P.size(); j++)
            {
                if (P[j] == search->second[i]){
                    intersectionP.push_back(P[j]);
                }
            }

            // Création de l'intersection X
            for (long unsigned int j = 0; j < X.size(); j++)
            {
                if (search->second[i] == X[j]){
                    intersectionX.push_back(X[j]);
                }
            }
        }

        unionR = R;
        unionR.push_back(v);
        BronKerboschPivot(unionR,intersectionP,intersectionX);
        P.erase(remove(P.begin(),P.end(),v),P.end());
        X.push_back(v);
    }
}

/**
 * La fonction BronKerboschPivot permet de trouver toutes les cliques max du graphe
 * selon la méthode de Bron-Kerbosch mais cette fois-ci en utilisant un tri de parcourt des sommets par degenerescence
 * @param R une ensemble de sommet
 * @param P ensemble de sommet avec une partie de R
 * @param X ensemble de sommet avec aucun sommet de R
 */
void Graph::BronKerboschDegenerescence(vector<int> R, vector<int> P, vector<int> X)
{
    /*

    vector<int> intersectionP = {};
    vector<int> intersectionX = {};
    vector<int> unionR = {};
    vector<int> PuX = {};
    vector<int> P_Nu = {};

    auto search = liste_adjacence.find(P_Nu[0]);
    

    for (long unsigned int i = 0; i<search->second.size(); i++)
    {
        for (long unsigned int j = 0; j < P.size(); j++)
        {
            if (P[j] == search->second[i]){
                intersectionP.push_back(P[j]);
            }
        }

        // Création de l'intersection X
        for (long unsigned int j = 0; j < X.size(); j++)
        {
            if (search->second[i] == X[j]){
                intersectionX.push_back(X[j]);
            }
        }
    }

    BronKerboschPivot(unionR,intersectionP,intersectionX);
    P.erase(remove(P.begin(),P.end(),P_Nu[0]),P.end());
    X.push_back(P_Nu[0]);*/
}

/*

algorithme BronKerbosch3(G)
    P = V(G)
    R = Ø
    X = Ø
    pour tout sommet v visités dans un ordre de dégénérescence de G faire
        BronKerbosch2({v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}
        
*/

/**
 * Fonnction main qui permet de tester toutes les autres fonctions
 * @return int 0
 */
int main() {

    Graph g = Graph();
    vector<int> R;
    vector<int> P;
    vector<int> X;

    g.genere_graph_triangle();
    g.ajout_sommet();
    g.ajout_arete(1,3);

    for (int i = 0; i < g.getNombreSommets(); i++)
    {
        P.push_back(i);
    }

    g.BronKerbosch(R,P,X);
    g.afficher_cliqueMax();

    
    return 0;
}