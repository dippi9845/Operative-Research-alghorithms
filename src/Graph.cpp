#include "Graph.hpp"

Graph::Graph() {
    this->last_node_number = 0;
    this->highest_max_flow = 0;
}

Graph::~Graph() {
}

const Node *Graph::AddNode()
{
    Node * node = new Node(this->last_node_number);
    this->last_node_number++;
    this->nodes.push_back(*node);
    return node;
}

Graph * Graph::AddEdge(const Node *start, const Node *end, int max_flow) {
    if (this->highest_max_flow < max_flow) {
        this->highest_max_flow = max_flow;
    }
    this->edge_number++;
    start->AddEdge(end, max_flow);
    return this;
}

Graph * Graph::AddEdgeToLastNode(const Node *end, int max_flow) {
    return this->AddEdge(&(this->nodes.back()), end, max_flow);
}

int Graph::GetNodesNumber()
{
    return this->last_node_number;
}

int Graph::GetMaxFlow()
{
    return this->highest_max_flow;
}
