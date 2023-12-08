#include "clientNet.hpp"
#define PORT 8080
#define SA struct sockaddr

int initClient(){

    int cliSock, cliConnection;
    struct sockaddr_in servAddr, cliAddr;

    cliSock = socket(AF_INET, SOCK_STREAM, 0);
    if(cliSock == -1){
        printf("ERROR: Client socket creation failed\n");
        exit(1);
    }
    printf("Client socket creation successful\n");
    bzero(&servAddr, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("10.42.0.1");
    servAddr.sin_port = htons(PORT);

    if(connect(cliSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0){
        printf("ERROR: Connection with server failed\n");
        exit(1);
    }
    printf("Client connection with server successful\n");

    return cliSock;
}