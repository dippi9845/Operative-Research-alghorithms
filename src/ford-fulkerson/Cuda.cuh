#ifndef FORD_FULKERSON_CUDA
#define FORD_FULKERSON_CUDA

#include "Serial.hpp"

class PathCuda
{
private:
    int * d_min_flow;
    int path_length;

    __global__ int IncreaseFlowKernel(int path_len);
    __global__ int FindPath(int end);
    
public:
    PathCuda(int end);
    bool IsEmpty();
    int IncreaseFlow();
    ~PathCuda();
};


class FordFulkersonCuda : FordFulkersonSerial {
    private:
        int *d_flow_matrix;
        int *d_parent_node;
        bool *d_visited;
        int *d_first_queue;
        int *d_second_queue;

        /*
            Array containing edges to increase the flow
        */
        int *d_path;

        int nodes_num;
        __managed__ int pushed_num = 0;
        __constant__ int d_nodes_num;

        /* prova a ridurre il numero di parametri */
        __global__ int ComputeNextQueue(int to_pop_num,  int * pop_queue, int * push_queue, int * flow_matrix, bool * visited, int *parent_node); 

        void InitializeGraphOnDevice(Graph *g);
        void InitializeParentNode();
        void InitializeVisited();
        int FindMinFlow();
        PathCuda BFS(Node * start, Node * end);
        
    public:
        FordFulkersonCuda(Graph * g);
        int Solve();
        ~FordFulkersonCuda();
};

#endif