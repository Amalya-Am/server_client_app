SRC=./src/

run: client
	./client 127.0.0.1 1234

client: ${SRC}main.cpp ${SRC}client.cpp ${SRC}client.hpp
	g++ ${SRC}main.cpp ${SRC}client.cpp -o client -lpthread

clean:
	rm -f client
