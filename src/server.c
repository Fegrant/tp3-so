#include "include/server.h"

int main(){
    int servsock_fd, clisock_fd;
    int sock_optval[] = {1};
    socklen_t sock_optlen = 4;
    socklen_t clisock_len = sizeof(struct sockaddr);

    struct sockaddr_in server;
    struct sockaddr_in client;

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if((servsock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1){
        printf("Error opening socket\n");
        return -1;
    }

    if(setsockopt(servsock_fd, SOL_SOCKET, SO_REUSEPORT, (const void*)sock_optval, sock_optlen) == -1){
        printf("Error setting socket options");
        return -1;
    }

    if(bind(servsock_fd, (struct sockaddr*)&server, sizeof(struct sockaddr)) == -1){
        printf("Error binding socket\n");
        return -1;
    }

    if(listen(servsock_fd, MAX_CONNECTIONS) == -1){
        printf("Error marking socket as passive (listen)\n");
        return -1;
    }

    if((clisock_fd = accept(servsock_fd, (struct sockaddr*)&client, &clisock_len)) == -1){
        printf("Error accepting incoming connection\n");
        return -1;
    }

    printf("Hola y adios\n");
    close(servsock_fd);
    close(clisock_fd);
    return 0;
}