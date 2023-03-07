#include "server.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "When calling, pass only the port\n";
        exit(1);
    }
    Server server;
    server.run(std::stoi(argv[1]));
}
