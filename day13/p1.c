#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAT_X   895
#define MAT_Y   1309
#define FOLD_N  12

typedef struct {
    char axis;
    int num;
} fold;

void set_zero_matrix(int matrix[MAT_X][MAT_Y]) {
    for (int i = 0; i < MAT_Y; i++)
        for (int j = 0; j < MAT_X; j++)
            matrix[i][j] = 0;
}

int reflect(int matrix[MAT_X][MAT_Y], char axis, int num, int bound) {
    int count = 0;
    int i, j;
    if (axis == 'x') {
    }
    else if (axis == 'y') {
    }
    return count;
}

int main(int argc, char *argv[]) {
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    //ssize_t num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (!stream) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int matrix[MAT_X][MAT_Y];
    fold instr[FOLD_N];

    int fold_input = 0;
    int i = 0, x, y, bound_x, bound_y;
    while (getline(&line, &len, stream) != -1) {  /* getline returns -1 when EOF */
        if (strcmp(line, "\n") == 0) {
            fold_input = 1;
            continue;
        }

        if (fold_input) {
            sscanf(line, "fold along %c=%d\n", &instr[i].axis, &instr[i].num);
            i++;
        }
        else {
            sscanf(line, "%d,%d\n", &x, &y);
            matrix[y][x] = 1;
        }
    }

    if (instr[0].axis == 'x') {
        x = instr[0].num;
    }
    if (instr[0].axis == 'y') {
        y = instr[0].num;
    }

    //for (int j = 0; j < i; j++)
    //    printf("fold along %c=%d\n", instr[j].axis, instr[j].num);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}
