#include <stdio.h>
#include <stdlib.h>

/* reads data from standard input, storages them in x_ptr and y_ptr and returns N */
int readalloc(int **x_ptr, int chunk) {
    int i = 0, N = 0;
    int *x = (int *) malloc(chunk * sizeof(int));

    /* getting input */
    while (scanf("%d", &x[N]) != EOF) {
        i++; N++;
        if (i > chunk-1) {
            x = (int *) realloc(x, (N+chunk)*sizeof(int));
            i = 0;
        }
    }

    /* resizing the arrays to correct size */
    *x_ptr = (int *) realloc(x, N * sizeof(int));
    return N;
}

int main() {
    int *x;
    int N = readalloc(&x, 2010);
    int prev = 0, curr, count = 0;
    for (int i = 0; i < N-2; i++) {
        curr = x[i] + x[i+1] + x[i+2];
        if (curr > prev)
            count++;
        prev = curr;
    }
    printf("count = %d\n", count-1);
    free(x);
    return 0;
}
