#include "Serial.hpp"
#include "../Graph.hpp"
#include "../Node.hpp"
#include "../DirectedEdge.hpp"
#include <cstdio>
#include <queue>
#include <cstdlib>
using std::queue;

void FordFulkersonSerial::InitCopyGraph() {
    vector<Node> nodes = this->original->GetNodes();

    for (Node i : nodes) {
        this->copy->AddNode();
    }

    for (Node i : nodes) {
        vector<DirectedEdge<Node>> * edges = i.GetEdges();

        for (DirectedEdge<Node> e : *edges) {
            //this->copy->AddEdgeToLastNode(e.GetEnd()->GetNodeNum(), e.GetMaxFlow());
            this->copy->AddEdge(i.GetNodeNum(), e.GetEnd()->GetNodeNum(), e.GetMaxFlow());
        }
    }
}

Path FordFulkersonSerial::BFS(Node * start, Node * end) {
    queue<Node *> qu;
    Path rtr = Path();
    vector<DirectedEdge<Node> *> parent_edge = vector<DirectedEdge<Node> *>(this->original->GetNodesNumber(), NULL);
    vector<bool> visited = vector<bool>(this->original->GetNodesNumber(), false);
    vector<DirectedEdge<Node>> * edges;
    Node * current = NULL;
    
    qu.push(start);
    while (!qu.empty() && current != end) {
        current = qu.front();
        qu.pop();

        edges = current->GetEdges();

        for (long unsigned int edge_idx = 0; edge_idx < edges->size(); edge_idx++) {

            DirectedEdge<Node> * edge = &edges->at(edge_idx);

            const int adj_num = edge->GetEnd()->GetNodeNum();

            if (!visited[adj_num] && edge->HasResidue()) {
                visited[adj_num] = true;
                parent_edge[adj_num] = edge;
                qu.push(edge->GetEnd());
            }
        }
    }

    if (parent_edge[end->GetNodeNum()] != NULL) {
        current = end;
        while (current != start) {
            DirectedEdge<Node> * pe = parent_edge[current->GetNodeNum()];
            rtr.AddEdge(pe);
            current = pe->GetStart();
        }
        
    }

    return rtr;
}

FordFulkersonSerial::FordFulkersonSerial(Graph *max_flow_graph) {
    this->original = max_flow_graph;
    this->copy = max_flow_graph;
    //this->copy = new Graph(this->original->GetSource()->GetNodeNum(), this->original->GetSilk()->GetNodeNum());
    //this->InitCopyGraph();
    
}

int FordFulkersonSerial::Solve()
{
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

FordFulkersonSerial::~FordFulkersonSerial() {
}

Path::Path() {
    this->edges = vector<DirectedEdge<Node> *>();
    this->min_flow = __INT_MAX__;
}

bool Path::IsEmpty() {
    return this->edges.empty();
}

void Path::AddEdge(DirectedEdge<Node> *edge) {
    if (edge->GetResidueFlow() < this->min_flow) {
        this->min_flow = edge->GetResidueFlow();
    }
    this->edges.push_back(edge);
}

int Path::IncreaseFlow() {
    for (auto i : this->edges) {
        i->IncreaseCurrentFlow(this->min_flow);
    }
    return this->min_flow;
}

Path::~Path() {
}

