/*
 * 
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    int x = 100;
    int pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        x = 103;
        printf("in child process\n");
    } else {
        x = 106;
        printf("in parent process\n");
    }
    return 0;
}