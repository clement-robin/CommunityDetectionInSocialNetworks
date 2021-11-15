#include "partie3.h"

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
                if (mapContient(T,search->second)/*any of its neighbors in G with lower rank than vj in σG is adjacent to all the vertices in K*/)
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