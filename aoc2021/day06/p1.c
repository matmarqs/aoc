#include <stdio.h>
#include <stdlib.h>

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

/* diminui o numero de dias de cada um dos peixes e retorna o numero de peixes com 0 */
int updateFish(int **fish_ptr, int N) {
    int count = 0, i;
    int *fish = *fish_ptr;
    /* atualizando os peixes existentes */
    for (i = 0; i < N; i++) {
        fish[i]--;
        if (fish[i] < 0) {    /* contamos os que estiverem com dia -1 */
            count++;
            fish[i] = 6;    /* resetar para dia 6 */
        }
    }
    int new_N = N + count;
    /* alocar espaço para os peixes que irao a nascer */
    if (count > 0)
        fish = (int *) realloc(fish, new_N * sizeof(int));
    /* setando os novos peixes no dia 8 */
    for (i = N; i < new_N; i++)
        fish[i] = 8;

    *fish_ptr = fish;
    return new_N;
}

int main() {
    int *fish;
    int num_days = 80;
    int N = readalloc(100, "%d,", &fish);

    for (int d = 0; d < num_days; d++)
        N = updateFish(&fish, N);

    printf("N = %d\n", N);
    free(fish);
    return 0;
}
