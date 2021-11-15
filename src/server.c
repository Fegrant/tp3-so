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

    /*
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

    printf("\n ----- PREGUNTA PARA INVESTIGAR -----");
    printf("\n");
    printf("¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?\n");

    if(fstat(client.fd, &file_stat) == -1){
        fprintf(stderr, "Error retrieving file descriptor info\n");
    }

    read(client.fd, (void*)answer, MAX_READ_BYTES);
    if(strncmp(answer, "entendido\n", MAX_READ_BYTES) != 0){
        printf("RESPUESTA EQUIVOCADA\n");
        printf("Respuesta ingresada: %s\n", answer);
    }
    else
        printf("RESPUESTA CORRECTA\n");
    */

    close(server.fd);
    close(client.fd);
    return 0;
}