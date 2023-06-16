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

    solver = FordFulkersonOmp(&d);
    printf("Max flow: %d\n", solver.Solve());

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

    solver = FordFulkersonOmp(&e);
    printf("Max flow: %d\n", solver.Solve());

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

    solver = FordFulkersonOmp(&f);
    printf("Max flow: %d\n", solver.Solve());

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

    solver = FordFulkersonOmp(&g);
    printf("Max flow: %d\n", solver.Solve());
}