#include "Node.hpp"

Node::Node(int node_num){
    this->node_num = node_num;
    this->edges = vector<DirectedEdge>();
}

int Node::GetNodeNum() {
    return this->node_num;
}

vector<DirectedEdge> * Node::GetEdges() {
    // THIS IS TOTALLY UNSAFE, IT DOES NOT FOLLOW ENCASPULATION
    // BUT FOR THIS LIMITED USECASE CAN BE ACCEPTED
    // IT SHOULD RETURN A COPY
    return &(this->edges);
}

void Node::AddEdge(const Node *end, int max_flow) {
    this->edges.push_back(DirectedEdge(this, end, max_flow));
}

Node::~Node() {
}

