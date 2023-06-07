#include "Label.hpp"

NodaLabelable::NodaLabelable(int node_num) : Node(node_num) {
    this->label.flow = 0;
    this->label.from = NULL;
}

Node *NodaLabelable::GetNodeFrom()
{
    return this->label.from;
}

int NodaLabelable::GetFluxFrom()
{
    return this->label.flow;
}

void NodaLabelable::ReLabel(Node *from, int flow) {
    this->label.from = from;
    this->label.flow = flow;
}

bool NodaLabelable::IsLabelled()
{
    return this->label.from != NULL;
}

NodaLabelable::~NodaLabelable() {
}

LabelableGraph::LabelableGraph(Node * source, Node * silk) : Graph(source, silk) {
}

LabelableGraph::~LabelableGraph() {
}

const Node *LabelableGraph::AddNode() {
    Node * node = new NodaLabelable(this->last_node_number);
    this->last_node_number++;
    this->nodes.push_back(*node);
    return node;
}
