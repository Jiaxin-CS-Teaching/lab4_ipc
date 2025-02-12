#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    /* define a file descriptor with 2 entries */
    int fds_1[2];
    /* hint: define a new file descriptor */
    
    int pid1, pid2;
    /* hint: define a new pid for third child */

    /* create a pipe using fds_1 */
    // read end - fds_1[0]
    // write end - fds_1[1]
    if(pipe(fds_1) == -1)
    {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    /* hint: create second pipe */

    /* fork first child */
    if((pid1 = fork()) < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    /* first child code path */
    if(pid1 == 0)
    {
        close(1);  /* close default stdout */
        dup2(fds_1[1], 1);  /* redirect stdout to pipe write end */
        close(fds_1[0]);  /* close unnecessary pipe read end */

        /* hint: perform operations for second pipe */

        if(execlp("cat", "cat", "pipe3.c", (char *) 0) < 0)
        {
            fprintf(stderr, "exec failed\n");
            exit(1);
	    }
    } 

    /* fork second child */
    if((pid2 = fork()) < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    /* second child code path */
    if(pid2 == 0)
    {
        close(0);  /* close default stdin */
        dup2(fds_1[0], 0);  /* redirect stdin to pipe read end */
        close(fds_1[1]);  /* close unnecessary pipe write end */

        /* hint: perform operations for second pipe */
        /* hint: where should output go? */

        if(execlp("grep", "grep", "close", (char *) 0) < 0)
        {
            fprintf(stderr, "exec failed\n");
            exit(1);
	    }
    }

    /* hint: fork third child */

    /* hint: third child code path */
    /* hint: where does input come from? */
    /* hint: where should output go? */

    /* parent does not need any ends of pipe */
    close(fds_1[0]); 
    close(fds_1[1]);
    /* hint: perform operations for second pipe */

    /* parent waits for children to complete */
    /* hint: modify a bit to wait for three children */
    for(int i = 0; i < 2; i++)
    {
	    wait(NULL);
    }
}