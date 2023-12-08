#include "network.hpp"
#define PORT 8080
#define SA struct sockaddr

int initServer(){
    int servSock, servConnection;
    socklen_t len;
    struct sockaddr_in servAddr, cliAddr;

    servSock = socket(AF_INET, SOCK_STREAM, 0);
    if(servSock == -1){
        printf("ERROR: Server socket creation failed\n");
        exit(1);
    }
    bzero(&servAddr, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(PORT);

    if((bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr))) != 0){
        printf("ERROR: Server socket bind failed\n");
        exit(1);
    }

    if((listen(servSock, 5)) != 0){
        printf("ERROR: Server listen failed\n");
        exit(1);
    }
    len = sizeof(cliAddr);

    servConnection = accept(servSock, (struct sockaddr*)&cliAddr, &len);
    if(servConnection < 0){
        printf("ERROR: Server accept failed\n");
        exit(1);
    }

    return servConnection;
}