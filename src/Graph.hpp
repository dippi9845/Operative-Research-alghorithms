#ifndef GRAPH_H
#define GRAPH_H

#include "Node.hpp"
#include <vector>
using std::vector;

class Graph {
private:
    int highest_max_flow;
    int edge_number;
    int source;
    int silk;

protected:
    int last_node_number;
    vector<Node> nodes;

public:
    Graph(int source, int silk);
    ~Graph();

    const Node * AddNode();
    Graph * AddEdge(int start, int end, int max_flow);
    Graph * AddEdgeToLastNode(int end, int max_flow);
    
    vector<Node> GetNodes();
    Node * GetSource();
    Node * GetSilk();

    int GetNodesNumber();
    int GetMaxFlow();
};


#endif