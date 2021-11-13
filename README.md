# CommunityDetectionInSocialNetworks
Projet IATIC 4 - Détection de communautés dans des réseaux sociaux

# Compilation
Makefile pour compiler les fichiers (make necessairement installer sur la machine)

pour compiler : **make**
pour executer : **./graph**
pour supprimer les .o et executable : **make clean**

# Arborescence
Voici la répartition des fichiers suivant les parties du projets :

### 1ere partie :
 - graph.cpp
 - graph.h

### 2eme partie :
 - bronkerbosch.cpp
 - bronkerbosch.h

### 3eme partie :
 - partie3.cpp
 - partie3.h


# Execution 
Vous trouverez ci-dessous plusieurs exemples d'execution a modifier dans le **main** à la fin du fichier *bronkerbosch.cpp
>ne pas oublier le `return 0` 

## Partie 1 : 

### - Génération de graphes :

```cpp
Graph g = Graph(3);

g.ajout_sommet();
g.ajout_sommet();
g.ajout_sommet();

g.ajout_arete(1,3)
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

g.afficher_graph_matrice(); //affiche la matrice d'adjacence du graphe<br>
g.afficher_graph_liste(); //affiche la liste d'adjacence du graphe<br>
```

### Génération aléatoire de graphes :

```cpp
srand(time(NULL));

Graph g = Graph(10);<br>
g.genere_arete_probabilite(0.56);

g.afficher_graph_matrice(); //affiche la matrice d'adjacence du graphe
g.afficher_graph_liste(); //affiche la liste d'adjacence du graphe
```

### Test et vérification de la probabilité de la génération de graphes aléatoire

```cpp
test_probabilite(10, 15000, 0.63);<br>
// 10 taille des graphes<br>
// 150000 le nombre de graphes différents généré pour le test<br>
// 0.63 la probabilite testée<br>
```

> cf. explication de l'algorithme de la fonction dans le rapport

## Partie 2 : 

# - Bron-Kerbosch :

```cpp
Graph g = Graph();
vector<int> R;
vector<int> P;
vector<int> X;
vector<int> PuX = {};

g.genere_graph_triangle();
g.ajout_sommet();
g.ajout_arete(1,3);

for (int i = 0; i < g.getNombreSommets(); i++)
{
    P.push_back(i);<
}

g.BronKerbosch(R,P,X);
g.afficher_cliqueMax();
```
### - Bron-Kerbosch avec pivot :

l'execution est la meme, on remplace seulement:
```cpp
g.BronKerbosch(R,P,X);
```
par
```cpp
g.BronKerboschPivot(R,P,X);
```