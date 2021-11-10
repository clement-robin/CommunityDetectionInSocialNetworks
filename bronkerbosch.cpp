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
        cout << i << endl;
    }
    
    g.BronKerbosch(R,P,X);
    g.afficher_cliqueMax();
    
    return 0;
}