#include "client.hpp"

std::string Concate(vector<std::string> list, int start)
{
    std::string message = "";
    for (int i = start; i < list.size(); ++i) {
        message += list[i] + " ";
    }
    return message;
}

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

Client::Client(std::string ip, int port)
{
    setAddress(ip, port);
}

void Client::setAddress(std::string ip, int port)
{
    m_ip = ip;
    m_port = port;
    m_server_address.sin_port = htons(m_port);
    m_server_address.sin_family = AF_INET;
    inet_pton(AF_INET, m_ip.c_str(), &m_server_address.sin_addr);
}

void Client::run()
{
    m_server = Socket();
    int is_connected = Connect();
    if (is_connected) {
        Recv();
    }
}

int Client::Socket()
{
    int res = socket(AF_INET, SOCK_STREAM, 0);
    if (res == -1) {
        perror("Critical Error: Socket Creating Failed");
        exit(EXIT_FAILURE);
    }   
    return res;
}

bool Client::Connect()
{
    int ret = connect(m_server, reinterpret_cast<const struct sockaddr*>(&m_server_address),sizeof(m_server_address));
    if(ret != 0) {
        perror("Don't connected");
        exit(EXIT_FAILURE);
    }
    std::cout << "CLIENT: Connection to server " << inet_ntoa(m_server_address.sin_addr) << " with port number: " << m_port << '\n';
    return true;
}


void Client::Recv()
{
    int buff_size = 1024;
    char buffer[buff_size];
	std::cout << "RECV func started\n";
    while(true) {
        memset(buffer, 0, buff_size);
        recv(m_server, buffer, buff_size, 0);
        std::cout << buffer << "\n\n";
		if (std::string(buffer) == "disconnect") {
			std::cout << "There is no enough space for new client.\n";
			break;
		}
        if (std::string(buffer) == "{EXIT}") {
            exit(0);
        }
        memset(buffer, 0, buff_size);
        std::cin.getline(buffer, buff_size);
        send(m_server, buffer, buff_size, 0);
        if (std::string(buffer) == "disconnect") break;
    }
}
