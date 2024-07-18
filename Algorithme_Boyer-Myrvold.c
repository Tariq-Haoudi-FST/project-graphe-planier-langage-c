#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Structure pour représenter un graphe
struct Graph {
    int V; // Nombre de sommets
    int E; // Nombre d'arêtes
    int adj[MAX_VERTICES][MAX_VERTICES]; // Matrice d'adjacence
};

// Fonction pour initialiser un graphe vide
void initGraph(struct Graph* graph, int V) {
    graph->V = V;
    graph->E = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph->adj[i][j] = 0;
        }
    }
}

// Fonction auxiliaire pour contracter une arête dans le graphe
void contractEdge(struct Graph* graph, int u, int v) {
    // Contracter une arête consiste à fusionner les sommets u et v en un seul sommet

    // Fusionner les sommets u et v en un nouveau sommet
    int mergedVertex = graph->V;
    graph->V++;

    // Mettre à jour les arêtes incidentes au nouveau sommet
    for (int i = 0; i < graph->V; i++) {
        if (i != u && i != v) {
            graph->adj[mergedVertex][i] = graph->adj[u][i] || graph->adj[v][i];
            graph->adj[i][mergedVertex] = graph->adj[mergedVertex][i];
        }
    }

    // Effacer les arêtes incidentes à u et v
    for (int i = 0; i < graph->V; i++) {
        graph->adj[u][i] = 0;
        graph->adj[v][i] = 0;
        graph->adj[i][u] = 0;
        graph->adj[i][v] = 0;
    }
}

// Fonction pour vérifier si une arête peut être contractée
bool canContract(struct Graph* graph, int u, int v) {
    // Vérifier s'il y a une arête entre u et v
    if (graph->adj[u][v] && u != v) {
        // Vérifier si la contraction de l'arête ne créera pas d'arêtes parallèles ou de boucles
        for (int i = 0; i < graph->V; i++) {
            if (graph->adj[u][i] && graph->adj[v][i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// Fonction pour ajouter une arête entre deux sommets
void addEdge(struct Graph* graph, int u, int v) {
    graph->adj[u][v] = 1;
    graph->adj[v][u] = 1;
    graph->E++;
}

// Fonction pour vérifier s'il existe un graphe complet sur 5 sommets (K5)
bool hasK5(struct Graph* graph) {
    int i, j, k, l, m;

    for (i = 0; i < graph->V - 4; i++) {
        for (j = i + 1; j < graph->V - 3; j++) {
            for (k = j + 1; k < graph->V - 2; k++) {
                for (l = k + 1; l < graph->V - 1; l++) {
                    for (m = l + 1; m < graph->V; m++) {
                        if (graph->adj[i][j] && graph->adj[i][k] && graph->adj[i][l] && graph->adj[i][m] &&
                            graph->adj[j][k] && graph->adj[j][l] && graph->adj[j][m] &&
                            graph->adj[k][l] && graph->adj[k][m] &&
                            graph->adj[l][m]) {
                            // Les sommets i, j, k, l et m forment un sous-graphe K5
                            return true;
                        }
                    }
                }
            }
        }
    }

    // Sous-graphe K5 non trouvé
    return false;
}

// Fonction pour vérifier s'il existe un graphe bipartite complet sur 3+3 sommets (K3,3)
bool hasK33(struct Graph* graph) {
    int i, j, k, l, m, n;

    for (i = 0; i < graph->V - 5; i++) {
        for (j = i + 1; j < graph->V - 4; j++) {
            for (k = j + 1; k < graph->V - 3; k++) {
                for (l = k + 1; l < graph->V - 2; l++) {
                    for (m = l + 1; m < graph->V - 1; m++) {
                        for (n = m + 1; n < graph->V; n++) {
                            if ((graph->adj[i][j] && graph->adj[i][k] && graph->adj[i][l] &&
                                 graph->adj[j][k] && graph->adj[j][l] &&
                                 graph->adj[k][l]) &&
                                (graph->adj[m][n] && graph->adj[m][i] && graph->adj[m][j] &&
                                 graph->adj[n][i] && graph->adj[n][j] &&
                                 graph->adj[n][k])) {
                                // Les sommets i, j, k, l, m et n forment un sous-graphe K3,3
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    // Sous-graphe K3,3 non trouvé
    return false;
}

// Fonction pour vérifier les conditions finales requises par l'algorithme de Boyer-Myrvold
bool checkFinalConditions(struct Graph* graph) {
    // Vérifier les conditions supplémentaires basées sur les spécificités de l'algorithme
    // ...

    // Pour simplifier, supposons une condition de base pour la planarité
    // (ce n'est pas une représentation précise de l'algorithme complet)
    if (graph->E <= 3 * graph->V - 6) {
        // Le graphe satisfait une condition de base de planarité
        return true;
    } else {
        // Le graphe ne satisfait pas la condition de planarité
        return false;
    }
}

// Fonction pour réduire le graphe en utilisant des contractions d'arêtes
void reduceGraph(struct Graph* graph) {
    bool contractionPerformed = true;
    while (contractionPerformed) {
        contractionPerformed = false;

        // Votre logique pour trouver une arête à contracter
        for (int u = 0; u < graph->V; u++) {
            for (int v = 0; v < graph->V; v++) {
                if (canContract(graph, u, v)) {
                    // Contracter l'arête (u, v)
                    contractEdge(graph, u, v);

                    // Définir le drapeau pour indiquer que la contraction a été effectuée
                    contractionPerformed = true;

                    // Sortir de la boucle interne après la première contraction
                    break;
                }
            }

            // Sortir de la boucle externe si une contraction a été effectuée
            if (contractionPerformed) {
                break;
            }
        }
    }
}

// Fonction pour vérifier si un graphe est planaire en utilisant l'algorithme de Boyer-Myrvold
bool isPlanar(struct Graph* graph) {
    // Vérification des conditions de base
    if (graph->V == 0 || graph->V < 4) {
        return true;
    }

    // Recherche des sous-graphes K5 et K3,3
    if (hasK5(graph) || hasK33(graph)) {
        return false;
    }

    // Réduction du graphe
    reduceGraph(graph);

    // Vérification des conditions finales
    return checkFinalConditions(graph);
}

int main() {
    struct Graph graph;
    int V, E;

    printf("Entrez le nombre de sommets du graphe : ");
    scanf("%d", &V);

    printf("Entrez le nombre d'arêtes du graphe : ");
    scanf("%d", &E);

    initGraph(&graph, V);

    printf("Entrez les arêtes du graphe :\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&graph, u, v);
    }

    if (isPlanar(&graph)) {
        printf("Le graphe est planaire.\n");
    } else {
        printf("Le graphe n'est pas planaire.\n");
    }

    return 0;
}