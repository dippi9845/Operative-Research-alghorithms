#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.hpp"
using std::vector;

class Graph {
private:
    int last_node_number;
    int highest_max_flow;
    int edge_number;
    vector<Node> nodes;

public:
    Graph();
    ~Graph();

    const Node * AddNode();
    Graph * AddEdge(const Node * start, const Node * end, int max_flow);
    Graph * AddEdgeToLastNode(const Node * end, int max_flow);
    int GetNodesNumber();
    int GetMaxFlow();
};


#endif