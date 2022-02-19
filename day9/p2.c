#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE    (100)

#define printMatrix(mat, m, n, s) {   \
    for (int i=0; i<(m); i++)         \
    for (int j=0; j<(n); j++)         \
    printf(s"%c", mat[i][j],          \
    (j == (n)-1) ? '\n' : ' '); }

typedef struct {
    int h;  /* height */
    int check;
} loc;

int lowpoint(loc map[][SIZE], int M, int N, int i, int j) {
    int low = 1;
    if (i > 0)
        if (!(low *= (map[i][j].h < map[i-1][j].h)))
            return 0;
    if (i < M-1)
        if (!(low *= (map[i][j].h < map[i+1][j].h)))
            return 0;
    if (j > 0)
        if (!(low *= (map[i][j].h < map[i][j-1].h)))
            return 0;
    if (j < N-1)
        low *= (map[i][j].h < map[i][j+1].h);
    return low;
}

int basin(loc map[][SIZE], int M, int N, int i, int j) {
    int size = 0;
    if (map[i][j].check == 9)   /* stop when finding a 9 */
        return 0;
    else if (map[i][j].check == 0) {    /* if not checked */
        size++; /* counting the current location */
        map[i][j].check = 1;    /* now it is checked */
        /* expanding to frontiers */
        if (i > 0)
            size += basin(map, M, N, i-1, j);
        if (i < M-1)
            size += basin(map, M, N, i+1, j);
        if (j > 0)
            size += basin(map, M, N, i, j-1);
        if (j < N-1)
            size += basin(map, M, N, i, j+1);
    }
    return size;
}

int main(int argc, char *argv[]) {
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t num;

    assert(argc == 2 && "Only one argument => input.txt path");
    //if (argc != 2) {
    //    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    //    exit(EXIT_FAILURE);
    //}

    stream = fopen(argv[1], "r");
    if (!stream) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    /* getting input */
    loc map[SIZE][SIZE];
    int M = 0, N = 0;  /* map is M x N */
    int once = 1;
    while ((num = getline(&line, &len, stream)) != -1) {    /* getline returns -1 when EOF */
        if (once)
            N = (int) (num - 1), once = 0;  /* subtracting 1, because of '\n' */
        for (int j = 0; j < N; j++) {
            if ((map[M][j].h = (int) (line[j] - '0')) == 9)
                map[M][j].check = 9;
            else
                map[M][j].check = 0;
        }
        M++;
    }

    int size, s1 = 0, s2 = 0, s3 = 0; /* largest sizes 1st, 2nd and 3rd */
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (lowpoint(map, M, N, i, j)) {
                size = basin(map, M, N, i, j);
                if (size > s1) {
                    s3 = s2;
                    s2 = s1;
                    s1 = size;
                }
                else if (size > s2) {
                    s3 = s2;
                    s2 = size;
                }
                else if (size > s3)
                    s3 = size;
            }
        }
    }
    printf("product of 3 largest basins = %d\n", s1*s2*s3);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}
