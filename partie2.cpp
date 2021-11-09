#include "partie2.h"

/*
    - Bron-Kerbosch
    - Degenerecence
    - Bron-Kerbosch pivot

*/

void Graph::BronKerbosch(vector<int> R, vector<int> P, vector<int> X){

    if (P.empty() && X.empty()){
        result_cliques.insert(R);
    }

    for (int node : P){

        vector<int> intersection = {}, intersectionX = {};

        //N(P)
        for (int nodeP : liste_adjacence[node]){
            for (int node2 : P){
                if (nodeP == node2){
                    intersection.push_back(nodeP);
                }   
            }
            //N(X)
            for (int node3 : X){
               if (nodeP == node3){
                    intersectionX.push_back(nodeP);
               }
           }
        }

        R.push_back(node);
        BronKerbosch(R,intersection,intersectionX);
        P.erase(remove(P.begin(),P.end(),node),P.end());
        X.push_back(node);    

    }
}


int main() {
    srand(time(NULL));

    
    
    return 0;
}
