// gcc -Wall -Wextra -O2 -s -pedantic -std=c99 problem_02.c -o problem_02

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int file = open("testfile.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (file < 0)
    {
        fprintf(stderr, "error: unable to open the file");
        return EXIT_FAILURE;
    }

    int fork_res = fork();
    if (fork_res > 0) // Parent
    {
        const char *message = "This is the parent process\n";
        write(file, message, strlen(message));
        close(file);
    }
    else if (fork_res == 0)  // Child
    {
        const char *message = "This is the child process\n";
        write(file, message, strlen(message));
        close(file);
    }
    else
    {
        fprintf(stderr, "error: unable to fork");
        close(file);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
