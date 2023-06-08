#ifndef NODE_H
#define NODE_H

#include "DirectedEdge.hpp"
#include <vector>
using std::vector;

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