#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <ip address> <port range>" << std::endl;
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cout << "Failed to create socket" << std::endl;
        return 1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    char *end;
    long port_range = strtol(argv[2], &end, 10);
    if (*end != '\0' || port_range < 1 || port_range > 65535) {
        std::cout << "Invalid port range" << std::endl;
        return 1;
    }

    for (int port = 1; port <= port_range; ++port) {
        server_address.sin_port = htons(port);
        int result = connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
        if (result == 0) {
            std::cout << "Port " << port << " open" << std::endl;
        }
    }

    close(sock);

    return 0;
}
