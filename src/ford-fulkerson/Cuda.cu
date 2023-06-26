#include "Cuda.cuh"

#define THREADS 1024
#define BLOCKS(X) (X + THREADS - 1) / THREADS
#define UNREACHED -1


__global__ int FordFulkersonCuda::ComputeNextQueue(int to_pop_num,  int * pop_queue, int * push_queue, int * flow_matrix, bool * visited, int *parent_node) {
    // push_queue attualmente ci pensa la cpu
    // senò il primo thread che entra
    const int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < to_pop_num) {
        const int current = pop_queue[tid];
        for (int adj = 0;  adj < d_nodes_num; adj++) {
            const int adj_matrix_index = current * d_nodes_num + adj;

            if (flow_matrix[adj_matrix_index] > 0 && !visited[adj]) {
                const int push_at = atomicAdd(&pushed_num, 1) - 1;
                push_queue[push_at] = adj;
                atomicExch(parent_node + adj, current);
                visited[adj] = true;
            }
        }
    }

    return pushed_num;
}


void FordFulkersonCuda::InitializeGraphOnDevice(Graph *g)
{
    const int nodes_num = g->GetNodesNumber();
    unsigned int bytes_matrix = nodes_num * nodes_num * sizeof(nodes_num);
    vector<Node> nodes = g->GetNodes();

    cudaMalloc((void **)this->d_flow_matrix, bytes_matrix);
    cudaMemset((void **)this->d_flow_matrix, 0, bytes_matrix);
    cudaDeviceSynchronize();

    for (int start = 0; start < nodes_num; start++) {
        
        for (DirectedEdge<Node> e : *(nodes[start].GetEdges())) {
            const int end = e.GetEnd()->GetNodeNum();
            const int max_flow = e.GetMaxFlow();
            const int edge_index = start * nodes_num + end;
            int *d_edge_index = this->d_flow_matrix + edge_index;

            cudaMemset((void **)d_edge_index, max_flow, sizeof(max_flow));
        }
    }
}

void FordFulkersonCuda::InitializeParentNode() {
    cudaMalloc((void **)this->d_parent_node, this->nodes_num * sizeof(int));
    cudaMemset((void **)this->d_parent_node, UNREACHED, this->nodes_num * sizeof(int));
}


void FordFulkersonCuda::InitializeVisited() {
    cudaMalloc((void **)this->d_visited, this->nodes_num * sizeof(bool));
    cudaMemset((void **)this->d_visited, false, this->nodes_num * sizeof(bool));
}


int FordFulkersonCuda::FindMinFlow() {
    /* computes min flow in path found */
    int min_flow = 0;

    return min_flow;
}


PathCuda FordFulkersonCuda::BFS(Node *start, Node *end) {
    int *d_pop_queue = this->d_first_queue;
    int *d_push_queue = this->d_second_queue;
    const int end_num = end->GetNodeNum();

    cudaMemset((void **)this->d_parent_node + end_num, UNREACHED, sizeof(int));
    
    const int start_num = start->GetNodeNum();
    cudaMemset((void **)d_pop_queue, start_num, sizeof(start_num));

    this->pushed_num = 1;

    cudaDeviceSynchronize();

    while (this->pushed_num > 0) {
        const int pop_num = this->pushed_num;
        this->pushed_num = 0;

        ComputeNextQueue<<<BLOCKS(pop_num), THREADS>>>(pop_num, d_pop_queue, d_push_queue, d_flow_matrix, d_visited, d_parent_node);
        
        cudaDeviceSynchronize();

        int * tmp = d_pop_queue;
        d_pop_queue = d_push_queue;
        d_push_queue = tmp;
    }

    return PathCuda(end_num);
}


FordFulkersonCuda::FordFulkersonCuda(Graph * g) : FordFulkersonSerial(g) {
    this->nodes_num = g->GetNodesNumber();
    this->InitializeGraphOnDevice(g);
    this->InitializeParentNode();
    this->InitializeVisited();
    cudaDeviceSynchronize();

    this->d_nodes_num = this->nodes_num;
}


int FordFulkersonCuda::Solve() {
    Node * source = this->copy->GetSource();
    Node * sink = this->copy->GetSilk();
    int max_flow = 0;
    
    PathCuda bfs_path = this->BFS(source, sink);

    while (!bfs_path.IsEmpty()) {

        max_flow += bfs_path.IncreaseFlow();
        bfs_path = this->BFS(source, sink);
    
    }

    return max_flow;
}


FordFulkersonCuda::~FordFulkersonCuda() {
}

__global__ int PathCuda::IncreaseFlowKernel(int path_len) {
}

__global__ int PathCuda::FindPath(int end) {
    int len = 0;

}

PathCuda::PathCuda(int end) {
    this->path_length = 0;
    int current_node = end;
    cudaMalloc((void **)this->d_min_flow, sizeof(int));
    cudaMemset(this->d_min_flow, __INT_MAX__, sizeof(int));

    this->path_length = FindPath<<<1,1>>>(end);
    
}

bool PathCuda::IsEmpty() {
    return this->path_length == 0;
}

int PathCuda::IncreaseFlow() {
    return IncreaseFlowKernel<<<BLOCKS(path_length), THREADS>>>(this->path_length);
}

PathCuda::~PathCuda() {
    cudaFree(this->d_min_flow);
}