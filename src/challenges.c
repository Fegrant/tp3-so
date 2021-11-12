#include "include/challenges.h"

#define CHILD_STACK_SIZE 36864
#define PIPE_READ_FD    5
#define PIPE_WRITE_FD   6

#define EBADF_CHALLENGE_FD 13

typedef int (*challengeFunction)();

typedef struct ChallengeStruct {
    challengeFunction challenge;
    char* answer;
    char* hint;
    char* homeworkQuestion;
} ChallengeStruct;

char userAnswer[MAX_READ_BYTES] = {0};
int pipefd[] = {PIPE_READ_FD, PIPE_WRITE_FD};
int current = 0;

int naiveChallenge();
int badFileDescriptorChallenge();

ChallengeStruct challenges[CHALLENGE_AMOUNT] = {
    { &naiveChallenge, "entendido\n", "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n"
    "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n"
    "Además tendrán que investigar otras preguntas para responder durante la defensa.\n"
    "El desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos "
    "y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\n"
    "Además, deberán implementar otro programa para comunicarse conmigo\n\n"
    "Deberán estar atentos a los easter eggs.\n\n"
    "Para verificar que sus respuestas tienen el formato correcto respondan a este desafio con la palabra 'entendido\\n'\n", "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?\n"},
    { &naiveChallenge, "itba\n", "The Wire S1E5\n5295 888 6288\n\n", "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n"},
    { &naiveChallenge, "M4GFKZ289aku\n", "https://ibb.co/tc0Hb6w\n\n", "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?\n"},
    { &badFileDescriptorChallenge, "fk3wfLCm3QvS\n", "................................La respuesta es fk3wfLCm3QvS\n", "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿Se puede utilizar read(2) y write(2) para operar?\n"},
    { &naiveChallenge, "too_easy\n", "respuesta = strings:TBD\n\n", "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n"},
    { &naiveChallenge, ".RUN_ME\n", ".data .bss .comment ? .shstrtab .symtab .strtab", "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?\n"},
    { &naiveChallenge, "K5n2UFfpFMUN\n", "", "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n"},
    { &naiveChallenge, "BUmyYq5XxXGt\n", "", "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n"},
    { &naiveChallenge, "u^v\n", "", "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n"},
    { &naiveChallenge, "chin_chu_lan_cha\n", "", "¿Cuáles son las características del protocolo SCTP?\n"},
    { &naiveChallenge, "gdb_rules\n", "", "¿Qué es un RFC?\n"},
    { &naiveChallenge, "normal\n", "", "¿Fue divertido?"}
};

void doChallenges(int readFd){
    void* childStackHead = malloc(CHILD_STACK_SIZE);
    void* childStack = childStackHead + CHILD_STACK_SIZE - 1;
    int childFd;
    int childStatus;
    int nullTerminateIdx;
    char ofuscatedHint[MAX_READ_BYTES] = {0};

    while(current < CHALLENGE_AMOUNT){
        // challenge execution
        pipe2(pipefd, O_CLOEXEC);
        childFd = clone(challenges[current].challenge, childStack, CLONE_VM | CLONE_VFORK | SIGCHLD, NULL);
        read(pipefd[0], ofuscatedHint, MAX_READ_BYTES);
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(childFd, &childStatus, 0);

        printf("------------- DESAFIO -------------\n");
        printf(ofuscatedHint);
        printf("----- PREGUNTA PARA INVESTIGAR -----\n");
        printf(challenges[current].homeworkQuestion);
        nullTerminateIdx = read(readFd, userAnswer, MAX_READ_BYTES);
        userAnswer[nullTerminateIdx] = 0;
        if(strcmp(userAnswer, challenges[current].answer) == 0) {
            current++;
        } else {
            printf("\nRespuesta incorrecta: %s\n", userAnswer);
            sleep(2);
        }
        printf("\e[1;1H\e[2J");         // Clear screen. Commented bc it cleared strace calls. Comment out on final version
        memset(ofuscatedHint, 0, MAX_READ_BYTES);
        memset(userAnswer, 0, MAX_READ_BYTES);
    }
    free(childStackHead);
}

int naiveChallenge(){
    size_t hintLen = strlen(challenges[current].hint)+1;        //
    write(pipefd[1], challenges[current].hint, hintLen);
    exit(0);
}

int badFileDescriptorChallenge(){
    size_t hintLen = strlen(challenges[current].hint)+1;        //
    write(pipefd[1], "EBADF...\n\n", 10);
    if(write(EBADF_CHALLENGE_FD, challenges[current].hint, hintLen) == -1){
        int dupErr = dup(2);
        write(dupErr, "write: Bad file descriptor\n", 27);
        close(dupErr);
    }
    exit(0);
}