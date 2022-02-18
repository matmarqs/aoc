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

/* esse foi o algoritmo que o ThePrimeagen escreveu, ele É MUITO MELHOR */
/* https://www.youtube.com/watch?v=__gDZny1uwY */
/* a execução do programa foi instantanea em todos os casos */
int main() {
    int *x, i, d;
    int days = 256;
    int n = readalloc(100, "%d,", &x);
    /* array do numero de peixes de acordo com o dia */
    ull fish[9];
    for (d = 0; d < 9; d++)
        fish[d] = 0ULL;
    /* colocando os peixes no array fish */
    for (i = 0; i < n; i++)
        fish[x[i]]++;
    /* fazendo os shifts e reproducoes */
    for (i = 0; i < days; i++) {
        ull D = fish[0];
        fish[0] = 0ULL;
        for (d = 0; d < 9; d++) {
            fish[d-1] = fish[d];
            fish[d] = 0ULL;
        }
        fish[8] = D;
        fish[6] += D;
    }
    ull totalfish = 0ULL;
    for (d = 0; d < 9; d++)
        totalfish += fish[d];
    printf("totalfish = %llu\n", totalfish);
    free(x);
    return 0;
}
