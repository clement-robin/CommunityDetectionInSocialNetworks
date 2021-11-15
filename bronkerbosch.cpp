#include "bronkerbosch.h"

/**
 * La fonction BronKerbosch peemet de trouver toutes les cliques max d'un graphe 
 * selon la méthode de Bron-Kerbosch (Algo récursif)
 * @param R Un vecteur qui est vide lors du premier appel, puis contient après l'ensemble des sommets qui appartiennent a la clique maximale
 * @param P Un vecteur qui comprend lors du premier appel tous les sommets du graphe a traité
 * @param X un vecteur qui est vide lors du premier appel, puis contient après l'ensemble des sommets déjà traité
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
 * selon la méthode de Bron-Kerbosch mais cette fois-ci en utilisant un pivot qui permet de reduire le nombre d'appel (Algo récursif) 
 * @param R Un vecteur qui est vide lors du premier appel, puis contient après l'ensemble des sommets qui appartiennent a la clique maximale
 * @param P Un vecteur qui comprend lors du premier appel tous les sommets du graphe a traité
 * @param X un vecteur qui est vide lors du premier appel, puis contient après l'ensemble des sommets déjà traité
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
 * La fonction triOrdreDegenerescence permet de trier l'ensemble
 * des sommets selon l'odre de dégénérescence du graphe
 * Retourne le vecteur trier des sommets selon l'odre de dégénérescence du graphe
 */
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

/**
 * La fonction genOrdreDegenerescence permet de générer 
 * l'ordre de dégénérescence du graphe
 */
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
}

/**
 * La fonction BronKerboschDegenerescence permet de trouver toutes les cliques max du graphe
 * selon la méthode de Bron-KerboschPivot mais cette fois-ci en utilisant l'ordre de dégénérescence
 * du graphe, ce qui permet de reduire le nombre d'appel et de trouver les cliques max du graphe
 * plus rapidement
 */
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

/**
 * La fonction genDecompositionGraphe permet de construire un graphe a partir d'un graphe donner
 * en entrée et en ajoutant le sommet donner en parametre, la fonction ajoute les arretes et retourne 
 * ainsi le graphe construit
 * @param g le graphe de reference
 * @param sommet un sommet du graphe
 */
Graph Graph::genDecompositionGraphe(Graph g,int sommet)
{
    Graph Gj = *(this); 
    Gj.ajout_sommet();
    auto search = g.liste_adjacence.find(sommet);

    for (long unsigned int i = 0; i < search->second.size(); i++)
    {
        if (search->second[i] < Gj.getNombreSommets() && sommet != search->second[i])
        {
            Gj.ajout_arete(sommet,search->second[i]);
        }
    }

    return Gj;
}

/**
 * La fonction mapContient permet de savoir si un vecteur est contenu 
 * dans une table de hachage de vecteur
 * Retourne true si le vecteur est dedans, false sinon
 * @param m une table de hachage de vecteur
 * @param v un vecteur
 */
bool mapContient(map<int,vector<int>> m,vector<int> v)
{   
    map<int, vector<int>>::iterator iteMap;
    for (iteMap = m.begin(); iteMap != m.end(); iteMap++)
    {
        if (iteMap->second == v)
        {
            return true;
        }
    }
    return false;
}

/**
 * La fonction compareOrdreDegenerescence compare et trie
 * un vecteur pour qu'il stocke les sommets
 * dans l'ordre de dégénérescence du graphe g
 * @param g graphe de reference
 * @param v un vecteur
 */
void compareOrdreDegenerescence(Graph g,vector<int>v)
{
    vector<int> vordre={};
    for (long unsigned int i = 0; i < g.getOrdreDegenerescence().size(); i++)
    {
        for (long unsigned int j = 0; j < v.size(); j++)
        {
            if (v[j] == g.getOrdreDegenerescence()[i]){
                vordre.push_back(v[j]);
            }
        }
    }
    v = vordre;
}

/**
 * La fonction Algorithm1 permet de trouver toutes 
 * en utilisant l'ordre de dégénérescence du graphe et BronKerboschDegenerescence
 * Cette algorithme est beaucoup plus rapide et moins couteux que l'algo de BronKerbosch
 * Retourne les cliques max du graphe g
 * @param g graphe de reference
 */
map<int,vector<int>> Graph::Algorithm1(Graph g){

    map<int,vector<int>> T = {};
    map<int,vector<int>> Tsuppr = {};
    Graph Gj = Graph(1);
    g.genOrdreDegenerescence();
    
    for (int j = 1; j < g.getNombreSommets(); j++)
    {
        Gj = Gj.genDecompositionGraphe(g,j);

        Gj.BronKerboschDegenerescence();
        map<int,vector<int>> Gj_clique = Gj.getListeCliqueMax();

        for (long unsigned int i = 0; i < Gj_clique.size(); i++)
        {
            auto search = Gj_clique.find(i);
            compareOrdreDegenerescence(g,search->second);
        }
        
        for (long unsigned int k = 0; k < Gj_clique.size(); k++)
        {
            auto search = Gj_clique.find(k);
            if(mapContient(T,search->second)){
                T.erase(k);
                Tsuppr.insert( std::pair<int,vector<int>>(Tsuppr.size(),search->second));
            }
            else
            {
                if (!mapContient(Tsuppr,search->second))
                {
                    T.insert( std::pair<int,vector<int>>(T.size(),search->second));
                }
            }
        }
    }
    return T;
}


/**
 * La fonction Algorithm2 permet de trouver toutes les cliques max du graphe
 * C'est une amélioration de Algorithm1
 * Retourne les cliques max du graphe g
 * @param g graphe de reference
 */
map<int,vector<int>> Graph::Algorithm2(Graph g){
    map<int,vector<int>> T = {};
    map<int,vector<int>> Tsuppr = {};
    Graph Gj = Graph(1);
    g.genOrdreDegenerescence();
    
    for (int j = 1; j < g.getNombreSommets(); j++)
    {
        Gj = Gj.genDecompositionGraphe(g,j);

        Gj.BronKerboschDegenerescence();
        map<int,vector<int>> Gj_clique = Gj.getListeCliqueMax();

        for (long unsigned int k = 0; k < Gj_clique.size(); k++)
        {
            auto search = Gj_clique.find(k);
            for (long unsigned int i = 0; i < search->second.size(); i++)
            {
                if (true/*any of its neighbors in G with lower rank than vj in σG is adjacent to all the vertices in K*/)
                {
                    T.erase(k);
                    Tsuppr.insert( std::pair<int,vector<int>>(Tsuppr.size(),search->second));
                }
                else
                {
                    if (!mapContient(Tsuppr,search->second))
                    {
                        T.insert( std::pair<int,vector<int>>(T.size(),search->second));
                    }
                } 
            }
        }
    }
    return T;
}