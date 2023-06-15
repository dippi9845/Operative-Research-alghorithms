#include "../Graph.hpp"
#include "../ford-fulkerson/Serial.hpp"
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
    
    FordFulkersonSerial solver = FordFulkersonSerial(&a);
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


    solver = FordFulkersonSerial(&b);
    printf("Max flow: %d\n", solver.Solve());

}