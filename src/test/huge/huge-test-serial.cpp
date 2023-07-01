#include "../../hpc.h"
#include "../../Graph.hpp"
#include "../../ford-fulkerson/Serial.hpp"
#include <cstdio>

int main() {

    //printf("Generation ... ");
    GraphGenerator gf = GraphGenerator();
    Graph h = gf.NodeNumber(960)->Generate();
    printf("OK\n");
    
    FordFulkersonSerial solver = FordFulkersonSerial(&h);
    int max_flow;
    double start = hpc_gettime();
    max_flow = solver.Solve();
    double end = hpc_gettime() - start;
    h.PrintAsMatrix();
    printf("Max flow: %d\n", max_flow);
    //printf("Took %f s\n", end);
}