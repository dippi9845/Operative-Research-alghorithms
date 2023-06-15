#include "../Graph.hpp"
#include "../ford-fulkerson/Serial.hpp"
#include <stdio.h>

int main() {
    // taken from https://www.programiz.com/dsa/ford-fulkerson-algorithm
    Graph a = Graph(0, 5);
    a.AddNode();
    a.AddNode();
    a.AddNode();
    a.AddNode();
    a.AddNode();
    a.AddNode();
    
    a.AddEdge(0, 1, 8); // S -> A
    a.AddEdge(0, 2, 3); // S -> D
    a.AddEdge(1, 3, 9); // A -> B
    a.AddEdge(2, 3, 7); // D -> B
    a.AddEdge(3, 5, 2); // B -> T
    a.AddEdge(2, 4, 4); // D -> C
    a.AddEdge(4, 5, 5); // C -> T
    
    /*
    a.AddEdge(0, 1, 8);
    a.AddEdge(1, 3, 3);
    a.AddEdge(3, 5, 8);
    */
    FordFulkersonSerial solver = FordFulkersonSerial(&a);
    printf("Max flow: %d\n", solver.Solve());

}