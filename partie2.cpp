#include "partie2.h"

/*
    - Bron-Kerbosch
    - Degenerecence
    - Bron-Kerbosch pivot

*/

void Graph::BronKerbosch(vector<int> R, vector<int> P, vector<int> X){

    if (P.empty() && X.empty()){
        result_cliques = R;
    }

    for (long unsigned int sommet = 0; sommet<P.size(); sommet++){

        vector<int> intersection = {}, intersectionX = {};

        auto search = liste_adjacence.find(sommet);
        cout << "size liste_adjacence "<< search->second.size() << endl;
        
        for (long unsigned int i = 0; i<search->second.size(); i++)
        {   
            // N(P)
            for (long unsigned int j = 0; j < P.size(); j++)
            {
                if (P[i] == P[j]){
                    intersection.push_back(P[i]);
                }
            }

            // N(X)
            for (long unsigned int j = 0; j < X.size(); j++)
            {
                if (P[i] == X[j]){
                    intersectionX.push_back(P[i]);
                }
            }
        }

        R.push_back(P[sommet]);
        cout << "R "<< R.size() << endl;
        cout << "P "<< P.size() << endl;
        cout << "X "<< X.size() << endl;
        //BronKerbosch(R,intersection,intersectionX);
        //P.erase(P.begin()+sommet-1);
        P.erase(remove(P.begin(),P.end(),P[sommet]),P.end());
        X.push_back(P[sommet]);
    }
}


int main() {

    srand(time(NULL));

    Graph g = Graph();
    vector<int> R;
    vector<int> P;
    vector<int> X;

    g.genere_graph_triangle();

    for (int i = 0; i < g.getNombreSommets(); i++)
    {
        P.push_back(i);
    }
    
    g.BronKerbosch(R,P,X);

    /*for (long unsigned int i = 0; i < g.result_cliques.size(); i++)
    {
        cout << g.result_cliques[i] << " ";
    }
    
    cout << endl;*/
    
    return 0;
}