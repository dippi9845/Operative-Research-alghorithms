OBJECT_DIR=object
SRC=src
EXE_DIR=exe

FLAGS=-Wall -Wpedantic
C_FLAGS=g++ ${FLAGS}
C_O_FLAGS=${C_FLAGS} -c

${OBJECT_DIR}/DirectedEdge.o : ${SRC}/DirectedEdge.hpp ${SRC}/DirectedEdge.cpp
	${C_O_FLAGS} ${SRC}/DirectedEdge.cpp -o ${OBJECT_DIR}/DirectedEdge.o


${OBJECT_DIR}/Node.o : ${SRC}/Node.hpp ${SRC}/Node.hpp ${OBJECT_DIR}/DirectedEdge.o
	${C_O_FLAGS} ${SRC}/Node.cpp -o ${OBJECT_DIR}/Node.o


${OBJECT_DIR}/Graph.o : ${SRC}/Graph.hpp ${SRC}/Graph.cpp ${OBJECT_DIR}/Node.o
	${C_O_FLAGS} ${SRC}/Graph.cpp -o ${OBJECT_DIR}/Graph.o


${OBJECT_DIR}/FordSerial.o : ${OBJECT_DIR}/Graph.o ${SRC}/ford-fulkerson/Serial.cpp ${SRC}/ford-fulkerson/Serial.hpp
	${C_O_FLAGS} ${SRC}/ford-fulkerson/Serial.cpp -o ${OBJECT_DIR}/FordSerial.o


test-ford-serial: ${OBJECT_DIR}/FordSerial.o ${SRC}/test/test-Ford-Fulkerson-Serial.cpp
	${C_FLAGS} -g ${SRC}/test/test-Ford-Fulkerson-Serial.cpp ${OBJECT_DIR}/DirectedEdge.o ${OBJECT_DIR}/Node.o ${OBJECT_DIR}/Graph.o ${OBJECT_DIR}/FordSerial.o -o ${EXE_DIR}/test-for-serial


.PHONY : all test-ford-serial clean


clean :
	-rm -r object/*