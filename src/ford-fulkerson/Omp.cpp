#include "Omp.hpp"
#include <vector>
#include <queue>

using std:: queue;
using std::vector;

void FordFulkersonOmp::Expand(int adj_num, DirectedEdge<Node> * edge) {
    if (!this->visited[adj_num] && edge->HasResidue()) {  
        visited[adj_num] = true;
        parent_edge[adj_num] = edge;
        
        #pragma omp task
        this->Explore(edge->GetEnd());
    }
}

void FordFulkersonOmp::Explore(Node *node) {
    vector<DirectedEdge<Node>> * edges = node->GetEdges();

    for (long unsigned int edge_idx = 0; edge_idx < edges->size(); edge_idx++) {
        DirectedEdge<Node> * edge = &edges->at(edge_idx);
        const int adj_num = edge->GetEnd()->GetNodeNum();

        this->Expand(adj_num, edge);
    }
}

Path FordFulkersonOmp::BFS(Node *start, Node *end) {
    Path rtr = Path();
    this->parent_edge = vector<DirectedEdge<Node> *>(this->copy->GetNodesNumber(), NULL);
    this->visited = vector<bool>(this->copy->GetNodesNumber(), false);

    #pragma omp parallel default(none) shared(start)
    {
        #pragma omp single
        this->Explore(start);

    }

    if (parent_edge[end->GetNodeNum()] != NULL) {
        Node * current = end;
        while (current != start) {
            DirectedEdge<Node> * pe = parent_edge[current->GetNodeNum()];
            rtr.AddEdge(pe);
            current = pe->GetStart();
        }
        
    }

    return rtr;
}

FordFulkersonOmp::FordFulkersonOmp(Graph * max_flow_graph) : FordFulkersonSerial(max_flow_graph) {
}

int FordFulkersonOmp::Solve() {
    Node * source = this->copy->GetSource();
    Node * silk = this->copy->GetSilk();
    int max_flow = 0;

    Path bfs_path = this->BFS(source, silk);

    while (!bfs_path.IsEmpty()) {

        max_flow += bfs_path.IncreaseFlow();
        bfs_path = this->BFS(source, silk);
    
    }

    return max_flow;
}

FordFulkersonOmp::~FordFulkersonOmp() {
}