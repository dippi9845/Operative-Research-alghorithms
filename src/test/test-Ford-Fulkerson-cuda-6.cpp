#include "../ford-fulkerson/Cuda.cuh"
#include <cstdio>

int main() {
    Graph f = Graph(1, 6);
    f.AddNode();

    f.AddNode();
    f.AddNode();
    f.AddNode();
    f.AddNode();
    f.AddNode();
    f.AddNode();

    f.AddEdge(1, 2, 5);
    f.AddEdge(1, 3, 5);
    f.AddEdge(2, 3, 5);
    f.AddEdge(2, 4, 5);
    f.AddEdge(2, 5, 5);
    f.AddEdge(3, 5, 5);
    f.AddEdge(5, 4, 5);
    f.AddEdge(5, 6, 5);
    f.AddEdge(4, 6, 5);

    EdmonsKarpCuda solver = EdmonsKarpCuda(&f);
    printf("Max flow: %d\n", solver.Solve());
    return 0;
}