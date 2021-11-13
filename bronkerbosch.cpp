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

        int v = P[0];
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
        //P.erase(remove(P.begin(),P.end(),P[0]),P.end());
        P.erase(P.begin());
        X.push_back(v);
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
    vector<int> PuX = {};
    vector<int> P_Nu = {};

    int u = -1;
    int val = 0;
    int max = 0;
    
    if (P.empty() && X.empty())
    {
        AddListeCliqueMax(R);
    }

    cout << "Size P: "<< P.size() << endl;
    for (long unsigned int i = 0; i < P.size(); i++)
    {
        cout << P[i] <<" ";
    }
    cout << endl;

    cout << "Size X: "<< X.size() << endl;
    for (long unsigned int i = 0; i < X.size(); i++)
    {
        cout << X[i] <<" ";
    }
    cout << endl;

    // Construire le vecteur PuX 
    for (long unsigned int i = 0; i < P.size(); i++)
    {
        PuX.push_back(P[i]);
    }
    for (long unsigned int i = 0; i < X.size(); i++)
    {   
        vector<int>::iterator it;
        it = find(PuX.begin(),PuX.end(),X[i]);
        if(it!=PuX.end()){
            PuX.push_back(X[i]);
        }
    }
    
    // Affichage PuX
    cout << "Size PuX: "<< PuX.size() << endl;
    for (long unsigned int i = 0; i < PuX.size(); i++)
    {
        cout << PuX[i] <<" ";
    }
    cout << endl;

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

    cout << "u: " << u << endl;

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

    // Affichage P \ N(u)
    cout << "Size P - N(u): "<< P_Nu.size() << endl;
    for (long unsigned int i = 0; i < P_Nu.size(); i++)
    {
        cout << P_Nu[i] <<" ";
    }
    cout << endl;
    

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
        unionR.push_back(P_Nu[0]);
         
        // Affichage de l'intersection P)
        cout << "Size intersectionP: "<< intersectionP.size() << endl;
        for (long unsigned int i = 0; i < intersectionP.size(); i++)
        {
            cout << intersectionP[i] <<" ";
        }
        cout << endl;

        // Affichage de l'intersection X)
        cout << "Size intersectionX: "<< intersectionX.size() << endl;
        for (long unsigned int i = 0; i < intersectionX.size(); i++)
        {
            cout << intersectionX[i] <<" ";
        }
        cout << endl;

        // Affichage de l'union R)
        cout << "Size unionR: "<< unionR.size() << endl;
        for (long unsigned int i = 0; i < unionR.size(); i++)
        {
            cout << unionR[i] <<" ";
        }
        cout << endl;

        BronKerboschPivot(unionR,intersectionP,intersectionX);
        P.erase(remove(P.begin(),P.end(),P_Nu[0]),P.end());
        X.push_back(P_Nu[0]);
    }
}

void Graph::BronKerboschDegenerence()
{
    vector<int> R;
    vector<int> P;
    vector<int> X;


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
    X.push_back(P_Nu[0]);
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



algorithme BronKerbosch3(G)
    P = V(G)
    R = Ø
    X = Ø
    pour tout sommet v visités dans un ordre de dégénérescence de G faire
        BronKerbosch2({v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}*/

int main() {
    srand(time(NULL));

    test_probabilite(10,15000, 0.63);

    return 0;
}