#include "../ford-fulkerson/Cuda.cuh"
#include <cstdio>

int main() {
    Graph b = Graph(1, 9);
    b.AddNode();
    b.AddNode();
    b.AddNode();
    b.AddNode();
    b.AddNode();
    b.AddNode();
    b.AddNode();
    b.AddNode();
    b.AddNode();
    b.AddNode();
    
    b.AddEdge(1, 2, 14);
    b.AddEdge(1, 4, 23);
    b.AddEdge(2, 4, 9);
    b.AddEdge(2, 3, 10);
    b.AddEdge(3, 5, 12);
    b.AddEdge(3, 8, 18);
    b.AddEdge(4, 5, 26);
    b.AddEdge(5, 6, 25);
    b.AddEdge(5, 7, 4);
    b.AddEdge(6, 7, 7);
    b.AddEdge(6, 8, 8);
    b.AddEdge(7, 9, 15);
    b.AddEdge(8, 9, 20);


    FordFulkersonCuda solver = FordFulkersonCuda(&b);
    printf("Max flow: %d\n", solver.Solve());
    return 0;
}