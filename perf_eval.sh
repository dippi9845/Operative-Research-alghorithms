STEP=100
MAX=1000

for (( i=$STEP ; $i <= $MAX; i=$i+$STEP )); do 
    exe/huge-test-serial $i >> serial_perf.txt
done

for (( i=$STEP ; $i <= $MAX; i=$i+$STEP )); do 
    exe/huge-test-omp $i >> omp_perf.txt
done

for (( i=$STEP ; $i <= $MAX; i=$i+$STEP )); do 
    exe/huge-test-cuda $i >> cuda_perf.txt
done