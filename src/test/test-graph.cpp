#include "../Graph.hpp"
#include <cstdio>

int main() {
    Graph a(0, 2);
    a.AddNode();
    a.AddNode();
    a.AddNode();

    a.AddEdge(0, 1, 8);
    a.AddEdge(1, 2, 9);
    a.AddEdge(2, 0, 10);

    vector<Node> nodes = a.GetNodes();
    Node * first = &nodes[0];
    Node * second = &nodes[1];
    Node * third = &nodes[2];


    if (first->GetNodeNum() == 0) {
        printf("Node 1 OK\n");

        vector<DirectedEdge<Node>> *edge = first->GetEdges();
        if (edge->at(0).GetStart()->GetNodeNum() == 0 && edge->at(0).GetEnd()->GetNodeNum() == 1 && edge->at(0).GetMaxFlow() == 8) {
            printf("Edge 1 OK\n");
        }
        else {
            printf("Edge 1 NO\n");
        }
    }
    else {
        printf("Node 1 NO\n");
    }

    if (second->GetNodeNum() == 1) {
        printf("Node 2 OK\n");

        vector<DirectedEdge<Node>> *edge = second->GetEdges();
        if (edge->at(0).GetStart()->GetNodeNum() == 1 && edge->at(0).GetEnd()->GetNodeNum() == 2 && edge->at(0).GetMaxFlow() == 9) {
            printf("Edge 2 OK\n");
        }
        else {
            printf("Edge 2 NO\n");
        }
    }
    else {
        printf("Node 2 NO\n");
    }

    if (third->GetNodeNum() == 2) {
        printf("Node 3 OK\n");

        vector<DirectedEdge<Node>> *edge = third->GetEdges();
        if (edge->at(0).GetStart()->GetNodeNum() == 2 && edge->at(0).GetEnd()->GetNodeNum() == 0 && edge->at(0).GetMaxFlow() == 10) {
            printf("Edge 3 OK\n");
        }
        else {
            printf("Edge 3 NO\n");
        }
    }
    else {
        printf("Node 3 NO\n");
    }
}