#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H

template <class T> class DirectedEdge {
private:
    T * start;
    T * end;
    int max_flow;
    int curent_flow;

public:
    DirectedEdge<T>(T * start, T * end, int max_flow);
    ~DirectedEdge<T>();

    int IncreaseCurrentFlow(int flow);
    int GetCurrentFlow();
    int GetMaxFlow();
    T * GetStart();
    T * GetEnd();
    bool HasResidue();
    int GetResidueFlow();

};

#endif