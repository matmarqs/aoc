#include <stdio.h>
#include <stdlib.h>

#define SIZE    600

int min(int a, int b) {
    return (a > b) ? b : a;
}

typedef struct node {
    int num;
    int lowsum;
    struct node *down;
    struct node *right;
} node;

void setup_nodes(node *mat[], int m, int n) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            /* setting right */
            if (j < n-1) {
                mat[i][j].right = mat[i] + (j+1);
            }
            else {
                mat[i][j].right = NULL;
            }
            /* setting down */
            if (i < m-1) {
                mat[i][j].down = mat[i+1] + j;
            }
            else {
                mat[i][j].down = NULL;
            }
        }
}

//int low_sum(int m, int n, int mat[SIZE][SIZE], int i, int j) {
//    if (i == m-1 && j == n-1)
//        return mat[i][j];
//    else if (i == m-1 && j < n-1)
//        return mat[i][j] + low_sum(m, n, mat, i, j+1);
//    else if (i < m-1 && j == n-1)
//        return mat[i][j] + low_sum(m, n, mat, i+1, j);
//    else
//        return mat[i][j] + min(low_sum(m, n, mat, i, j+1), low_sum(m, n, mat, i+1, j));
//}

/* it should get the root node as input */
void setup_lowsum(node *mat[SIZE], int m, int n) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                if (j == 0)
                    mat[i][j].lowsum = mat[i][j].num;
                else
                    mat[i][j].lowsum = mat[i][j].num + mat[i][j-1].lowsum;
            }
            else if (j == 0)
                mat[i][j].lowsum = mat[i][j].num + mat[i-1][j].lowsum;
            else
                mat[i][j].lowsum = mat[i][j].num + min(mat[i-1][j].lowsum, mat[i][j-1].lowsum);
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
    setup_lowsum(mat, m, n);

    printf("lowest_sum = %d\n", mat[m-1][n-1].lowsum - mat[0][0].num);

    for (int i = 0; i < SIZE; i++)
        free(mat[i]);
    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
