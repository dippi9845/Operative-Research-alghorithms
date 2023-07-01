#include "../../hpc.h"
#include "../../Graph.hpp"
#include "../../ford-fulkerson/Omp.hpp"
#include <cstdio>

int main() {

    //printf("Generation ... \n");
    GraphGenerator gf = GraphGenerator();
    Graph h = gf.NodeNumber(50)->Generate();
    printf("OK\n");
    
    FordFulkersonOmp solver = FordFulkersonOmp(&h);
    int max_flow;
    double start = hpc_gettime();
    max_flow = solver.Solve();
    double end = hpc_gettime() - start;
    h.PrintAsMatrix();
    printf("Max flow: %d\n", max_flow);
    //printf("Took %f s\n", end);
}