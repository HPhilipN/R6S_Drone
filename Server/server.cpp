#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Binding socket to the port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listening for connections
    listen(server_fd, 3);

    // Accepting a connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // Receiving data
    char buffer[1024] = {0};
    read(new_socket, buffer, 1024);
    std::cout << "Data received: " << buffer << std::endl;

    // Closing socket
    close(server_fd);

    return 0;
}