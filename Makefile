OBJECT_DIR=object
SRC=src
EXE_DIR=exe

FLAGS=-Wall -Wpedantic

${OBJECT_DIR}/DirectedEdge.o : ${SRC}/DirectedEdge.hpp ${SRC}/DirectedEdge.cpp
	g++ ${FLAGS} -c ${SRC}/DirectedEdge.cpp -o ${OBJECT_DIR}/DirectedEdge.o


${OBJECT_DIR}/Node.o : ${SRC}/Node.hpp ${SRC}/Node.hpp ${OBJECT_DIR}/DirectedEdge.o
	g++ ${FLAGS} -c ${SRC}/Node.cpp -o ${OBJECT_DIR}/Node.o


${OBJECT_DIR}/Graph.o : ${SRC}/Graph.hpp ${SRC}/Graph.cpp ${OBJECT_DIR}/Node.o
	g++ ${FLAGS} -c ${SRC}/Graph.cpp -o ${OBJECT_DIR}/Graph.o


${OBJECT_DIR}/FordSerial.o : ${OBJECT_DIR}/Graph.o ${SRC}/ford-fulkerson/Serial.cpp ${SRC}/ford-fulkerson/Serial.hpp
	g++ ${FLAGS} -c ${SRC}/ford-fulkerson/Serial.cpp -o ${OBJECT_DIR}/FordSerial.o


test-ford-serial: ${OBJECT_DIR}/FordSerial.o ${SRC}/test/test-Ford-Fulkerson-Serial.cpp
	g++ ${FLAGS} ${SRC}/test/test-Ford-Fulkerson-Serial.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/FordSerial.o -o ${EXE_DIR}/test-for-serial


.PHONY : all test-ford-serial clean


clean :
	-rm -r object/*