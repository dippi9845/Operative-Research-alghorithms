#include "../edmons-karp/Cuda.cuh"
#include <cstdio>

int main() {
    Graph g = Graph(1, 6);
    g.AddNode();

    g.AddNode();
    g.AddNode();
    g.AddNode();
    g.AddNode();
    g.AddNode();
    g.AddNode();

    g.AddEdge(1, 3, 2);
    g.AddEdge(1, 5, 4);
    g.AddEdge(2, 1, 2);
    g.AddEdge(2, 3, 2);
    g.AddEdge(2, 4, 3);
    g.AddEdge(3, 5, 4);
    g.AddEdge(3, 4, 1);
    g.AddEdge(4, 6, 5);
    g.AddEdge(5, 4, 2);
    g.AddEdge(5, 6, 2);

    EdmonsKarpCuda solver = EdmonsKarpCuda(&g);
    printf("Max flow: %d\n", solver.Solve());
    return 0;
}