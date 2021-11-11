#include "bronkerbosch.h"

/*
    - Bron-Kerbosch
    - Degenerecence
    - Bron-Kerbosch pivot

*/

void Graph::BronKerbosch(vector<int> R, vector<int> P, vector<int> X){

    if (P.empty() && X.empty()){
        AddListeCliqueMax(R);
    }

    // Pour chaque sommet de P
    for (long unsigned int sommet = 0; sommet<P.size(); sommet++){

        vector<int> intersectionP = {};
        vector<int> intersectionX = {};
        vector<int> unionR = {};

        auto search = liste_adjacence.find(P[0]);
        
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
        unionR.push_back(P[0]);
        BronKerbosch(unionR,intersectionP,intersectionX);
        //P.erase(remove(P.begin(),P.end(),P[0]),P.end());
        P.erase(P.begin());
        X.push_back(P[0]);
    }
}

/*
algorithme BronKerbosch2(R, P, X)
    si P et X sont vides alors
        déclarer R clique maximale
    choisir un sommet pivot u dans P ⋃ X
    pour tout sommet v dans P \ N(u) faire
        BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}
*/

void Graph::BronKerboschPivot(vector<int> R, vector<int> P, vector<int> X)
{
    vector<int> PinterX = {};
    vector<int> P_Nu = {};

    int u = -1;
    int val = 0;
    int max = 0;

    if (P.empty() && X.empty()){
        AddListeCliqueMax(R);
    }

    // Construire le vecteur PinterX 
    for (long unsigned int i = 0; i < P.size(); i++)
    {
        for (long unsigned int j = 0; j < X.size(); j++)
        {
            if(P[i]==X[j]){
                PinterX.push_back(P[i]);
            }
        } 
    }

    // Choisir un sommet u dans P U X tel que le nombre de sommet en commun entre P et les voisins de u soit maximal
    for (long unsigned int i = 0; i < PinterX.size(); i++)
    {
        auto search = liste_adjacence.find(PinterX[i]);
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
            u = PinterX[i];
        }
    }

    cout << "u: " << u << endl;

    // Creation de P \ N(u)
    auto search = liste_adjacence.find(u);
    for (long unsigned int i = 0; i < P.size(); i++)
    {
        for (long unsigned int j = 0; j < search->second.size(); j++)
        {
            if (P[i]!=search->second[j])
            {
                P_Nu.push_back(P[i]);
            }
        }
    }

    // Pour chaque sommet de P \ N(u)
    for (long unsigned int sommet = 0; sommet<P_Nu.size(); sommet++){

        vector<int> intersectionP = {};
        vector<int> intersectionX = {};
        vector<int> unionR = {};

        auto search = liste_adjacence.find(P_Nu[0]);
        
        // Pour chaque voisin de "sommet"
        for (long unsigned int i = 0; i<search->second.size(); i++)
        {   
            // Création de l'intersection P
            for (long unsigned int j = 0; j < P_Nu.size(); j++)
            {
                if (P_Nu[j] == search->second[i]){
                    intersectionP.push_back(P_Nu[j]);
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
        unionR.push_back(P_Nu[0]);
        BronKerbosch(unionR,intersectionP,intersectionX);
        //P.erase(remove(P.begin(),P.end(),P[0]),P.end());
        P.erase(P.begin());
        X.push_back(P[0]);
    }
}

int main() {

    srand(time(NULL));

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
    
    g.BronKerboschPivot(R,P,X);
    g.afficher_cliqueMax();
    
    return 0;
}