#include "DirectedEdge.hpp"
#include "Node.hpp"

Node::Node(int node_num){
    this->node_num = node_num;
    this->edges = vector<DirectedEdge<Node>>();
}

int Node::GetNodeNum() {
    return this->node_num;
}

vector<DirectedEdge<Node>> * Node::GetEdges() {
    // THIS IS TOTALLY UNSAFE, IT DOES NOT FOLLOW ENCASPULATION
    // BUT FOR THIS LIMITED USECASE CAN BE ACCEPTED
    // IT SHOULD RETURN A COPY
    return &(this->edges);
}

void Node::AddEdge(Node *end, int max_flow) {
    this->edges.push_back(DirectedEdge<Node>(this, end, max_flow));
}

bool Node::operator==(Node n)
{
    return this->node_num == n.node_num;
}

Node::~Node() {
}

