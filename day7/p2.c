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

ll expense(ll x) {
    ll xabs = llabs(x);
    return (xabs * (xabs+1LL)) / 2LL;
}

ll f(ll u, ll *y, ll *repeat, ll ndiff) {
    ll sum = 0;
    for (ll i = 0; i < ndiff; i++)
        sum += repeat[i] * expense(u - y[i]);
    return sum;
}

int intcmp(const void *a, const void *b) {
    const int *ia = (const int *) a;
    const int *ib = (const int *) b;
    return (*ia > *ib) - (*ia < *ib);
}

/* it assumes the array is sorted */
int diff_elem(int *x, int N, ll **y_ptr, ll **repeat_ptr) {
    if (N == 0) {
        *y_ptr = NULL;
        *repeat_ptr = NULL;
        return 0;
    }
    else {
        ll *y = malloc(N * sizeof(ll));
        ll *repeat = malloc(N * sizeof(ll));
        ll count = repeat[0] = 1LL;
        ll prev = y[0] = x[0], curr;
        for (ll i = 1; i < (ll) N; i++) {
            if ((curr = (ll) x[i]) > prev) {
                y[count] = curr;
                count++;
            }
            repeat[count-1LL]++;
            prev = curr;
        }
        *y_ptr = realloc(y, count * sizeof(ll));
        *repeat_ptr = realloc(repeat, count * sizeof(ll));
        return (int) count;
    }
}

int main() {
    int *x;
    int N = readalloc(100, "%d,", &x);
    qsort(x, N, sizeof(int), intcmp);
    ll *y, *repeat;
    int ndiff = diff_elem(x, N, &y, &repeat);
    /* the function is convex */
    /* it starts decreasing. the first time it increases we found our answer */
    ll prev = f(y[0], y, repeat, ndiff), curr;
    int i;
    for (i = 1; ; i++) {
        if ((curr = f(y[i], y, repeat, ndiff)) >= prev)
            break;
        prev = curr;
    }
    /* minha ideia for usar o fato da funcao ser convexa */
    /* tem que fazer um desenho para entender pq esse codigo merda da certo */
    /* agora, temos que y[i-2] <= argmin <= y[i] */
    ll k; prev = f(y[i-2], y, repeat, ndiff);
    for (k = y[i-2] + 1LL; ; k++) {
        if ((curr = f(k, y, repeat, ndiff)) >= prev)
            break;
        prev = curr;
    }

    printf("\nargmin = %lld\n", k-1);
    printf("\nmin = %lld\n\n", prev);

    //for (ll j = k-6LL; j < k+7LL; j++)
    //    printf("f(%lld) = %lld\n", j, f(j, y, repeat, ndiff));

    //print_array(x, N, "%d", ',');
    //print_array(y, ndiff, "%d", ',');
    //print_array(repeat, ndiff, "%d", ',');

    free(x);
    if (y)
        free(y);
    if (repeat)
        free(repeat);
}
