#!/bin/bash
OBJECT_DIR=object
EXE_DIR=exe
SRC=src

for test_file in src/test/test-edmons-karp-cuda-*; do
    file_name=$(basename "$test_file")
    file_name="${file_name%.*}"
    echo $file_name
    nvcc ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${SRC}/edmons-karp/Cuda.cu ${test_file} -o ${EXE_DIR}/${file_name}
done

for exe_test_file in exe/test-edmons-karp-cuda-*; do
    #echo $exe_test_file
    ./${exe_test_file}
done