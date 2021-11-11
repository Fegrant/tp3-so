#include "include/server.h"

int main(){
    int servsock_fd, clisock_fd;
    int sock_optval[] = {1};
    socklen_t sock_optlen = 4;
    socklen_t clisock_len = sizeof(struct sockaddr);

    char answer[MAX_READ_BYTES];

    struct stat file_stat;

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

    printf("------------- DESAFIO -------------");
    printf("\n");

    printf("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n"
    "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n"
    "Además tendrán que investigar otras preguntas para responder durante la defensa.\n"
    "El desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos "
    "y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\n"
    "Además, deberán implementar otro programa para comunicarse conmigo\n\n"
    "Deberán estar atentos a los easter eggs.\n\n"
    "Para verificar que sus respuestas tienen el formato correcto respondan a este desafio con la palabra 'entendido\\n'\n");

    if(fstat(clisock_fd, &file_stat) == -1){
        printf("Error retrieving file descriptor info\n");
    }

    read(clisock_fd, (void*)&answer, MAX_READ_BYTES);
    if(strncmp(answer, "entendido\n", MAX_READ_BYTES) != 0)
        printf("RESPUESTA EQUIVOCADA\n");
    else
        printf("RESPUESTA CORRECTA\n");

    close(servsock_fd);
    close(clisock_fd);
    return 0;
}