#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

using std::vector;


class Server {
    public:
        // Launching the functions of creating and accepting clients
        void run(int port);

    private:
        // Functions for creating a server and accepting clients
        int Socket();
        void Bind();
        void Listen();
        int Accept();

        // Client management features
        void NewConnection(int client, int& connected_count); // Creates 2 parallel streams with the client to listen and send
		void Notify(int client);
        bool Recv(int client); // Listening thread for client requests
        std::string execute(std::string command);
        std::string Concate(vector<std::string> list); // Concatenates the elements of a list into a single string

    private:
        // Variables for creating and managing a connection between the server and clients
        sockaddr_in server_address;
        int server_port;
        int server_socket;
};
