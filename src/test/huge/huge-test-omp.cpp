#include "../../hpc.h"
#include "../../Graph.hpp"
#include "../../ford-fulkerson/Omp.hpp"
#include <cstdio>

int main() {

    printf("Generation ... ");
    GraphGenerator gf = GraphGenerator();
    Graph h = gf.NodeNumber(60)
                ->EdgeNumber(3000)
                ->Generate();
    printf("OK\n");
    
    FordFulkersonOmp solver = FordFulkersonOmp(&h);
    int max_flow;
    double start = hpc_gettime();
    max_flow = solver.Solve();
    double end = hpc_gettime() - start;
    printf("Max flow: %d\n", max_flow);
    printf("Took %f s\n", end);
}