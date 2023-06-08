#include "DirectedEdge.hpp"
#include <vector>
using std::vector;

#ifndef NODE_H
#define NODE_H


class Node {

private:
    int node_num;
    vector<DirectedEdge<Node>> edges;

public:
    Node(int nodeNum);
    ~Node();
    
    int GetNodeNum();

    vector<DirectedEdge<Node>> * GetEdges();

    void AddEdge(Node * end, int max_flow);
    bool operator==(Node n);

};

#endif