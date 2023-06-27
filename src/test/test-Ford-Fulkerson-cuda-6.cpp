#include "../ford-fulkerson/Cuda.cuh"
#include <cstdio>

int main() {
    Graph e = Graph(1, 5);
    e.AddNode();

    e.AddNode();
    e.AddNode();
    e.AddNode();
    e.AddNode();
    e.AddNode();

    e.AddEdge(1, 3, 4);
    e.AddEdge(1, 4, 4);
    e.AddEdge(2, 1, 2);
    e.AddEdge(2, 3, 1);
    e.AddEdge(2, 4, 3);
    e.AddEdge(3, 5, 3);
    e.AddEdge(3, 4, 2);
    e.AddEdge(4, 5, 5);

    FordFulkersonCuda solver = FordFulkersonCuda(&e);
    printf("Max flow: %d\n", solver.Solve());
    return 0;
}