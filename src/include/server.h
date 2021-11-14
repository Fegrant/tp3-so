#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <asm-generic/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include "challenges.h"

typedef struct SockStruct {
    int fd;
    struct sockaddr_in socket;
} SockStruct;

#define MAX_CONNECTIONS 5
#define SERVER_PORT 8080
#define SERVER_ADDR "0.0.0.0"