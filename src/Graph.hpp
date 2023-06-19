#include "Node.hpp"
#include <vector>
using std::vector;

#ifndef GRAPH_H
#define GRAPH_H


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

class GraphGenerator {
private:
    int node_num;
    int edge_num;
    bool min_one_path;
    unsigned int seed;
    Graph generated = Graph(0, 0);

    Graph * AddEdgeWithRandomMaxFlow(int start, int end);

public:
    GraphGenerator();
    GraphGenerator * NodeNumber(int node_number);
    GraphGenerator * EdgeNumber(int edge_number);
    GraphGenerator * MinOnePath(bool condition);
    GraphGenerator * Seed(unsigned int seed);
    GraphGenerator * SeedByTime();
    Graph Generate();
    ~GraphGenerator();
};


#endif