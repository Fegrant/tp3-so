// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/server.h"

int main(){
    SockStruct server;
    SockStruct client;
    int sock_optval[] = {1};
    socklen_t sock_optlen = 4;
    socklen_t clisock_len = sizeof(struct sockaddr);

    server.socket.sin_family = AF_INET;
    server.socket.sin_port = htons(SERVER_PORT);
    server.socket.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if((server.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1){
        fprintf(stderr, "Error opening socket\n");
        return -1;
    }

    if(setsockopt(server.fd, SOL_SOCKET, SO_REUSEPORT, (const void*)sock_optval, sock_optlen) == -1){
        fprintf(stderr, "Error setting socket options");
        return -1;
    }

    if(bind(server.fd, (struct sockaddr*)&server.socket, sizeof(struct sockaddr)) == -1){
        fprintf(stderr, "Error binding socket\n");
        return -1;
    }

    if(listen(server.fd, MAX_CONNECTIONS) == -1){
        fprintf(stderr, "Error marking socket as passive (listen)\n");
        return -1;
    }

    if((client.fd = accept(server.fd, (struct sockaddr*)&client.socket, &clisock_len)) == -1){
        fprintf(stderr, "Error accepting incoming connection\n");
        return -1;
    }

    doChallenges(client.fd);

    close(server.fd);
    close(client.fd);
    return 0;
}