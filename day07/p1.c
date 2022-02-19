#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
typedef unsigned long long ull;

#define print_array(a, n, s, sep) { \
    for (int i=0; i<n; i++)         \
    printf(s"%c", a[i],             \
    (i == n-1) ? '\n' : sep); }

int readalloc(int chunk, const char *s, int **x_ptr) {
    int i = 0, N = 0;
    int *x = (int *) malloc(chunk * sizeof(int));
    /* getting input */
    while (scanf(s, &x[N]) != EOF) {
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

int f(int u, int *y, int *repeat, int ndiff) {
    int sum = 0;
    for (int i = 0; i < ndiff; i++)
        sum += repeat[i] * abs(u - y[i]);
    return sum;
}

int intcmp(const void *a, const void *b) {
    const int *ia = (const int *) a;
    const int *ib = (const int *) b;
    return (*ia > *ib) - (*ia < *ib);
}

/* it assumes the array is sorted */
int diff_elem(int *x, int N, int **y_ptr, int **repeat_ptr) {
    if (N == 0) {
        *y_ptr = NULL;
        *repeat_ptr = NULL;
        return 0;
    }
    else {
        int *y = malloc(N * sizeof(int));
        int *repeat = malloc(N * sizeof(int));
        int count = repeat[0] = 1;
        int prev = y[0] = x[0], curr;
        for (int i = 1; i < N; i++) {
            if ((curr = x[i]) > prev) {
                y[count] = curr;
                count++;
            }
            repeat[count-1]++;
            prev = curr;
        }
        *y_ptr = realloc(y, count * sizeof(int));
        *repeat_ptr = realloc(repeat, count * sizeof(int));
        return count;
    }
}

int main() {
    int *x;
    int N = readalloc(100, "%d,", &x);
    qsort(x, N, sizeof(int), intcmp);
    int *y, *repeat;
    int ndiff = diff_elem(x, N, &y, &repeat);
    /* the function is convex */
    /* it starts decreasing. the first time it increases we found our answer */
    int prev = f(y[0], y, repeat, ndiff), curr;
    int i;
    for (i = 1; ; i++) {
        if ((curr = f(y[i], y, repeat, ndiff)) >= prev)
            break;
        prev = curr;
    }
    /* agora, temos que y[i-1] <= argmin <= y[i] */
    int k;
    for (k = y[i-1] + 1; ; k++) {
        if ((curr = f(k, y, repeat, ndiff)) >= prev)
            break;
        prev = curr;
    }

    printf("argmin = %d\n", k-1);
    printf("min = %d\n", prev);

    //print_array(x, N, "%d", ',');
    //print_array(y, ndiff, "%d", ',');
    //print_array(repeat, ndiff, "%d", ',');

    free(x);
    if (y)
        free(y);
    if (repeat)
        free(repeat);
}
