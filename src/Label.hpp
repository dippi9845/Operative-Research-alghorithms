#ifndef LABEL_H
#define LABEL_H
#include "Node.hpp"
#include "Graph.hpp"

/*
    The label describe, where it come from and which amount of flow
*/
struct Label {
    Node * from;
    int flow;
};


class NodaLabelable : public Node {
private:
    Label label;

public:
    NodaLabelable(int node_num);

    Node * GetNodeFrom();
    int GetFluxFrom();

    void ReLabel(Node * from, int flow);
    bool IsLabelled();

    ~NodaLabelable();
};

class LabelableGraph : public Graph {
public:
    LabelableGraph(Node * source, Node * silk);
    ~LabelableGraph();
    const Node * AddNode();
};


#endif