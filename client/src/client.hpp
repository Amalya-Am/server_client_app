#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <vector>
#include <functional>
using std::vector;

std::string Concate(vector<std::string> list, int start);
vector<std::string> split(std::string msg);

using std::vector;

class Client
{
    public:
        Client(std::string ip, int port);
        void run();

    private:
        void setAddress(std::string ip, int port);
        int Socket();
        bool Connect();

        void Recv();

    private: 
        sockaddr_in m_server_address;
        std::string m_ip;
        int m_port;
        int m_server;
};

#endif
