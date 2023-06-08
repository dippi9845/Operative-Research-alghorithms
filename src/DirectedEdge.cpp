#include "DirectedEdge.hpp"

template <class T>
DirectedEdge<T>::DirectedEdge(T * start, T * end, int max_flow) {
    this->start = start;
    this->end = end;
    this->max_flow = max_flow;
    this->curent_flow = 0;
}

template <class T>
int DirectedEdge<T>::IncreaseCurrentFlow(int flow) {
    if (this->curent_flow + flow <= this->max_flow){
        this->curent_flow += flow;
    }
    
    return this->curent_flow;
}

template <class T>
int DirectedEdge<T>::GetCurrentFlow() {
    return this->curent_flow;
}

template <class T>
T * DirectedEdge<T>::GetEnd() {
    return this->end;
}

template <class T>
T * DirectedEdge<T>::GetStart() {
    return this->start;
}

template <class T>
int DirectedEdge<T>::GetMaxFlow() {
    return this->max_flow;
}

template <class T>
bool DirectedEdge<T>::HasResidue() {
    return this->curent_flow < this->max_flow;
}

template <class T>
int DirectedEdge<T>::GetResidueFlow() {
    return this->max_flow - this->curent_flow;
}

template <class T>
DirectedEdge<T>::~DirectedEdge()
{
}
