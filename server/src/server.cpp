#include "server.hpp"

vector<std::string> split(std::string msg)
{
    vector<std::string> list;
    std::string buffer = "";
    for (int i = 0; i < msg.size(); ++i) {
        if (msg[i] == ' ') {
            list.push_back(buffer);
            buffer = "";
            continue;
        }
        buffer += msg[i];
    }
    if (buffer != "") list.push_back(buffer);
    return list;
}

int Server::Socket()
{
    int res = socket(AF_INET, SOCK_STREAM, 0);
    if (res == -1) {
        perror("Critical Error: Socket Creating Failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Server::Bind()
{
    int res = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    if (res == -1) {
        perror("Critical Error: Bind Failed");
        exit(EXIT_FAILURE);
    }
}

void Server::Listen()
{
    int res = listen(server_socket, 5);
    if (listen(server_socket, 5) == -1) {
        perror("Critical Error: Listen Failed");
        exit(EXIT_FAILURE);
    }
}

int Server::Accept()
{
    socklen_t adrlen = sizeof(server_address);
    int res = accept(server_socket, reinterpret_cast<sockaddr*>(&server_address), &adrlen);
    if (res == -1 ) {
        perror("Error: Accept Failed");
        exit(EXIT_FAILURE);
    }
    return res;
	std::cout << res;
}

void Server::run(int port)
{
    server_address.sin_port = htons(port);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_socket = Socket();
	Bind();
	Listen();
	int connected_count = 0;
	int max_connect = 5;
    while (true) {
		if (connected_count < max_connect) {
			std::cout << "Wait Connect\n";
			int client =  Accept();
			connected_count++;
        	std::thread th1([&](){NewConnection(client, connected_count);});
        	th1.detach();
		}
		if (connected_count == max_connect) {
			int client =  Accept();
			Notify(client);
		}
	}
}

void Server::NewConnection(int client, int& connected_count)
{
    std::string notify_msg = "You are connected\n";
    send(client, notify_msg.c_str(), notify_msg.size(), 0);
    Recv(client);
	connected_count--;
}

void Server::Notify(int client) {
	std::string msg = "disconnect";
	send(client, msg.c_str(), msg.size(), 0);
}

bool Server::Recv(int client)
{
    int buf_size = 1024;
    char buffer[buf_size];
    while(true) {
        memset(buffer, 0, buf_size);
        recv(client, buffer, buf_size, 0);
        std::string buf_str = buffer;
        std::cout << buf_str << "\n\n";
        if (buf_str.size() == 0) {
            std::cout << "Client Crashed\n";
            return true;
        }
        if (buf_str == "disconnect") {
            std::cout << "Client disconnected\n";
            break;
        }
        std::string response = execute(buf_str);
        send(client, response.c_str(), response.size(), 0);
    }
}

std::string Server::execute(std::string command)
{
    int start_index = command.find_first_of('"');
    if (start_index < 0 && start_index > command.size()) {return "Not supported";}
    command.erase(0, start_index + 1);
    int end_index = command.find_last_of('"');
    if (end_index < 0 && end_index > command.size()) {return "Not supported";}
    command.erase(end_index);
    std::system(command.c_str());
    return "Executed";
}
