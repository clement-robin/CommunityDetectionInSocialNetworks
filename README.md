# CommunityDetectionInSocialNetworks
Projet IATIC 4 - Détection de communautés dans des réseaux sociaux



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
## Compilation
Makefile pour compiler les fichiers (make doit necessairement être installé sur la machine)

pour compiler : **make**
pour supprimer les .o et executable : **make clean**

## Execution
Afin d'executer, utilisez la commande : **make exe**

Dans le terminal, vous devrez saisir l'exemple d'execution parmis les 9 choix possibles :
### 1ere partie : génération de graphes
- 1 Construction d'un graphe manuellement
- 2 Generation avec une probabilite
- 3 Verification des tests de generation par probabilite
- 4 Generation selon Barabasi-Albert
### 2eme partie : Bron-Kerbosch
- 5 Bron-Kerbosch
- 6 Bron-Kerbosch avec Pivot
- 7 Dégénérescence avec Bron-Kerbosch
### 3eme partie : Autres calcules des cliques max
- 8 Algorithme 1
- 9 Algorithme 2

>vous devrez saisir un nombre parmis les choix pour vos tests
> `-1` pour quitter

## Partie 1 : 

Voici le code de chaque exemple d'execution, ils sont modifiable dans le `main.cpp` 

### - Génération de graphes :

```cpp
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
```

### - Génération aléatoire de graphes :

```cpp
Graph g = Graph(10);
g.genere_arete_probabilite(0.56);

g.afficher_graph_matrice();
g.afficher_graph_liste();
```

### - Test et vérification de la probabilité de la génération de graphes aléatoire

```cpp
test_probabilite(10, 15000, 0.63);
```


### - Barabasi-Albert

```cpp
Graph g = genere_barabasi_albert();
g.afficher_graph_liste();
```
L'utilisateur devra indique le nombre d'arètes maximums que l'on peut ajouter pour un sommet.
>Chaque demande impliquera l'ajout d'un sommet et la génération des arètes selon la méthode de Barabasi-Albert.

Si l'utilisateur souhaite stoper la génération et afficher la liste d'adjacence du graphe, il lui suifit de taper `-1`

# Partie 2 : 

### - Bron-Kerbosch :

```cpp
Graph g = Graph();
vector<int> R;
vector<int> P;
vector<int> X;

g.genere_graph_triangle();
g.ajout_sommet();
g.ajout_arete(1,3);

// P contient tout les sommets du graphe
for (int i = 0; i < g.getNombreSommets(); i++)
{
    P.push_back(i);
}

g.BronKerbosch(R,P,X);
g.afficher_cliqueMax();
```
### - Bron-Kerbosch avec pivot :

l'execution est la même que pour Bron-Kerbosch, on remplace seulement :
```cpp
g.BronKerbosch(R,P,X);
```
par
```cpp
g.BronKerboschPivot(R,P,X);
```

### - Dégénérécence de Bron-Kerbosch :
```cpp
Graph g = Graph();

g.genere_graph_triangle();
g.ajout_sommet();
g.ajout_arete(1,3);
g.afficher_graph_liste();

g.BronKerboschDegenerescence();
g.afficher_cliqueMax();
```


# Partie 3 : 

### - Algorithme 1:
```cpp
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
```

### - 3.2 :
```cpp
test
```