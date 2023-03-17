
SERVER=./server/src/
CLIENT=./client/src/

all: ${SERVER}main.cpp ${SERVER}server.cpp ${SERVER}server.hpp ${CLIENT}main.cpp ${CLIENT}client.cpp ${CLIENT}client.hpp
	g++ ${SERVER}main.cpp ${SERVER}server.cpp -o server1 -lpthread
	g++ ${CLIENT}main.cpp ${CLIENT}client.cpp -o client1 -lpthread

clean:
	rm -f client1
	rm -f server1
