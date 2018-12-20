#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void parse(char *line, char ** argv){

    while (*line != '\0')
    {
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';

        *argv++ = line;
        printf("%s", line);


        while (*line != '\0' && *line != ' ' &&
               *line != '\t' && *line != '\n')

            line++;
    }

    *argv = '\0';
}

void  execute(char **argv)
{
    pid_t  pid;
    int    status;

    if ((pid = fork()) < 0) {
        printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0) {
        if (execvp(*argv, argv) < 0) {
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
    }
    else {
        wait(&status) ;
    }
}

int main(void)
{
    char line[1024];
    char *argv[5];

    while (1) {

        printf("prompt >> ");
        fgets(line, sizeof(line), stdin);
        parse(line, argv);
        printf("\n");

        if (strcmp(argv[0], "exit") == 0)
            exit(0);
        execute(argv);
    }
    return 0;

}
