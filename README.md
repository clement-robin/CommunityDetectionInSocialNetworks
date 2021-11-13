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

    g.afficher_graph_matrice(); //affiche la matrice d'adjacence du graphe
    g.afficher_graph_liste(); //affiche la liste d'adjacence du graphe


- Génération aléatoire de graphes :

    srand(time(NULL));

    Graph g = Graph(10);
    g.genere_arete_probabilite(0.56);
 
    g.afficher_graph_matrice(); //affiche la matrice d'adjacence du graphe
    g.afficher_graph_liste(); //affiche la liste d'adjacence du graphe`

- Test et vérification de la probabilité de la génération de graphes aléatoire
    test_probabilite(10, 15000, 0.63);
    // 10 taille des graphes
    // 150000 le nombre de graphes différents généré pour le test
    // 0.63 la probabilite testée

cf. explication de l'algorithme de la fonction dans le rapport

