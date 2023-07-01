#include "../../hpc.h"
#include "../../Graph.hpp"
#include "../../ford-fulkerson/Cuda.cuh"
#include <cstdio>

int main() {

    printf("Generation ... ");
    GraphGenerator gf = GraphGenerator();
    Graph h = gf.NodeNumber(10000)->Generate();
    printf("OK\n");
    
    FordFulkersonCuda solver = FordFulkersonCuda(&h);

    double start = hpc_gettime();
    solver.Solve();
    double end = hpc_gettime() - start;

    printf("Took %f s\n", end);
}