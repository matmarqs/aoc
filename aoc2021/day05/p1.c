#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE(a)    (sizeof(a) / sizeof(a[0]))

#define max(a, b)   (((a) > (b)) ? (a) : (b))
#define min(a, b)   (((a) > (b)) ? (b) : (a))

#define printArray(a, s) {      \
    int n = ARRAYSIZE(a);       \
    for (int i=0; i<n; i++)     \
    printf(s"%c", a[i],         \
    (i == n-1) ? '\n' : ' '); }

#define printMatrix(mat, s) {   \
    int m = ARRAYSIZE(mat);     \
    int n = ARRAYSIZE(mat[0]);  \
    for (int i=0; i<m; i++)     \
    for (int j=0; j<n; j++)     \
    printf(s"%c", mat[i][j],    \
    (j == n-1) ? '\n' : ' '); }


typedef struct {
    int *x1, *y1, *x2, *y2;
} lines;

/* reads data from standard input, storages them in x_ptr and y_ptr and returns N */
int readalloc(lines *L, int chunk) {
    int i = 0, N = 0;
    int *x_1 = (int *) malloc(chunk * sizeof(int));
    int *y_1 = (int *) malloc(chunk * sizeof(int));
    int *x_2 = (int *) malloc(chunk * sizeof(int));
    int *y_2 = (int *) malloc(chunk * sizeof(int));
    /* getting input */
    while (scanf("%d,%d -> %d,%d\n", &x_1[N], &y_1[N], &x_2[N], &y_2[N]) != EOF) {
        i++; N++;
        if (i > chunk-1) {
            x_1 = (int *) realloc(x_1, (N+chunk)*sizeof(int));
            y_1 = (int *) realloc(y_1, (N+chunk)*sizeof(int));
            x_2 = (int *) realloc(x_2, (N+chunk)*sizeof(int));
            y_2 = (int *) realloc(y_2, (N+chunk)*sizeof(int));
            i = 0;
        }
    }
    /* resizing the arrays to correct size */
    L->x1 = (int *) realloc(x_1, N * sizeof(int));
    L->y1 = (int *) realloc(y_1, N * sizeof(int));
    L->x2 = (int *) realloc(x_2, N * sizeof(int));
    L->y2 = (int *) realloc(y_2, N * sizeof(int));
    return N;
}

void freeLine(lines *L) {
    free(L->x1); free(L->y1);
    free(L->x2); free(L->y2);
}

/* É, eu sei que isso eh muito feio */
int get_max(int N, lines *L) {
    int max_elem = L->x1[0];
    for (int k = 0; k < N; k++)
        max_elem = max(max(max(L->x1[k], L->x2[k]), max(L->y1[k], L->y2[k])), max_elem);
    return max_elem;
}

/* consider only horiz or vert lines, where x1 = x2 or y1 = y2 */
int main() {
    int i, j, k, N;
    lines L;
    N = readalloc(&L, 100);
    int len = get_max(N, &L) + 1;
    int matrix[len][len];
    for (i = 0; i < len; i++)
        for (j = 0; j < len; j++)
            matrix[i][j] = 0;

    int maior, menor;
    for (k = 0; k < N; k++) {
        if (L.x1[k] == L.x2[k]) {
            maior = max(L.y1[k], L.y2[k]);
            menor = min(L.y1[k], L.y2[k]);
            for (i = menor; i <= maior; i++)
                matrix[i][L.x1[k]]++;
        }
        else if (L.y1[k] == L.y2[k]) {
            maior = max(L.x1[k], L.x2[k]);
            menor = min(L.x1[k], L.x2[k]);
            for (j = menor; j <= maior; j++)
                matrix[L.y1[k]][j]++;
        }
    }

    int count = 0;
    for (i = 0; i < len; i++)
        for (j = 0; j < len; j++)
            if (matrix[i][j] > 1)
                count++;

    printf("count = %d\n", count);
    freeLine(&L);
    return 0;
}
