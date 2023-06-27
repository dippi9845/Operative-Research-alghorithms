#include "../ford-fulkerson/Cuda.cuh"
#include <cstdio>

int main() {
    const int expected = 6;
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
    
    FordFulkersonCuda solver = FordFulkersonCuda(&a);
    int flow_found = solver.Solve();
    printf("Max flow: %d Expepected %d : %d\n", flow_found, expected, flow_found == expected);

    return 0;
}