#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

#define MAX_CONNECTIONS 5
#define SERVER_PORT 8080
#define SERVER_ADDR "0.0.0.0"
#define MAX_READ_BYTES 4096