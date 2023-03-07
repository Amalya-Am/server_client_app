#include "client.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3) {
          std::cout << "When calling, pass ip and port\n";
          exit(1);
    }
    Client client(argv[1], std::stoi(argv[2]));
    client.run();
}
