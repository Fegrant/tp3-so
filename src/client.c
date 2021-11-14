#include "include/client.h"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Error 2 arguments expected\n");
        return -1;
    }
    
    if(strcmp(argv[1],SERVER_ADDR) != 0 || atoi(argv[2]) != SERVER_PORT) {
        fprintf(stderr, "Error wrong arguments\n");
        return -1;
    }
    SockStruct server;
    int sock_optval[] = {0};
    socklen_t sock_optlen = 4;

    server.socket.sin_family = AF_INET;
    server.socket.sin_port = htons(SERVER_PORT);
    server.socket.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    
    struct pollfd pollfd[4] = {{0,POLLIN,0}, {3,0,0}, {3,POLLIN,0}, {1,0,0}};

    if((server.fd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK , IPPROTO_TCP)) == -1){
        fprintf(stderr, "Error opening socket\n");
        return -1;
    }
    fd_set writefd;
    FD_ZERO(&writefd);
    FD_SET(server.fd,&writefd);
    
    connect(server.fd,(struct sockaddr*)&server.socket, sizeof(struct sockaddr));
    
    if(select(4,NULL,&writefd,NULL,NULL) == -1 ) {
        fprintf(stderr, "Error select\n");
        return -1;
    } 
    if(getsockopt(server.fd,SOL_SOCKET,SO_ERROR,sock_optval,&sock_optlen) == -1) {
        fprintf(stderr, "Error getting socket options\n");
        return -1;
    }
    char buffer[SIZE_BUFFER];
    int buffer_size = 0;
    while(1) {
    poll(pollfd, 4, -1);
        if(pollfd[0].revents == POLLIN) {
            buffer_size = read(0,buffer,SIZE_BUFFER);
            pollfd[1].events = POLLOUT;
        }
        if(pollfd[1].revents == POLLOUT) {
            write(pollfd[1].fd,buffer,buffer_size);
            pollfd[1].events = 0;
        }
        if(pollfd[2].revents == POLLIN) {
            read(pollfd[2].fd,buffer,SIZE_BUFFER);
            shutdown(server.fd,SHUT_RD);
            pollfd[2].fd = -1;
            pollfd[3].fd = -1;
            break;
        }
    }
    return 0;
} 