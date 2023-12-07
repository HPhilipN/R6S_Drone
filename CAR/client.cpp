#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    int buffer[1024] = {123}; // Example data to send

    // Creating the socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 addresses from text to binary form
    inet_pton(AF_INET, "172.28.231.23", &serv_addr.sin_addr);

    // Connect to the server
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Send data
    send(sock, buffer, sizeof(buffer), 0);

    // Close the socket
    close(sock);

    return 0;
}