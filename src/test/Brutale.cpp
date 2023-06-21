#include <cstdio>
#include <vector>
#include <climits>
#include <queue>
#include <cstdlib>
#include "../Graph.hpp"

using std::queue;
using std::min;

int NODES = 0;

void push(const int * const * C, int ** F, int *excess, int u, int v) {
  int send = min(excess[u], C[u][v] - F[u][v]);
  F[u][v] += send;
  F[v][u] -= send;
  excess[u] -= send;
  excess[v] += send;
}

void relabel(const int * const * C, const int * const * F, int *height, int u) {
  int v;
  int min_height = INT_MAX;
  for (v = 0; v < NODES; v++) {
    if (C[u][v] - F[u][v] > 0) {
      min_height = min(min_height, height[v]);
      height[u] = min_height + 1;
    }
  }
};

void discharge(const int * const * C, int ** F, int *excess, int *height, int *seen, int u) {
  while (excess[u] > 0) {
    if (seen[u] < NODES) {
      int v = seen[u];
      if ((C[u][v] - F[u][v] > 0) && (height[u] > height[v])) {
        push(C, F, excess, u, v);
      } else {
        seen[u] += 1;
      }
    } else {
      relabel(C, F, height, u);
      seen[u] = 0;
    }
  }
}

void moveToFront(int i, int *A) {
  int temp = A[i];
  int n;
  for (n = i; n > 0; n--) {
    A[n] = A[n-1];
  }
  A[0] = temp;
}

int pushRelabel(const int * const * C, int ** F, int source, int sink) {
  int *excess, *height, *list, *seen, i, p;

  excess = (int *) calloc(NODES, sizeof(int));
  height = (int *) calloc(NODES, sizeof(int));
  seen = (int *) calloc(NODES, sizeof(int));

  list = (int *) calloc((NODES-2), sizeof(int));

  for (i = 0, p = 0; i < NODES; i++){
    if ((i != source) && (i != sink)) {
      list[p] = i;
      p++;
    }
  }

  height[source] = NODES;
  excess[source] = INT_MAX;
  for (i = 0; i < NODES; i++)
    push(C, F, excess, source, i);

  p = 0;
  while (p < NODES - 2) {
    int u = list[p];
    int old_height = height[u];
    discharge(C, F, excess, height, seen, u);
    if (height[u] > old_height) {
      moveToFront(p, list);
      p = 0;
    } else {
      p += 1;
    }
  }
  int maxflow = 0;
  for (i = 0; i < NODES; i++)
    maxflow += F[source][i];

  free(list);

  free(seen);
  free(height);
  free(excess);

  return maxflow;
}

// Funzione di esempio per testare l'algoritmo
int main() {
    
    Graph a = Graph(1, 4);
    a.AddNode();
    a.AddNode();
    a.AddNode();
    a.AddNode();
    a.AddNode();


    
    a.AddEdge(1, 3, 4); // 1 ---(4)---> 3
    a.AddEdge(1, 2, 2); // 1 ---(2)---> 2
    a.AddEdge(2, 4, 1); // 2 ---(1)---> 4
    a.AddEdge(2, 3, 3); // 2 ---(3)---> 3
    a.AddEdge(3, 4, 5); // 3 ---(5)---> 4

    int maxFlow = pushRelabel(&a);
    printf("Flusso massimo: %d\n", maxFlow);

    return 0;
}