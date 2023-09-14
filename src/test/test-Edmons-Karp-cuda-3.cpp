#include "../edmons-karp/Cuda.cuh"
#include <cstdio>

int main() {
    Graph c = Graph(0, 11);
    c.AddNode();
    c.AddNode();
    c.AddNode();

    c.AddNode();
    c.AddNode();
    c.AddNode();

    c.AddNode();
    c.AddNode();
    c.AddNode();

    c.AddNode();
    c.AddNode();
    c.AddNode();
    
    c.AddEdge(0, 1, 1);
    c.AddEdge(0, 2, 1);
    c.AddEdge(0, 3, 1);
    c.AddEdge(0, 4, 1);
    c.AddEdge(0, 5, 1);
    c.AddEdge(0, 6, 1);
    c.AddEdge(0, 7, 1);

    c.AddEdge(1, 8, 1);
    c.AddEdge(1, 9, 1);
    c.AddEdge(2, 8, 1);
    c.AddEdge(3, 10, 1);
    c.AddEdge(4, 8, 1);
    c.AddEdge(4, 10, 1);
    c.AddEdge(5, 10, 1);
    c.AddEdge(6, 9, 1);
    c.AddEdge(6, 10, 1);
    c.AddEdge(7, 8, 1);

    c.AddEdge(8, 11, 4);
    c.AddEdge(9, 11, 2);
    c.AddEdge(10, 11, 4);


    EdmonsKarpCuda solver = EdmonsKarpCuda(&c);
    printf("Max flow: %d\n", solver.Solve());
    return 0;
}