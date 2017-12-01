#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

static int isParent = 1;

void parent_term(int sig) {
    if (isParent) {
        exit(1);
    }
}

int single_p(char** arglist) {
    pid_t process_id = fork();
    int child = 0;
    if (process_id < 0) {
        fprintf(stderr, "Error : %s", strerror(errno));
        fflush(stdout);
    }
    if (process_id == 0) {
        int res = execvp(arglist[0], (const char **)(arglist + 1));
        if (res == -1) {
            fprintf(stderr, "ExecVp Fialed with error code %s\n", strerror(errno));
            fflush(stdout);
            exit(1);
        }
    }
    if (process_id > 0) {
        isParent = 0;
        waitpid(child, NULL, 1);
        isParent=1;
    }

    return 1;
}

int contains(char ** data, char * key, int count) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(data[i], key) == 0) {
            return i;
        }
    }

    return  -1;
}
int process_arglist(int count, char** arglist){
    arglist[count] = NULL;
    int idx;
    if(strcmp(arglist[count-1],"&") == 0){
        // TODO: daemon proc
    }
    else if((idx = contains(arglist, "|", count)) != -1) {
        // TODO: pipe proc
    }
    else{
        single_p(arglist);
    }
}
int prepare(void){
    signal(SIGINT, parent_term);
    signal(SIGCHLD, SIG_IGN);
    return 0;
}
int finalize(void){

    return 0;
}

