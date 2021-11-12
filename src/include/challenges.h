#define _GNU_SOURCE
#include <sched.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define CHALLENGE_AMOUNT 12
#define MAX_READ_BYTES 4096

void doChallenges(int readFd);