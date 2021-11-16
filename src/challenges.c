// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/challenges.h"

#define CHILD_STACK_SIZE 36864

#define PIPE_READ_FD    5
#define PIPE_WRITE_FD   6

#define EBADF_CHALLENGE_FD 13

#define NORMAL_DATAPOINTS 400

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

int naiveChallenge() __attribute__((section(".RUN_ME")));
int badFileDescriptorChallenge();
int filterChallenge();
int hideAnswerChallenge();
int gdbChallenge();
int normalDistributionChallenge();
int diffChallenge();

char* quineAnswer = "#include<stdio.h>\nchar*i=\"\\\\#include<stdio.h>\",n=\'\\n\',q=\'\"\',*p=\n\"%s%cchar*i=%c%c%s%c,n=\'%cn\',q=\'%c\',*p=%c%c%s%c,*m=%c%c%s%c%c;%s%c\",*m=\n\"int main(){return!printf(p,i+1,n,q,*i,i,q,*i,q,n,q,p,q,n,q,m,q,n,m,n);}\"\n;int main(){return!printf(p,i+1,n,q,*i,i,q,*i,q,n,q,p,q,n,q,m,q,n,m,n);}";

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
    { &naiveChallenge, ".RUN_ME\n", ".init .plt .text ? .fini .rodata .eh_frame_hdr\n\n", "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?\n"},
    { &filterChallenge, "K5n2UFfpFMUN\n", "La respuesta es K5n2UFfpFMUN\n\n", "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n"},
    { &hideAnswerChallenge, "BUmyYq5XxXGt\n", "¿?\n\nLa respuesta es BUmyYq5XxXGt\n\n", "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n"},
    { &naiveChallenge, "u^v\n", "Latexme\n\nSi\n \\mathrm{d}y = u^v{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\nentonces\ny =\n\n", "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n"},
    { &diffChallenge, "chin_chu_lan_cha\n", "La respuesta es chin_chu_lan_cha", "¿Cuáles son las características del protocolo SCTP?\n"},
    { &gdbChallenge, "gdb_rules\n", "b gdbme y encontrá el valor mágico\n\n", "¿Qué es un RFC?\n"},
    { &normalDistributionChallenge, "normal\n", "Me conoces\n", "¿Fue divertido?\n"}
};

void doChallenges(int readFd){
    char* childStackHead = (char*)malloc(CHILD_STACK_SIZE);
    if(childStackHead == NULL){
        fprintf(stderr, "No memory available for challenge processing\n");
        return;
    }
    void* childStack = childStackHead + CHILD_STACK_SIZE - 1;
    int childStatus;
    char ofuscatedHint[MAX_READ_BYTES] = {0};

    srand((unsigned)time(NULL));

    while(current < CHALLENGE_AMOUNT){
        int childFd;
        int nullTerminateIdx;

        printf("------------- DESAFIO -------------\n");

        // challenge execution
        pipe2(pipefd, O_CLOEXEC);
        childFd = clone(challenges[current].challenge, childStack, CLONE_VM | CLONE_VFORK | SIGCHLD, NULL);
        read(pipefd[0], ofuscatedHint, MAX_READ_BYTES);
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(childFd, &childStatus, 0);

        printf("%s",ofuscatedHint);
        printf("----- PREGUNTA PARA INVESTIGAR -----\n");
        printf("%s",challenges[current].homeworkQuestion);
        nullTerminateIdx = read(readFd, userAnswer, MAX_READ_BYTES);

        if(nullTerminateIdx == -1){
            fprintf(stderr, "Error checking user response\n");
            return;
        }
        if(nullTerminateIdx >= MAX_READ_BYTES){
            nullTerminateIdx = MAX_READ_BYTES - 1;
        }

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
    printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n");
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

int filterChallenge(){
    size_t hintLen = strlen(challenges[current].hint);
    write(pipefd[1], "Filter error\n\n", 15);             // Don´t write EOF
    int dupStdOut = dup(1);
    int dupErr = dup(2);
    char randCharArr[1];

    for(unsigned int i=0 ; i < hintLen-2 ; i++){         // Doesn´t take into account \n\n
        int randLen = (rand() % 5) + 4;
        for(int j=0 ; j < randLen ; j++){
            randCharArr[0] = (rand() % 94) + 32;
            write(dupErr, randCharArr, 1);
        }
        write(dupStdOut, challenges[current].hint+i, 1);
    }
    write(dupStdOut, challenges[current].hint + (hintLen-2), 3);

    close(dupStdOut);
    close(dupErr);
    exit(0);
}

int hideAnswerChallenge(){
    size_t hintLen = strlen(challenges[current].hint);
    write(pipefd[1], challenges[current].hint, 4);      // Prints '¿?\n\n'
    write(pipefd[1], "\033[8m", 4);                  // Conceals text
    write(pipefd[1], challenges[current].hint+4, hintLen-4);
    write(pipefd[1], "\033[28m", 5);                 // Conceal effect off
    exit(0);
}

// Normal random function obtained from https://phoxis.org/2013/05/04/generating-random-numbers-from-normal-distribution-in-c/
double randn (double mu, double sigma) {
    double U1, U2, W, mult;
    static double X1, X2;
    static int call = 0;

    if (call == 1) {
        call = 0;
        return (mu + sigma*(double)X2);
    }
 
    do {
        U1 = -1 + ((double)rand() / RAND_MAX)*2;
        U2 = -1 + ((double)rand() / RAND_MAX)*2;
        W = pow(U1, 2) + pow(U2, 2);
    } while (W >= 1 || W == 0);
 
    mult = sqrt((-2*log(W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;
    call = !call;
    return (mu + sigma*(double)X1);
}

int gdbChallenge(){
    size_t hintLen = strlen(challenges[current].hint);
    char* badAnswerResponse = "ENTER para reintentar.\n";
    char* answerBase = "La respuesta es ";
    write(pipefd[1], challenges[current].hint, hintLen);
    gdbme(pipefd[1], answerBase, challenges[current].answer, badAnswerResponse);
    write(pipefd[1], "\n", 2);
    exit(0);
}

int normalDistributionChallenge(){
    size_t hintLen = strlen(challenges[current].hint);
    write(pipefd[1], challenges[current].hint, hintLen);
    char buf[10] = {0};
    for(int i=0 ; i < NORMAL_DATAPOINTS ; i++){
        // float printNum = randn(0, 1);
        ftoa(randn(0, 1), buf, 6);
        write(pipefd[1], buf, 8);
        write(pipefd[1], " ", 1);
    }
    write(pipefd[1],"\n",2);
    exit(0);
}

int diffChallenge(){
    size_t hintLen = strlen(challenges[current].hint)+1;        //
    FILE* quineFile = fopen("./quine.c", "r");
    if(quineFile == NULL){
        // Print quine not found
        exit(0);
    }
    char fileRead[500];
    fgets(fileRead, 500, quineFile);
    int diffResult = strcmp(quineAnswer, fileRead);
    if (diffResult == 0){
        write(pipefd[1], challenges[current].hint, hintLen);
    }
    exit(0);
}