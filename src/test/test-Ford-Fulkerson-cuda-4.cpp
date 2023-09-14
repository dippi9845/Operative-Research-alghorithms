#include "../ford-fulkerson/Cuda.cuh"
#include <cstdio>

int main() {
   Graph d = Graph(1,6);
    d.AddNode();

    d.AddNode();
    d.AddNode();
    d.AddNode();
    d.AddNode();
    d.AddNode();
    d.AddNode();

    d.AddEdge(1, 2, 3);
    d.AddEdge(1, 3, 3);
    d.AddEdge(2, 3, 1);
    d.AddEdge(2, 5, 4);
    d.AddEdge(2, 4, 1);
    d.AddEdge(3, 5, 2);
    d.AddEdge(4, 6, 3);
    d.AddEdge(5, 4, 2);
    d.AddEdge(5, 6, 3);

    EdmonsKarpCuda solver = EdmonsKarpCuda(&d);
    printf("Max flow: %d\n", solver.Solve());
    return 0;
}