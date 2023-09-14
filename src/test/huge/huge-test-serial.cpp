#include "../../hpc.h"
#include "../../Graph.hpp"
#include "../../edmons-karp/Serial.hpp"
#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {
    int n = 950;

    if (argc > 1) {
        n = atoi(argv[1]);
    }

    //printf("Generation ... ");
    GraphGenerator gf = GraphGenerator();
    Graph h = gf.NodeNumber(n)->Generate();
    //printf("OK\n");
    
    EdmonsKarpSerial solver = EdmonsKarpSerial(&h);
    double start = hpc_gettime();
    solver.Solve();
    double end = hpc_gettime() - start;
    
    printf("%f\n", end);
}