#include "../Graph.hpp"
#include "../ford-fulkerson/Omp.hpp"
#include <cstdio>

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
    
    FordFulkersonOmp solver = FordFulkersonOmp(&a);
    printf("Max flow: %d\n", solver.Solve());

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


    solver = FordFulkersonOmp(&b);
    printf("Max flow: %d\n", solver.Solve());


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


    solver = FordFulkersonOmp(&c);
    printf("Max flow: %d\n", solver.Solve());
}