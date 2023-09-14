#ifndef FORD_FULKERSON_CUDA
#define FORD_FULKERSON_CUDA

#include "Serial.hpp"

class EdmonsKarpCuda {
    private:
        /*
            Matrix, containing all the flows
        */
        int *d_flow_matrix;
        
        /*
            array containing the parent node for each node, -1 otherwise
        */
        int *d_parent_node;

        /*
            array that tells if a node is visited
        */
        unsigned int *d_visited;

        /*
            queues used for popping element and pushing
        */
        int *d_first_queue;
        int *d_second_queue;

        /*
            Array containing destination node wich will increase the flow
        */
        int *d_destination_node;

        /*
            Array containing start node wich will increase the flow
        */
        int *d_start_node;

        int nodes_num;

        Graph * graph;

        void InitializeGraphOnDevice(Graph *g);
        void InitializeParentNode();
        void InitializeVisited();
        void InitializeQueues();
        void InitializeStartDestination();
        bool BFS(Node * start, Node * end);
        
    public:
        EdmonsKarpCuda(Graph * g);
        int Solve();
        ~EdmonsKarpCuda();
};

#endif