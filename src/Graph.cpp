#include "Graph.hpp"
#include "Node.hpp"
#include "DirectedEdge.hpp"
#include <cstdlib>
#include <ctime>

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

bool GraphGenerator::AddEdgeWithRandomMaxFlow(int start, int end) {
    //this->generated.AddEdge(start, end, rand() % 50 + 1);
    this->adiacency_matrix[start * this->node_num + end] = rand() % 50 + 1;
    return true;
}

void GraphGenerator::ApplyMatrix() {
    for (int i = 0; i < this->node_num; i++) {
        for( int j = 0; j < this->node_num; j++) {
            
            const int flux = this->adiacency_matrix[i * this->node_num + j];
            if (flux > 0) {
                this->generated.AddEdge(i, j, flux);
            }
        }
    }
}


Graph GraphGenerator::RandomGenerate() { 
    int source = rand() % this->node_num;
    int silk = rand() % this->node_num;
    int remaining_edges = this->edge_num;

    this->generated = Graph(source, silk);

    /* add all nodes */
    for (int i = 0; i < this->node_num; i++) {
        this->generated.AddNode();
    }

    /* if u want to ensure a path from source amd silk */
    if (this->min_one_path) {
        int intermediate_nodes = rand() % this->node_num;

        if (intermediate_nodes == 0) {
            this->AddEdgeWithRandomMaxFlow(source, silk);
        }

        else {
            intermediate_nodes--;
            int first_node = rand() % this->node_num;
            int last_node = first_node;
            this->AddEdgeWithRandomMaxFlow(source, first_node);

            for (int i = 0; i < intermediate_nodes && remaining_edges > 0; i++) {
                last_node = rand() % this->node_num;
                this->AddEdgeWithRandomMaxFlow(first_node, last_node);
                remaining_edges--;
                first_node = last_node;
            }

            this->AddEdgeWithRandomMaxFlow(last_node, silk);
        }

    }

    int current_node = 0;

    while (remaining_edges > 0) {
        int edges_to_add = rand() % 4 + 1; // avoid zero
        
        for (int i = 0; i < edges_to_add && remaining_edges > 0; i++) {
            int random_node = rand() % this->node_num;
            this->AddEdgeWithRandomMaxFlow(current_node, random_node);
            
            remaining_edges--;
        }

        current_node++;
        current_node %= this->node_num;

    }
    
    return this->generated;
}


void GraphGenerator::FillGenerate() {

    this->generated = Graph(0, this->node_num);

    /* add all nodes */
    for (int i = 0; i < this->node_num; i++) {
        this->generated.AddNode();
    }
    
    for (int i = 0; i < this->node_num; i++) {
        for( int j = 0; j < this->node_num; j++) {
            if (i != j) {
                this->adiacency_matrix[i * this->node_num + j] = rand() % 50 + 1;
            }
        }
    }
}

GraphGenerator::GraphGenerator() {
    this->edge_num = 0;
    this->node_num = 0;
    this->min_one_path = true;
    this->unique_edge = false;
    this->seed = 42;
}

GraphGenerator::~GraphGenerator(){
}

GraphGenerator * GraphGenerator::NodeNumber(int node_number) {
    this->node_num = node_number;
    return this;
}

GraphGenerator * GraphGenerator::EdgeNumber(int edge_number){
    this->edge_num = edge_number;
    return this;
}

GraphGenerator *GraphGenerator::MinOnePath(bool condition)
{
    this->min_one_path = condition;
    return this;
}

GraphGenerator * GraphGenerator::Seed(unsigned int seed) {
    this->seed = seed;
    return this;
}

GraphGenerator * GraphGenerator::SeedByTime() {
    return this->Seed(time(NULL));
}

GraphGenerator *GraphGenerator::SetUniquesEdges(bool flag) {
    this->unique_edge = flag;
    return this;
}



Graph GraphGenerator::Generate() {
    srand(this->seed);
    this->adiacency_matrix = (int *)calloc(this->node_num * this->node_num, sizeof(int));

    if (this->edge_num == 0) {
        this->FillGenerate();
    }
    else {
        this->RandomGenerate();
    }

    this->ApplyMatrix();
    free(this->adiacency_matrix);
    return this->generated;
}