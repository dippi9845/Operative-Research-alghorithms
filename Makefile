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


${OBJECT_DIR}/EdmonsSerial.o : ${OBJECT_DIR}/Graph.o ${SRC}/edmons-karp/Serial.cpp ${SRC}/edmons-karp/Serial.hpp
	${C_O_FLAGS} -g ${SRC}/edmons-karp/Serial.cpp -o ${OBJECT_DIR}/EdmonsSerial.o


${OBJECT_DIR}/EdmonsOmp.o : ${OBJECT_DIR}/EdmonsSerial.o ${SRC}/edmons-karp/Omp.cpp ${SRC}/edmons-karp/Omp.hpp
	${C_O_FLAGS} ${OMP_F} -g ${SRC}/edmons-karp/Omp.cpp -o ${OBJECT_DIR}/EdmonsOmp.o

test-edmons-serial: ${OBJECT_DIR}/EdmonsSerial.o ${SRC}/test/test-edmons-karp-Serial.cpp
	${C_FLAGS} -g ${SRC}/test/test-edmons-karp-Serial.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/EdmonsSerial.o -o ${EXE_DIR}/test-emd-serial


test-graph: ${OBJECT_DIR}/Graph.o ${SRC}/test/test-graph.cpp
	${C_FLAGS} -g ${SRC}/test/test-graph.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o -o ${EXE_DIR}/test-graph


test-edmons-omp: ${OBJECT_DIR}/EdmonsOmp.o ${SRC}/test/test-edmons-karp-Omp.cpp
	${C_FLAGS} ${OMP_F} -g ${SRC}/test/test-edmons-karp-Omp.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/EdmonsSerial.o ${OBJECT_DIR}/EdmonsOmp.o -o ${EXE_DIR}/test-edm-omp


huge-omp-test: ${OBJECT_DIR}/EdmonsOmp.o ${SRC}/test/huge/huge-test-omp.cpp
	${C_FLAGS} ${OMP_F} ${SRC}/test/huge/huge-test-omp.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/EdmonsSerial.o ${OBJECT_DIR}/EdmonsOmp.o -o ${EXE_DIR}/huge-test-omp


huge-serial-test: ${OBJECT_DIR}/EdmonsSerial.o ${SRC}/test/huge/huge-test-serial.cpp
	${C_FLAGS} ${SRC}/test/huge/huge-test-serial.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/EdmonsSerial.o -o ${EXE_DIR}/huge-test-serial


huge-cuda-test: ${OBJECT_DIR}/Graph.o ${SRC}/edmons-karp/Cuda.cu 
	nvcc ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${SRC}/edmons-karp/Cuda.cu ${SRC}/test/huge/huge-test-cuda.cu -o ${EXE_DIR}/huge-test-cuda

.PHONY : all test-edmons-serial test-graph clean


clean :
	-rm -r object/* exe/*
