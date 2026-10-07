#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

void print(const char *who, clock_t start)
{
    clock_t end = clock();
    double ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("%s | PID = %d | PPID = %d | time = %.6f ms\n", who, getpid(), getppid(), ms);
}

int main(void)
{
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        clock_t start = clock();
        print("Child1", start);
        exit(EXIT_SUCCESS);
    }
    pid2 = fork();
    if (pid2 == 0) {
        clock_t start = clock();
        print("Child2", start);
        exit(EXIT_SUCCESS);
    }
    clock_t start = clock();
    wait(NULL);
    wait(NULL);
    print("Parent", start);
    return 0;
}
