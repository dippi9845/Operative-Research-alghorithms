#include "Omp.hpp"
#include <vector>
#include <queue>

using std:: queue;
using std::vector;

void EdmonsKarpOmp::Expand(int adj_num, DirectedEdge<Node> * edge) {
    if (this->visited[adj_num] == 0 && edge->HasResidue()) {
        int old_visited = 0;
        #pragma omp atomic capture
        {
            visited[adj_num]++;
            old_visited = visited[adj_num];
        }
        if (old_visited == 1) {
            parent_edge[adj_num] = edge;
            #pragma omp task
            this->Explore(edge->GetEnd());

        }
    }
}

void EdmonsKarpOmp::Explore(Node *node) {
    vector<DirectedEdge<Node>> * edges = node->GetEdges();

    for (long unsigned int edge_idx = 0; edge_idx < edges->size(); edge_idx++) {
        DirectedEdge<Node> * edge = &edges->at(edge_idx);
        const int adj_num = edge->GetEnd()->GetNodeNum();

        this->Expand(adj_num, edge);
    }
}

Path EdmonsKarpOmp::BFS(Node *start, Node *end) {
    Path rtr = Path();
    this->parent_edge = vector<DirectedEdge<Node> *>(this->copy->GetNodesNumber(), NULL);
    this->visited = vector<int>(this->copy->GetNodesNumber(), 0);

    #pragma omp parallel default(none) shared(start)
    {
        this->Explore(start);

    }

    if (parent_edge[end->GetNodeNum()] != NULL) {
        Node * current = end;
        while (*current != *start) {
            DirectedEdge<Node> * pe = parent_edge[current->GetNodeNum()];
            rtr.AddEdge(pe);
            current = pe->GetStart();
        }
        
    }

    return rtr;
}

EdmonsKarpOmp::EdmonsKarpOmp(Graph * max_flow_graph) : EdmonsKarpSerial(max_flow_graph) {
}

int EdmonsKarpOmp::Solve() {
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

EdmonsKarpOmp::~EdmonsKarpOmp() {
}