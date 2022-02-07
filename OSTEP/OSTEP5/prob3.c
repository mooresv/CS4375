/* OSTEP 5, p. 14, #3
   Ensure that the child process prints hello before the parent process prints goodbye.
   Try to do this without calling wait().
   Do not rely on timing by using sleep().
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int pipefd[2];
    char buf;
    pipe(pipefd);
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        sleep(rand()%5);
        printf("hello\n");
        close(pipefd[0]);
        write(pipefd[1],"x",1);   // child writes to write end of pipe after printing hello
        close(pipefd[1]);
    } else {
        // parent goes down this path (original process)
        sleep(rand()%5);
        close(pipefd[1]);
        read(pipefd[0],&buf,1);   // parent is block until able to read character that child wrote
        close(pipefd[0]);
        printf("goodbye\n");      // parent prints goodbye after reading character that child wrote
    }
    return 0;
}
