
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int ac, char **av, char **env)
{
    int fd[2];
    int pid1;
    int pid2;
    // char *args[] = {"cat", "lexer.c", NULL};

    if (pipe(fd) == -1)
        return -1;
    pid1 = fork();
    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve("/usr/bin/cat", (char *[3]){"cat", "lexer.c", NULL}, env);
    }

    pid2 = fork();
    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve("/usr/bin/grep", (char *[3]){"grep", "lexer", NULL}, env);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}