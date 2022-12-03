#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char atual[N][SIZE+1];

    /** OXYGEN **/
    /* copiando tudo pro atual */
    for (int i = 0; i < N; i++)
        strcpy(atual[i], lines[i].bin);
    int num = N, j = 0;
    int count0, count1;
    while (num > 1 && j < SIZE) {
        count0 = count1 = 0;
        for (int i = 0; i < num; i++) {
            if (atual[i][j] == '1')
                count1++;
            else
                count0++;
        }
        char c = (count1 >= count0) ? '1' : '0';
        int k = 0;
        for (int i = 0; i < num; i++) {
            if (atual[i][j] == c)
                strcpy(atual[k++], atual[i]);
        }
        num = k;
        j++;
    }
    int oxygen = bintodec(atual[0]);

    /** CARBON **/
    /* copiando tudo pro atual */
    for (int i = 0; i < N; i++)
        strcpy(atual[i], lines[i].bin);
    num = N, j = 0;
    while (num > 1 && j < SIZE) {
        count0 = count1 = 0;
        for (int i = 0; i < num; i++) {
            if (atual[i][j] == '1')
                count1++;
            else
                count0++;
        }
        char c = (count1 >= count0) ? '0' : '1';
        int k = 0;
        for (int i = 0; i < num; i++) {
            if (atual[i][j] == c)
                strcpy(atual[k++], atual[i]);
        }
        num = k;
        j++;
    }
    int carbon = bintodec(atual[0]);

    //printf("gamma * epsilon = %d\n", bintodec(gamma) * bintodec(epsilon));
    printf("oxygen = %d\n", oxygen);
    printf("carbon = %d\n", carbon);
    printf("oxygen * carbon = %d\n", oxygen * carbon);
    //printf("epsilon = %.*s\n", SIZE, epsilon);
    free(lines);
    return 0;
}
