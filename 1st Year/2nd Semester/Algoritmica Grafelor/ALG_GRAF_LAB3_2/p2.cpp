#include <iostream>
#include <fstream>
#include <vector>
#define inf 99999
using namespace std;

// Structura pentru o muchie
struct Edge {
    int s,d,w;
};

// Functia Bellman-Ford
bool bellmanFord(vector<Edge>& edges, int n, int s, vector<int>& dist) {
    dist.assign(n, inf);
    dist[s] = 0;

    // Relaxarea muchiilor repetat pentru n-1 iteratii
    for (int i = 0; i < n - 1; ++i) {
        for (const Edge& edge : edges) {
            if (dist[edge.s] != inf && dist[edge.d] > dist[edge.s] + edge.w) {
                dist[edge.d] = dist[edge.s] + edge.w;
            }
        }
    }

    // Verificare cicluri negative
    for (const Edge& edge : edges) {
        if (dist[edge.s] != inf && dist[edge.d] > dist[edge.s] + edge.w) {
            return false; // Ciclu negativ detectat
        }
    }

    return true;
}

// Functia Dijkstra
void dijkstra(vector<Edge> graph[], int n, int s, vector<int>& dist) {
    dist.assign(n, inf);
    dist[s] = 0;

    vector<bool> sptSet(n, false);

    for (int count = 0; count < n - 1; ++count) {
        int u = -1, minDist = inf;
        // Selectare nod nevizitat cu distanta minima
        for (int v = 0; v < n; ++v) {
            if (!sptSet[v] && dist[v] < minDist) {
                u = v;
                minDist = dist[v];
            }
        }

        if (u == -1) // Daca nu exista noduri disponibile, iesire
            return;

        sptSet[u] = true;

        // Relaxare muchiilor adiacente nodului selectat
        for (const Edge& edge : graph[u]) {
            int v = edge.d;
            if (!sptSet[v] && dist[u] != inf && dist[u] + edge.w < dist[v]) {
                dist[v] = dist[u] + edge.w;
            }
        }
    }
}
void algorithmJohnson(vector<Edge>& edges, vector<Edge> graph[], int n, ofstream& g) {
    // Copierea muchiilor pentru a păstra costurile inițiale
    vector<Edge> originalEdges = edges;

    // Adaugare nod fictiv cu muchii de cost 0 catre toate celelalte noduri
    vector<Edge> modifiedGraph = edges;
    for (int i = 0; i < n; ++i) {
        modifiedGraph.push_back({n, i, 0});
    }

    // Aplicare Bellman-Ford pentru a obtine h[]
    vector<int> h;
    if (!bellmanFord(modifiedGraph, n + 1, n, h)) {
        g << "-1"; // Scrie "-1" în fișierul de ieșire dacă există un circuit de cost negativ
        return;
    }

    // Rezolvare muchii folosind h[]
    for (Edge& edge : edges) {
        edge.w += h[edge.s] - h[edge.d];
    }

    // Scrie muchiile în fișierul de ieșire, ordonate după nodul sursă și apoi după nodul destinație
    for (const Edge& edge : originalEdges) {
        g << edge.s << " " << edge.d << " " << edge.w << endl;
    }

    // Aplicare Dijkstra pentru fiecare nod
    for (int u = 0; u < n; ++u) {
        vector<int> dist;
        dijkstra(graph, n, u, dist); // Transmiteți graph în loc de &edges
        // Revenirea la costurile initiale
        for (int v = 0; v < n; ++v) {
            if (dist[v] != inf) {
                dist[v] -= h[u] - h[v];
            }
        }

        // Scrie costurile minime în fișierul de ieșire
        for (int i = 0; i < n; ++i) {
            if (dist[i] == inf) {
                g << "INF ";
            } else {
                g << dist[i] << " ";
            }
        }
        g << endl;
    }
}

int main(int argc,char** argv) {
    ifstream f(argv[1]);
    ofstream g(argv[2]);

    int n, m; // n - numarul de noduri, m - numarul de muchii
    f >> n >> m;

    vector<Edge> edges(m);
    vector<Edge> graph[n]; // Crearea vectorului de vectori de muchii

    for (int i = 0; i < m; ++i) {
        f >> edges[i].s >> edges[i].d >> edges[i].w;
        graph[edges[i].s].push_back(edges[i]); // Adaugarea muchiilor la lista de adiacență a nodurilor corespunzătoare
    }

    algorithmJohnson(edges, graph, n, g); // Transmiteți graph în loc de &edges

    f.close();
    g.close();

    return 0;
}