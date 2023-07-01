#include "../../hpc.h"
#include "../../Graph.hpp"
#include "../../ford-fulkerson/Omp.hpp"
#include <cstdio>

int main() {

    printf("Generation ... ");
    GraphGenerator gf = GraphGenerator();
    Graph h = gf.NodeNumber(960)->Generate();
    printf("OK\n");
    
    FordFulkersonOmp solver = FordFulkersonOmp(&h);

    double start = hpc_gettime();
    solver.Solve();
    double end = hpc_gettime() - start;

    printf("Took %f s\n", end);
}