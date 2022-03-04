#include <stdio.h>
#include <stdlib.h>

#define SIZE    510

/* -1 is infinity */
int min(int a, int b) { return a == -1 ? b : (b == -1 ? a : (a > b ? b : a)); }

typedef struct node {
    int num;
    int dist;
    int unvisited;
    struct node *nbr[4];    /* 1 = left, 2 = up, 3 = right, 4 = down */
} node;

void setup_nodes(node *mat[], int m, int n) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            mat[i][j].unvisited = 1;
            mat[i][j].dist = -1;    /* infinity */
            mat[i][j].nbr[0] = (j > 0) ? (mat[i] + j-1) : NULL;
            mat[i][j].nbr[1] = (i > 0) ? (mat[i-1] + j) : NULL;
            mat[i][j].nbr[2] = (j < n-1) ? (mat[i] + j+1) : NULL;
            mat[i][j].nbr[3] = (i < m-1) ? (mat[i+1] + j) : NULL;
        }
}

int still_unvisited(node *mat[], int m, int n, int *ii, int *jj) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (mat[i][j].unvisited && mat[i][j].dist != -1) {
                *ii = i;
                *jj = j;
                return 1;
            }
    return 0;
}

void dijkstra(node *mat[], int m, int n) {
    mat[0][0].unvisited = 0;
    mat[0][0].dist = 0;
    int i = 0, j = 0, stop = 0;
    while (!stop) {
        for (int dir = 0; dir < 4; dir++)
            if (mat[i][j].nbr[dir]) /* not NULL */
                mat[i][j].nbr[dir]->dist = min(mat[i][j].dist + mat[i][j].nbr[dir]->num, mat[i][j].nbr[dir]->dist);
        mat[i][j].unvisited = 0;
        stop = !still_unvisited(mat, m, n, &i, &j);
    }
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

    node *mat[SIZE];
    for (int i = 0; i < SIZE; i++) {
        mat[i] = malloc(SIZE * sizeof(node));
    }

    /* getting input */
    int m = 0, n = 0;
    int once = 0;
    while ((num = getline(&line, &len, stream)) != -1) {  /* getline returns -1 when EOF */
        if (!once)
            n = (int) num - 1, once = 1;
        for (int j = 0; j < n; j++)
            mat[m][j].num = (int) (line[j] - '0');
        m++;
    }

    printf("m = %d, n = %d\n", m, n);
    setup_nodes(mat, m, n);
    dijkstra(mat, m, n);

    printf("lowest_sum = %d\n", mat[m-1][n-1].dist);

    /* freeing */
    for (int i = 0; i < SIZE; i++)
        free(mat[i]);
    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);

    return 0;
}
