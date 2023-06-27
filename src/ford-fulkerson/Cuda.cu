#include "Cuda.cuh"
#include <cstdio>

#define CUDA_SAFE_CALL(call)                                                                       \
    do {                                                                                           \
        cudaError_t cudaStatus = (call);                                                           \
        if (cudaStatus != cudaSuccess) {                                                            \
            printf("CUDA Error at %s:%d -- %s\n", __FILE__, __LINE__, cudaGetErrorString(cudaStatus)); \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (0)

#define THREADS 1024
#define BLOCKS(X) (X + THREADS - 1) / THREADS
#define UNREACHED -1

__managed__ int d_nodes_num;
__managed__ int mng_pushed_num;

__managed__ int mng_flow;
__managed__ int mng_path_len;

__global__ void IncreaseFlowKernel(int * start_node, int * destination_node, int * flow_matrix) {
    const int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if ( tid < mng_path_len ) {
        const int start = start_node[tid];
        const int dest = destination_node[tid];
        const int flow_idx = start * d_nodes_num + dest;
        flow_matrix[flow_idx] -= mng_flow;
    }
}

__global__ void FindPath(int end, int * parent_node, int * start_node, int * destination_node, int * flow_matrix) {
    int current = end;
    mng_path_len = 0;
    mng_flow = __INT_MAX__;

    while (parent_node[current] != UNREACHED) {
        const int start = parent_node[current];
        const int destination = current;
        start_node[mng_path_len] = start;
        destination_node[mng_path_len] = destination;

        const int flow_idx = start * d_nodes_num + destination;

        if (mng_flow > flow_matrix[flow_idx]) {
            mng_flow = flow_matrix[flow_idx];
        }

        mng_path_len++;

        current = parent_node[current];
    }
}

__global__ void ComputeNextQueue(int to_pop_num,  int * pop_queue, int * push_queue, int * flow_matrix, unsigned int * visited, int *parent_node) {
    const int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < to_pop_num) {
        const int current = pop_queue[tid];

        for (int adj = 0;  adj < d_nodes_num; adj++) {
            const int adj_matrix_index = current * d_nodes_num + adj;
            if (flow_matrix[adj_matrix_index] > 0 && visited[adj] == 0) {
                if (atomicAdd(visited + adj, 1) == 0) {
                    visited[adj] = true;
                    const int push_at = atomicAdd(&mng_pushed_num, 1);
                    push_queue[push_at] = adj;
                    atomicExch(parent_node + adj, current);

                }
            }
        }
    }
}



void FordFulkersonCuda::InitializeGraphOnDevice(Graph *g)
{
    const int nodes_num = g->GetNodesNumber();
    unsigned int bytes_matrix = nodes_num * nodes_num * sizeof(nodes_num);
    vector<Node> nodes = g->GetNodes();

    CUDA_SAFE_CALL(cudaMalloc((void **)&d_flow_matrix, bytes_matrix));
    CUDA_SAFE_CALL(cudaMemset(d_flow_matrix, 0, bytes_matrix));
    cudaDeviceSynchronize();

    for (int start = 0; start < nodes_num; start++) {
        for (DirectedEdge<Node> e : *(nodes[start].GetEdges())) {
            const int end = e.GetEnd()->GetNodeNum();
            const int max_flow = e.GetMaxFlow();
            const int edge_index = start * nodes_num + end;
            int *d_edge_index = this->d_flow_matrix + edge_index;

            CUDA_SAFE_CALL(cudaMemcpy(d_edge_index, &max_flow, sizeof(max_flow), cudaMemcpyHostToDevice));
        }
    }
}

void FordFulkersonCuda::InitializeQueues() {
    CUDA_SAFE_CALL(cudaMalloc((void **)&this->d_first_queue, this->nodes_num * sizeof(int)));
    CUDA_SAFE_CALL(cudaMalloc((void **)&this->d_second_queue, this->nodes_num * sizeof(int)));
}

void FordFulkersonCuda::InitializeStartDestination() {
    CUDA_SAFE_CALL(cudaMalloc((void **)&this->d_start_node, this->nodes_num * sizeof(int)));
    CUDA_SAFE_CALL(cudaMalloc((void **)&this->d_destination_node, this->nodes_num * sizeof(int)));
}

void FordFulkersonCuda::InitializeParentNode() {
    CUDA_SAFE_CALL(cudaMalloc((void **)&this->d_parent_node, this->nodes_num * sizeof(int)));
    CUDA_SAFE_CALL(cudaMemset(this->d_parent_node, UNREACHED, this->nodes_num * sizeof(int)));
}


void FordFulkersonCuda::InitializeVisited() {
    CUDA_SAFE_CALL(cudaMalloc((void **)&this->d_visited, this->nodes_num * sizeof(unsigned int)));
    CUDA_SAFE_CALL(cudaMemset(this->d_visited, 0, this->nodes_num * sizeof(bool)));
}


bool FordFulkersonCuda::BFS(Node *start, Node *end) {
    int *d_pop_queue = this->d_first_queue;
    int *d_push_queue = this->d_second_queue;
    const int end_num = end->GetNodeNum();

    CUDA_SAFE_CALL(cudaMemset(this->d_parent_node + end_num, UNREACHED, sizeof(int)));

    int start_num = start->GetNodeNum();
    CUDA_SAFE_CALL(cudaMemcpy(d_pop_queue, &start_num, sizeof(int), cudaMemcpyHostToDevice));
    CUDA_SAFE_CALL(cudaMemset(d_visited, 0, sizeof(unsigned int) * this->nodes_num));
    CUDA_SAFE_CALL(cudaMemset(d_visited + start_num, 1, sizeof(bool)));


    mng_pushed_num = 1;

    CUDA_SAFE_CALL(cudaDeviceSynchronize());

    while (mng_pushed_num > 0) {
        const int pop_num = mng_pushed_num;
        mng_pushed_num = 0;

        ComputeNextQueue<<<BLOCKS(pop_num), THREADS>>>(pop_num, d_pop_queue, d_push_queue, d_flow_matrix, d_visited, d_parent_node);

        CUDA_SAFE_CALL(cudaDeviceSynchronize());

        int * tmp = d_pop_queue;
        d_pop_queue = d_push_queue;
        d_push_queue = tmp;
    }

    FindPath<<<1,1>>>(end_num, d_parent_node, d_start_node, d_destination_node, d_flow_matrix);
    CUDA_SAFE_CALL(cudaDeviceSynchronize());

    return mng_path_len > 0;
}


FordFulkersonCuda::FordFulkersonCuda(Graph * g) {
    this->graph = g;
    this->nodes_num = g->GetNodesNumber();
    this->InitializeGraphOnDevice(g);
    this->InitializeQueues();
    this->InitializeParentNode();
    this->InitializeVisited();
    this->InitializeStartDestination();
    cudaDeviceSynchronize();

    d_nodes_num = this->nodes_num;
}


int FordFulkersonCuda::Solve() {
    Node * source = this->graph->GetSource();
    Node * sink = this->graph->GetSilk();
    int max_flow = 0;

    while (this->BFS(source, sink)) {
        IncreaseFlowKernel<<<BLOCKS(mng_path_len), THREADS>>>(d_start_node, d_destination_node, d_flow_matrix);
        max_flow += mng_flow;
    }

    return max_flow;
}


FordFulkersonCuda::~FordFulkersonCuda() {
    CUDA_SAFE_CALL(cudaFree(d_flow_matrix));
    CUDA_SAFE_CALL(cudaFree(d_parent_node));
    CUDA_SAFE_CALL(cudaFree(d_visited));
    CUDA_SAFE_CALL(cudaFree(d_first_queue));
    CUDA_SAFE_CALL(cudaFree(d_second_queue));
    CUDA_SAFE_CALL(cudaFree(d_destination_node));
    CUDA_SAFE_CALL(cudaFree(d_start_node));
    CUDA_SAFE_CALL(cudaDeviceSynchronize());
}