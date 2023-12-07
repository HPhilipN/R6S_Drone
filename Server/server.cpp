#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int buffer[1024] = {0};

    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Define the socket type
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket to the network address and port
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Put the server in listen mode
    listen(server_fd, 3);

    // Accept an incoming connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // Read data from the client
    read(new_socket, buffer, 1024);
    std::cout << "Data received: " << buffer << std::endl;

    // Close the socket
    close(new_socket);
    close(server_fd);

    return 0;
}