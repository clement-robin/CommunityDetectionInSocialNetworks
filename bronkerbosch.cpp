#include "bronkerbosch.h"

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
        return;
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

    cout << u << endl;

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

vector <int> Graph::triOrdreDegenerescence() 
{
    vector<int> A = {};
    map<int, vector<int>>::iterator iterator_map;

    for (iterator_map = liste_adjacence.begin(); iterator_map != liste_adjacence.end(); iterator_map++)
    {
        A.push_back(iterator_map->first);
    }
    
    for (long unsigned int i = 0; i < A.size(); i++)
    {
        for (long unsigned int j = 0; j < A.size(); j++)
        {
            if (calcul_degre_sommet_liste(A[i]) < calcul_degre_sommet_liste(A[j]))
            {
                int v = A[i];
                A[i] = A[j];
                A[j] = v;
            }
        } 
    }
    return A;
}

void Graph::genOrdreDegenerescence()
{
    vector<int> A = triOrdreDegenerescence();
    Graph g2 = *(this);
    
    for (int i = 0; i < nombre_sommets; i++)
    {
        ordre_degenerescence.push_back(A[0]);
        g2.suppr_sommet(A[0]);
        A = g2.triOrdreDegenerescence();
    }

    for (long unsigned int i = 0; i < ordre_degenerescence.size(); i++)
    {
        cout << ordre_degenerescence[i] << " ";
    } 
}

void Graph::BronKerboschDegenerescence()
{
    vector<int> P = {};
    vector<int> X = {};
    vector<int> ordreDegenerescence = {};

    for (int i = 0; i < nombre_sommets; i++)
    {
        P.push_back(i);
    }
    
    genOrdreDegenerescence();
    ordreDegenerescence = ordre_degenerescence;

    for (long unsigned int i = 0; i < ordreDegenerescence.size(); i++)
    {
        vector<int> intersectionP = {};
        vector<int> intersectionX = {};
        vector<int> R = {};

        int v = ordreDegenerescence [i];
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

        R.push_back(v);
        BronKerboschPivot(R,intersectionP,intersectionX);
        P.erase(remove(P.begin(),P.end(),v),P.end());
        X.push_back(v);
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

    g.genOrdreDegenerescence();

    g.BronKerboschDegenerescence();
    g.afficher_cliqueMax();
    

    /*g.ajout_arete(0,1);

    g.ajout_arete(1,2);
    g.ajout_arete(1,3);
    g.ajout_arete(1,4);
    g.ajout_arete(1,6);

    g.ajout_arete(2,4);
    g.ajout_arete(2,8);
    g.ajout_arete(2,5);

    g.ajout_arete(3,4);
    g.ajout_arete(3,7);
    g.ajout_arete(3,8);

    g.ajout_arete(4,5);
    g.ajout_arete(4,6);
    g.ajout_arete(4,7);
    g.ajout_arete(4,8);

    g.ajout_arete(5,7);

    g.ajout_arete(6,8);

    g.ajout_arete(7,8);*/

    /*
    g.ajout_arete(0,1); 
    g.ajout_arete(0,5);
    g.ajout_arete(1,5);
    g.ajout_arete(1,2);
    g.ajout_arete(1,4);
    g.ajout_arete(2,3);
    g.ajout_arete(2,4);
    g.ajout_arete(2,5);
    g.ajout_arete(3,4);
    g.ajout_arete(4,5);
    */
    
    
    
    //g.BronKerboschPivot(R,P,X);
    //g.afficher_cliqueMax();


    
    return 0;
}