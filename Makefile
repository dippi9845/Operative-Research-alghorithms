OBJECT_DIR=object
SRC=src
EXE_DIR=exe

FLAGS=-Wall -Wpedantic -O0
C_FLAGS=g++ ${FLAGS}
C_O_FLAGS=${C_FLAGS} -c
OMP_F=-fopenmp


${OBJECT_DIR}/DirectedEdge.o : ${SRC}/DirectedEdge.hpp ${SRC}/DirectedEdge.cpp
	${C_O_FLAGS} -g ${SRC}/DirectedEdge.cpp -o ${OBJECT_DIR}/DirectedEdge.o


${OBJECT_DIR}/Node.o : ${SRC}/Node.hpp ${SRC}/Node.hpp ${OBJECT_DIR}/DirectedEdge.o
	${C_O_FLAGS} -g ${SRC}/Node.cpp -o ${OBJECT_DIR}/Node.o


${OBJECT_DIR}/Graph.o : ${SRC}/Graph.hpp ${SRC}/Graph.cpp ${OBJECT_DIR}/Node.o
	${C_O_FLAGS} -g ${SRC}/Graph.cpp -o ${OBJECT_DIR}/Graph.o


${OBJECT_DIR}/FordSerial.o : ${OBJECT_DIR}/Graph.o ${SRC}/ford-fulkerson/Serial.cpp ${SRC}/ford-fulkerson/Serial.hpp
	${C_O_FLAGS} -g ${SRC}/ford-fulkerson/Serial.cpp -o ${OBJECT_DIR}/FordSerial.o


${OBJECT_DIR}/FordOmp.o : ${OBJECT_DIR}/FordSerial.o ${SRC}/ford-fulkerson/Omp.cpp ${SRC}/ford-fulkerson/Omp.hpp
	${C_O_FLAGS} ${OMP_F} -g ${SRC}/ford-fulkerson/Omp.cpp -o ${OBJECT_DIR}/FordOmp.o

test-ford-serial: ${OBJECT_DIR}/FordSerial.o ${SRC}/test/test-Ford-Fulkerson-Serial.cpp
	${C_FLAGS} -g ${SRC}/test/test-Ford-Fulkerson-Serial.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/FordSerial.o -o ${EXE_DIR}/test-for-serial


test-graph: ${OBJECT_DIR}/Graph.o ${SRC}/test/test-graph.cpp
	${C_FLAGS} -g ${SRC}/test/test-graph.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o -o ${EXE_DIR}/test-graph


test-ford-omp: ${OBJECT_DIR}/FordOmp.o ${SRC}/test/test-Ford-Fulkerson-Omp.cpp
	${C_FLAGS} ${OMP_F} -g ${SRC}/test/test-Ford-Fulkerson-Omp.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/FordSerial.o ${OBJECT_DIR}/FordOmp.o -o ${EXE_DIR}/test-for-omp


huge-omp-test: ${OBJECT_DIR}/FordOmp.o ${SRC}/test/huge/huge-test-omp.cpp
	${C_FLAGS} ${OMP_F} ${SRC}/test/huge/huge-test-omp.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/FordSerial.o ${OBJECT_DIR}/FordOmp.o -o ${EXE_DIR}/huge-test-omp


huge-serial-test: ${OBJECT_DIR}/FordSerial.o ${SRC}/test/huge/huge-test-serial.cpp
	${C_FLAGS} ${SRC}/test/huge/huge-test-serial.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/FordSerial.o -o ${EXE_DIR}/huge-test-serial


huge-cuda-test: ${OBJECT_DIR}/Graph.o ${SRC}/ford-fulkerson/Cuda.cu 
	nvcc ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${SRC}/ford-fulkerson/Cuda.cu ${SRC}/test/huge/huge-test-cuda.cu -o ${EXE_DIR}/huge-test-cuda

.PHONY : all test-ford-serial test-graph clean


clean :
	-rm -r object/* exe/*
