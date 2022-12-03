#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAT_X   900     // 895
#define MAT_Y   1400    // 1309
#define FOLD_N  12

typedef struct {
    char axis;
    int num;
} fold;

void print_grid(int mat[MAT_X][MAT_Y], int max_x, int max_y) {
    int i, j;
    for (i = 0; i < max_y; i++) {
        for (j = 0; j < max_x - 1; j++)
            printf("%c", (mat[i][j] == 1) ? '#' : '.');
        printf("%c\n", (mat[i][max_x - 1] == 1) ? '#' : '.');
    }
}

void set_zero_matrix(int matrix[MAT_X][MAT_Y]) {
    for (int i = 0; i < MAT_Y; i++)
        for (int j = 0; j < MAT_X; j++)
            matrix[i][j] = 0;
}

int reflect(int matrix[MAT_X][MAT_Y], char axis, int num, int *bound, int bound_x, int bound_y) {
    int count = 0;
    int i, j, k;
    if (axis == 'x')
        for (i = 0; i < *bound; i++)
            for (j = 1; j <= num; j++) {
                k = num + j;
                if (k < bound_x && matrix[i][k] == 1)
                    matrix[i][num - j] = 1;
                if (matrix[i][num - j] == 1)
                    count++;
            }
    else if (axis == 'y')
        for (j = 0; j < *bound; j++)
            for (i = 1; i <= num; i++) {
                k = num + i;
                if (k < bound_y && matrix[k][j] == 1)
                    matrix[num - i][j] = 1;
                if (matrix[num - i][j] == 1)
                    count++;
            }
    *bound = num;
    return count;
}

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

    int matrix[MAT_X][MAT_Y];
    fold instr[FOLD_N];
    int fold_input = 0;
    int i = 0, x, y, bound_x = 0, bound_y = 0;

    while ((num = getline(&line, &len, stream)) != -1) {  /* getline returns -1 when EOF */
        //printf("%s", line);
        if (strlen(line) == 1) {    /* line = "\n" */
            fold_input = 1;
            continue;
        }
        if (fold_input) {
            sscanf(line, "fold along %c=%d\n", &instr[i].axis, &instr[i].num);
            i++;
        }
        else {
            sscanf(line, "%d,%d\n", &x, &y);
            //char *save_ptr;
            //char *str_x = strtok_r(line, ",", &save_ptr);   /* separate string by token "," */
            //char *str_y = strtok_r(NULL, ",", &save_ptr);
            //sscanf(str_x, "%d", &x);
            //sscanf(str_y, "%d\n", &y);
            matrix[y][x] = 1;
            if (x > bound_x)
                bound_x = x;
            if (y > bound_y)
                bound_y = y;
        }
    }
    bound_x++;
    bound_y++;

    int count, bound;
    printf("char = %c, num = %d\n", instr[0].axis, instr[0].num);
    printf("bound_x = %d, bound_y = %d\n", bound_x, bound_y);
    bound = (instr[0].axis == 'x') ? bound_y : bound_x;
    count = reflect(matrix, instr[0].axis, instr[0].num, &bound, bound_x, bound_y);
    //count = reflect(matrix, instr[1].axis, instr[1].num, &bound, bound_x, bound_y);
    printf("count = %d\n", count);

    //for (int j = 0; j < i; j++)
    //    printf("fold along %c=%d\n", instr[j].axis, instr[j].num);
    //print_grid(matrix, bound_x, bound_y);
    print_grid(matrix, bound_x, bound_y);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}
