#include "Graph.hpp"
#include "Node.hpp"
#include "DirectedEdge.hpp"

Graph::Graph(int source, int silk)
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

Graph * Graph::AddEdge(int start, int end, int max_flow) {
    if (this->highest_max_flow < max_flow) {
        this->highest_max_flow = max_flow;
    }
    this->edge_number++;
    this->nodes[start].AddEdge(&(this->nodes[end]), max_flow);
    return this;
}

Graph * Graph::AddEdgeToLastNode(int end, int max_flow) {
    return this->AddEdge( this->nodes.size() - 1, end, max_flow);
}

vector<Node> Graph::GetNodes() {
    // THIS IS TOTALLY UNSAFE, IT DOES NOT FOLLOW ENCASPULATION
    // BUT FOR THIS LIMITED USECASE CAN BE ACCEPTED
    // IT SHOULD RETURN A COPY
    return this->nodes;
}

Node *Graph::GetSource()
{
    return &(this->nodes[this->source]);
}

Node *Graph::GetSilk()
{
    return &(this->nodes[this->silk]);
}

int Graph::GetNodesNumber()
{
    return this->last_node_number;
}

int Graph::GetMaxFlow()
{
    return this->highest_max_flow;
}
