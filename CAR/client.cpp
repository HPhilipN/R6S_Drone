#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char data_to_send[1024] = "Hello from client";

    // Creating socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 addresses from text to binary
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Connecting to server
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Sending data
    send(sock, data_to_send, strlen(data_to_send), 0);

    // Closing socket
    close(sock);

    return 0;
}