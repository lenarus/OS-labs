#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char line[1024];
    char *args[64];

    while (1) {
        printf("> ");
        fflush(stdout);
        if (!fgets(line, 1024, stdin)) break;
        line[strcspn(line, "\n")] = 0;
        int i = 0;
        char *tok = strtok(line, " \t");
        while (tok && i < 63) {
            args[i++] = tok;
            tok = strtok(NULL, " \t");
        }
        args[i] = NULL;
        if (i == 0) continue;

        if (fork() == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        }
    }
    return 0;
}
