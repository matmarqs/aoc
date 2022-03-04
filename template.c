#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (!stream) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((num = getline(&line, &len, stream)) != -1) {  /* getline returns -1 when EOF */
        ;
    }

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
