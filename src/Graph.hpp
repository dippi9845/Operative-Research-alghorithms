#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.hpp"
using std::vector;

class Graph {
private:
    int highest_max_flow;
    int edge_number;
    Node * source;
    Node * silk;

protected:
    int last_node_number;
    vector<Node> nodes;

public:
    Graph(Node * source, Node * silk);
    ~Graph();

    const Node * AddNode();
    Graph * AddEdge(Node * start, const Node * end, int max_flow);
    Graph * AddEdgeToLastNode(const Node * end, int max_flow);
    
    vector<Node> GetNodes();
    Node * GetSource();
    Node * GetSilk();

    int GetNodesNumber();
    int GetMaxFlow();
};


#endif