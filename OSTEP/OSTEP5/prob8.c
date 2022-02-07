/* OSTEP 5 p. 14, #8
   Write a program that creates two children, and connects the standard output of one to the 
   standard input of the other, using the pipe() system call. 
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int p[2];
    char *childargs[2];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s cmd1 cmd2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(p) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) {         // create first child
        close(STDOUT_FILENO);  // first child process closes stdout
        dup(p[1]);             // and connects write end of pipe to stdout
        close(p[0]);
        close(p[1]);
        childargs[0] = strdup(argv[1]);    // set up args for and exec cmd in argv[1]
        childargs[1] = NULL;
        execvp(childargs[0], childargs);
    }
    if (fork() == 0) {          // create second child
        close(STDIN_FILENO);    // second child closes stdin
        dup(p[0]);              // and connects read end of pipe to stdin
        close(p[0]);
        close(p[1]);
        childargs[0] = strdup(argv[2]);   // set up args for and exec cmd in argv[2]
        childargs[1] = NULL;
        execvp(childargs[0], childargs);
    }
  
    close(p[0]);  // parent closes pipe file descriptors
    close(p[1]);  
    wait(NULL);   // parent waits for children to complete
    wait(NULL);
  
    return 0;

}
