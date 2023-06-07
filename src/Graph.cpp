#include "Graph.hpp"

Graph::Graph(Node * source, Node * silk)
{
    this->source = source;
    this->silk = silk;
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

Graph * Graph::AddEdge(Node *start, const Node *end, int max_flow) {
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

vector<Node> Graph::GetNodes() {
    // THIS IS TOTALLY UNSAFE, IT DOES NOT FOLLOW ENCASPULATION
    // BUT FOR THIS LIMITED USECASE CAN BE ACCEPTED
    // IT SHOULD RETURN A COPY
    return this->nodes;
}

Node *Graph::GetSource()
{
    return this->source;
}

Node *Graph::GetSilk()
{
    return this->source;
}

int Graph::GetNodesNumber()
{
    return this->last_node_number;
}

int Graph::GetMaxFlow()
{
    return this->highest_max_flow;
}
