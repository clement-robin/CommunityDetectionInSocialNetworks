
#include "partie3.h"


/****PROTOTYPES****/

int affichage_demande_exemples();

/****FONCTIONS****/

/**
 * La fonction affichage_demande_exemples affiche toutes les possibilites d'exemple disponible
 * et demande laquelle l'utilisateur souhaite tester
 * @return int ans reponse de l'utilisateur
 */
int affichage_demande_exemples() {
    int ans = 0;
    cout << "---------------------------------------------------------------------------------------" << endl ;
    cout << "---------------------------------------------------------------------------------------" << endl ;
    cout << "Tapez le nombre correspondant à l'exemple voulu (-1 pour quitter, nombres uniquement)" << endl << endl;
    cout << "Partie 1 : génération de graphes" << endl;
    cout << "   1 - Construction d'un graphe manuellement" << endl;
    cout << "   2 - Generation avec une probabilite" << endl;
    cout << "   3 - Verification des tests de generation par probabilite" << endl;
    cout << "   4 - Generation selon Barabasi-Albert" << endl;
    cout << "Partie 2 : Bron-Kerbosch" << endl;
    cout << "   5 - Bron-Kerbosch" << endl;
    cout << "   6 - Bron-Kerbosch avec Pivot" << endl;
    cout << "   7 - Dégénérescence avec Bron-Kerbosch" << endl;
    cout << "Partie 3 : Autres calcules des cliques max" << endl;
    cout << "   8 - Algorithme 1" << endl;
    cout << "   9 - Algorithme 2" << endl;
    cout << "reponse : ";
    cin >> ans;
    cout << "---------------------------------------------------------------------------------------" << endl ;
    cout << "---------------------------------------------------------------------------------------" << endl ;

    return ans;

}

/**
 * Fonction main qui permet de tester toutes les autres fonctions
 * @return int 0
 */
int main() {

    srand(time(NULL));
    
    int ans = 0;

    ans = (int)affichage_demande_exemples();

    while (ans != -1)
    {
        switch(ans)
        {
        case 1: {
            cout << endl << "1 - Exemple de construction d'un graphe a la main :" << endl << endl;

            Graph g = Graph(3);

            g.ajout_sommet();
            g.ajout_sommet();
            g.ajout_sommet();

            g.ajout_arete(1,3);
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

            g.afficher_graph_liste(); //affiche la liste d'adjacence du graphe
            break;
        }

        case 2:{
            cout << endl << "2 - Exemple de construction d'un graphe avec une probabilite :" << endl;
            cout << "    sur un graphe de 5 a 20 sommets " << endl;
            cout << "    avec un probabilite de generation de sommet de 0 a 1 " << endl << endl;

            
            int random_sommet = 0;
            while(random_sommet<5) {
                random_sommet =rand()%20;
            }
            Graph g = Graph(random_sommet);
            float random_proba = (float(rand()%100))/100;
            g.genere_arete_probabilite(random_proba);

            g.afficher_graph_liste();
            break;
        }
        case 3: {
            cout << endl << "3 - Test de la probabilite sur les la generation des graphes :" << endl;
            cout << "    sur des graphes de 5 a 20 sommets " << endl;
            cout << "    avec un probabilite de generation de sommet de 0 a 1  " << endl;
            cout << "    on effectue le test 1000 a 20 000 fois " << endl << endl;
            
             int random_sommet = 0;
            while(random_sommet<5) {
                random_sommet =rand()%20;
            }
            int random_test= 0;
            while(random_test<1000) {
                random_test =rand()%20000;
            }
            float random_proba = (float(rand()%100))/100;
            test_probabilite(random_sommet, random_test, random_proba);
            break;
        }
        case 4: {
            Graph g = genere_barabasi_albert();
            g.afficher_graph_liste();
            break;
        }
        case 5: {
            Graph g = Graph();
            vector<int> R;
            vector<int> P;
            vector<int> X;

            g.genere_graph_triangle();
            g.ajout_sommet();
            g.ajout_arete(1,3);
            cout << endl;
            g.afficher_graph_liste();

            for (int i = 0; i < g.getNombreSommets(); i++)
            {
                P.push_back(i);
            }

            g.BronKerbosch(R,P,X);
            g.afficher_cliqueMax();
            break;
        }
        case 6: { 
            Graph g = Graph();
            vector<int> R;
            vector<int> P;
            vector<int> X;

            g.genere_graph_triangle();
            g.ajout_sommet();
            g.ajout_arete(1,3);
            cout << endl;
            g.afficher_graph_liste();

            for (int i = 0; i < g.getNombreSommets(); i++)
            {
                P.push_back(i);
            }

            g.BronKerboschPivot(R,P,X);
            g.afficher_cliqueMax();
            break;
        }
        case 7: {
            Graph g = Graph();

            g.genere_graph_triangle();
            g.ajout_sommet();
            g.ajout_arete(1,3);
            cout << endl;
            g.afficher_graph_liste();

            g.BronKerboschDegenerescence();
            g.afficher_cliqueMax();

            break;
        }
        case 8: { // algo 1
            map<int,vector<int>> T;
            Graph g = Graph(4);

            g.ajout_arete(0,1);
            g.ajout_arete(0,2);
            g.ajout_arete(1,2);
            g.ajout_arete(1,3);
            
            g.afficher_graph_liste();

            T = g.Algorithm1(g);

            map<int, vector<int>>::iterator p;
            for(p = T.begin(); p != T.end(); p++)
            {
                cout << "clique "<< p->first << " : ";
                for (long unsigned int i = 0; i < p->second.size(); i++)
                {
                    cout << p->second[i] << " ";
                }
                cout << endl;
            }
            cout << endl;
            break;
        }
        case 9: {
            cout << "partie 3.2" << endl;
            break;
        }    
        default:
            cout << "non definit" << endl;
            break;
        }

       ans = affichage_demande_exemples();

    }
    return 0;
}
