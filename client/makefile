
SERVER=./server/src/
CLIENT=./client/src/
all:  server client

server: ${SERVER}main.cpp ${SERVER}client.cpp ${SERVER}client.hpp
	g++ ${SERVER}main.cpp ${SERVER}server.cpp -o server -lpthread
client: ${CLIENT}main.cpp ${CLIENT}client.cpp ${CLIENT}client.hpp
	g++ ${CLIENT}main.cpp ${CLIENT}client.cpp -o client -lpthread

clean:
	rm -f client
	rm -f server
