SRC=./src/

run: server
	./server 1234

server: ${SRC}main.cpp ${SRC}server.cpp ${SRC}server.hpp
	g++ ${SRC}main.cpp ${SRC}server.cpp -o server -lpthread

clean:
	rm -f server
