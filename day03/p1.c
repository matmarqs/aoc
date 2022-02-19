#include <stdio.h>
#include <stdlib.h>

#define SIZE    (12)

typedef struct {
    char bin[SIZE+1];
} nbit;

/* reads data from standard input, storages them in x_ptr and y_ptr and returns N */
int readalloc(nbit **lines, int chunk) {
    int i = 0, N = 0;
    nbit *x = (nbit *) malloc(chunk * sizeof(nbit));

    /* getting input */
    while (scanf("%s", x[N].bin) != EOF) {
        i++, N++;
        if (i > chunk-1) {
            x = (nbit *) realloc(x, (N+chunk)*sizeof(nbit));
            i = 0;
        }
    }

    /* resizing the arrays to correct size */
    *lines = (nbit *) realloc(x, N * sizeof(nbit));
    return N;
}

int bintodec(char s[SIZE]) {
    int n = 0, base = 1;
    for (int i = SIZE-1; i >= 0; i--) {
        n += (s[i] - '0') * base;
        base *= 2;
    }
    return n;
}

int main() {
    nbit *lines;
    int N = readalloc(&lines, 100);

    char gamma[SIZE], epsilon[SIZE];
    int count0, count1;
    for (int j = 0; j < SIZE; j++) {
        count0 = count1 = 0;
        for (int i = 0; i < N; i++) {
            if (lines[i].bin[j] == '1')
                count1++;
            else
                count0++;
        }
        if (count1 >= count0)
            gamma[j] = '1', epsilon[j] = '0';
        else
            gamma[j] = '0', epsilon[j] = '1';
    }

    printf("gamma * epsilon = %d\n", bintodec(gamma) * bintodec(epsilon));
    //printf(" gamma  = %.*s\n", SIZE, gamma);
    //printf("epsilon = %.*s\n", SIZE, epsilon);
    free(lines);
    return 0;
}
