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

/* assumindo que estamos no dia 0 de um peixe, */
/* f eh a funcao que retorna o numero de peixes gerados */
ll f(ll x) {
    if (x < 1LL)    /* no dia 1 eh produzido o primeiro peixo novo */
        return 1LL; /* antes do dia 1 so tem um peixe mesmo, pq ainda nao foi produzido nenhum */
    else
        return f(x - 7LL) + f(x - 9LL); /* produzindo um novo peixe e resetando contagens para 7 e 9 dias */
}

/* com esse main() abaixo, meu PC demorou em torno de 1 min para conseguir resolver */
int main() {
    int *x;
    ll days = 256LL;
    int n = readalloc(100, "%d,", &x);
    print_array(x, n, "%d", ',');

    // Os dias presentes no input sao 1, 2, 3, 4 e 5
    // calcular tudo no começo por eficiencia
    ull function[6] = { 0LL, (ull) f(days-1LL), (ull) f(days-2LL),
        (ull) f(days-3LL), (ull) f(days-4LL), (ull) f(days-5LL) };

    ull totalfish = 0ULL;
    for (int i = 0; i < n; i++)
        totalfish += function[x[i]];

    printf("totalfish = %llu\n", totalfish);
    free(x);
    return 0;
}
