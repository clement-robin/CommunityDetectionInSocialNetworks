# CommunityDetectionInSocialNetworks
Projet IATIC 4 - Détection de communautés dans des réseaux sociaux

Makefile pour compiler les fichiers (make necessairement installer sur la machine)

pour compiler : make
pour executer : ./graph
pour supprimer les .o et executable : make clean

Voici la répartition des fichiers suivant les parties du projets :

1ere partie :
 - graph.cpp
 - graph.h

2eme partie :
 - bronkerbosch.cpp
 - bronkerbosch.h

3eme partie :
 - partie3.cpp
 - partie3.h

Vous trouverez ci-dessous plusieurs exemples d'execution:

Pour la partie 1 : 

- Génération de graphes :

    srand(time(NULL));

    Graph g = Graph(3);<br>
    g.ajout_sommet();<br>
    g.ajout_sommet();<br>
    g.ajout_sommet();<br>

    g.ajout_arete(1,3);<br>
    g.ajout_arete(0,1); <br>
    g.ajout_arete(0,5);<br>
    g.ajout_arete(1,5);<br>
    g.ajout_arete(1,2);<br>
    g.ajout_arete(1,4);<br>
    g.ajout_arete(2,3);<br>
    g.ajout_arete(2,4);<br>
    g.ajout_arete(2,5);<br>
    g.ajout_arete(3,4);<br>
    g.ajout_arete(4,5);<br>

    g.afficher_graph_matrice(); //affiche la matrice d'adjacence du graphe<br>
    g.afficher_graph_liste(); //affiche la liste d'adjacence du graphe<br>


- Génération aléatoire de graphes :

    srand(time(NULL));<br>

    Graph g = Graph(10);<br>
    g.genere_arete_probabilite(0.56);<br>
 
    g.afficher_graph_matrice(); //affiche la matrice d'adjacence du graphe<br>
    g.afficher_graph_liste(); //affiche la liste d'adjacence du graphe<br>

- Test et vérification de la probabilité de la génération de graphes aléatoire

    test_probabilite(10, 15000, 0.63);<br>
    // 10 taille des graphes<br>
    // 150000 le nombre de graphes différents généré pour le test<br>
    // 0.63 la probabilite testée<br>

cf. explication de l'algorithme de la fonction dans le rapport

Pour la partie 2 :

- Bron-Kerbosch

    Graph g = Graph();<br>
    vector<int> R;<br>
    vector<int> P;<br>
    vector<int> X;<br>
    vector<int> PuX = {};<br>

    g.genere_graph_triangle();<br>
    g.ajout_sommet();<br>
    g.ajout_arete(1,3);<br>

    for (int i = 0; i < g.getNombreSommets(); i++)<br>
    {<br>
        P.push_back(i);<br>
    }<br>
    
    g.BronKerbosch(R,P,X);<br>
    g.afficher_cliqueMax();<br>

- Bron-Kerbosch
    l'execution est la meme, on remplace seulement:<br>
        g.BronKerbosch(R,P,X);<br>
    par<br>
        g.BronKerboschPivot(R,P,X);<br>