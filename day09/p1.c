#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE    (100)

#define printMatrix(mat, m, n, s) {   \
    for (int i=0; i<(m); i++)         \
    for (int j=0; j<(n); j++)         \
    printf(s"%c", mat[i][j],          \
    (j == (n)-1) ? '\n' : ' '); }

int lowpoint(int map[][SIZE], int M, int N, int i, int j) {
    int check = 1;
    if (i > 0)
        if (!(check *= (map[i][j] < map[i-1][j])))
            return 0;
    if (i < M-1)
        if (!(check *= (map[i][j] < map[i+1][j])))
            return 0;
    if (j > 0)
        if (!(check *= (map[i][j] < map[i][j-1])))
            return 0;
    if (j < N-1)
        check *= (map[i][j] < map[i][j+1]);
    return check;
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

    /* getting input */
    int map[SIZE][SIZE], M = 0, N = 0;  /* map is M x N */
    int once = 1;
    while ((num = getline(&line, &len, stream)) != -1) {    /* getline returns -1 when EOF */
        if (once)
            N = (int) (num - 1), once = 0;  /* subtracting 1, because of '\n' */
        for (int j = 0; j < N; j++)
            map[M][j] = (int) (line[j] - '0');
        M++;
    }

    //printf("M = %d\nN = %d\n", M, (int) N);
    //printMatrix(map, M, N, "%d");

    int sum = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (lowpoint(map, M, N, i, j))
                sum += map[i][j] + 1;
        }
    }
    printf("sum = %d\n", sum);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}
