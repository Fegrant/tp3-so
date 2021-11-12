#include "include/challenges.h"

#define CHILD_STACK_SIZE 36864
#define PIPE_READ_FD    5
#define PIPE_WRITE_FD   6

typedef struct ChallengeStruct {
    void* challenge;
    char* answer;
    char* hint;
    char* homeworkQuestion;
} ChallengeStruct;

static int challenge1();
static int challenge2();
static int challenge3();
static int challenge4();
static int challenge5();
static int challenge6();
static int challenge7();
static int challenge8();
static int challenge9();
static int challenge10();
static int challenge11();
static int challenge12();

char* welcomeMessage = "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n"
    "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n"
    "Además tendrán que investigar otras preguntas para responder durante la defensa.\n"
    "El desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos "
    "y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\n"
    "Además, deberán implementar otro programa para comunicarse conmigo\n\n"
    "Deberán estar atentos a los easter eggs.\n\n"
    "Para verificar que sus respuestas tienen el formato correcto respondan a este desafio con la palabra 'entendido\\n'\n";

char* userAnswer[MAX_READ_BYTES] = {0};

ChallengeStruct challenges[CHALLENGE_AMOUNT] = {
    { challenge1, "entendido\n", welcomeMessage, "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?"},
    { challenge2, "itba\n", "", "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n"},
    { challenge3, "M4GFKZ289aku\n", "", "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?\n"},
    { challenge4, "fk3wfLCm3QvS\n", "", "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿Se puede utilizar read(2) y write(2) para operar?\n"},
    { challenge5, "too_easy\n", "", "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n"},
    { challenge6, ".RUN_ME\n", "", "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?\n"},
    { challenge7, "K5n2UFfpFMUN\n", "", "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n"},
    { challenge8, "BUmyYq5XxXGt\n", "", "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n"},
    { challenge9, "u^v\n", "", "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n"},
    { challenge10, "chin_chu_lan_cha\n", "", "¿Cuáles son las características del protocolo SCTP?\n"},
    { challenge11, "gdb_rules\n", "", "¿Qué es un RFC?\n"},
    { challenge12, "normal\n", "", "¿Fue divertido?"}
};

void doChallenges(int readFd){
    void* childStackHead = malloc(CHILD_STACK_SIZE);
    void* childStack = childStackHead + CHILD_STACK_SIZE - 1;
    int pipefd[] = {PIPE_READ_FD, PIPE_WRITE_FD};
    int current = 0;

    while(current < CHALLENGE_AMOUNT){
        // challenge execution
        system("clear");
        printf("------------- DESAFIO -------------\n");
        printf(challenges[current].hint);
        printf("----- PREGUNTA PARA INVESTIGAR -----\n");
        printf(challenges[current].homeworkQuestion);
        read(readFd, userAnswer, MAX_READ_BYTES);
        if(strcmp(userAnswer, challenges[current].answer) == 0)
            current++;
        else
            printf("Respuesta incorrecta: %s\n", userAnswer);
    }
    free(childStackHead);
}

static int challenge1(){
    // Do nothing, user just has to input answer
}