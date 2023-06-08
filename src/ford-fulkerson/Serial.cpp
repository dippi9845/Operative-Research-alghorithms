#include "Serial.hpp"
#include "../Graph.hpp"
#include "../Node.hpp"
#include "../DirectedEdge.hpp"
#include <queue>
using std::queue;

void FordFulkersonSerial::InitCopyGraph() {
    vector<Node> nodes = this->original->GetNodes();

    for (Node i : nodes) {
        this->copy->AddNode();
        vector<DirectedEdge<Node>> * edges = i.GetEdges();

        for (DirectedEdge<Node> e : *edges) {
            this->copy->AddEdgeToLastNode(e.GetEnd()->GetNodeNum(), e.GetMaxFlow());
        }
    }
}

Path FordFulkersonSerial::BFS(Node * start, Node * end) {
    queue<Node *> qu;
    Path rtr = Path();
    vector<DirectedEdge<Node> *> parent_edge = vector<DirectedEdge<Node> *>(this->original->GetNodesNumber(), nullptr);
    vector<bool> visited = vector<bool>(this->original->GetNodesNumber(), false);

    qu.push(start);
    while (!qu.empty()) {
        Node * current = qu.front();
        qu.pop();

        if (*current == *end) {
            while (current != nullptr) {
                DirectedEdge<Node> * pe = parent_edge[current->GetNodeNum()];
                rtr.AddEdge(pe);
                current = pe->GetStart();
            }
            
        }

        vector<DirectedEdge<Node>> edges = *current->GetEdges();

        for (DirectedEdge<Node> edge : edges) {
            const int node_num = edge.GetEnd()->GetNodeNum();
            if (!visited[node_num] && edge.HasResidue()) {
                visited[node_num] = true;
                parent_edge[node_num] = &edge;
                qu.push(edge.GetEnd());
            }
        }
    }

    return rtr;
}

FordFulkersonSerial::FordFulkersonSerial(Graph *max_flow_graph) {
    this->original = max_flow_graph;
    this->copy = new Graph(this->original->GetSource()->GetNodeNum(), this->original->GetSilk()->GetNodeNum());
    this->InitCopyGraph();
    
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
    if (edge->GetMaxFlow() < this->min_flow) {
        this->min_flow = edge->GetMaxFlow();
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

