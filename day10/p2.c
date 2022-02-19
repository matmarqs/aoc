#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

int llcmp(const void *a, const void *b) {
    const ll *ia = (const ll *) a;
    const ll *ib = (const ll *) b;
    return (*ia > *ib) - (*ia < *ib);
}

int open(char c) { switch (c) { case '(': case '[': case '{': case '<': return 1; default: return 0; } }
int closed(char c) { switch (c) { case ')': case ']': case '}': case '>': return 1; default: return 0; } }
char complement(char c) {
    switch(c) {
        case '(':
            return ')';
        case '[':
            return ']';
        case '{':
            return '}';
        case '<':
            return '>';
        default:
            return c;
    }
}

typedef struct link {
    char c;
    struct link *in;
    struct link *out;
} chunk;

chunk *chunk_alloc(chunk *out, char c) {
    chunk *p = malloc(sizeof(chunk));
    p->c = c;
    p->out = out;
    p->in = NULL;
    return p;
}

void chunk_free_everything(chunk *p) {
    while (p) { /* p != NULL */
        chunk *out = p->out;
        free(p);
        p = out;
    }
}

/* it assume c is closed */
ll corrup_score(char c) {
    assert(closed(c));
    switch (c) {
        case ')':
            return 3LL;
        case ']':
            return 57LL;
        case '}':
            return 1197LL;
        case '>':
            return 25137LL;
        default:    /* if c is not closed */
            return 0LL;
    }
}

/* assumes c to be closed */
int each_complete(char c) {
    assert(closed(c));
    switch (c) {
        case ')':
            return 1LL;
        case ']':
            return 2LL;
        case '}':
            return 3LL;
        case '>':
            return 4LL;
        default:    /* if c is not closed */
            return 0LL;
    }
}

ll free_and_score_complete(chunk *p) {
    ll total = 0LL;
    while (p) { /* p != NULL */
        total = 5LL * total + each_complete(complement(p->c));  /* p->c is always open */
        chunk *out = p->out;
        free(p);
        p = out;
    }
    return total;
}

/* a = str[0] is always a valid open char */
/* if incomplete, returns (-score): return < 0 */
/* if not corrupted, returns 0:     return = 0 */
/* if corrupted, returns score:     return > 0  */
ll analyze(chunk *p, const char *str) {
    char next = str[0];
    if (next == complement(p->c)) {
        chunk *out = p->out;
        if (!out) { /* if out == NULL (the root one) */
            free(p);    /* the chunk is over and not corrupted */
            if (open(str[1])) { /* the string has not ended, there are other chunks to analyze */
                chunk *root = chunk_alloc(NULL, str[1]);
                return analyze(root, str + 2);
            }
            /* assume a chunk always begin valid open */
            else    /* the string has ended and is not corrupted as a whole */
                return 0LL;
        }
        else {
            free(p);
            out->in = NULL;
            return analyze(out, str + 1);
        }
    }
    else if (closed(next)) {   /* it is corrupted */
        chunk_free_everything(p);   /* now we return the score */
        return corrup_score(next);
    }
    else if (open(next)) {
        p->in = chunk_alloc(p, next);
        return analyze(p->in, str + 1);
    }
    else {
        return -free_and_score_complete(p);
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

    /* getting input */
    ll scores[94];     /* 94 is the number of line in input.txt */
    int count = 0;
    while ((num = getline(&line, &len, stream)) != -1) {    /* getline returns -1 when EOF */
        chunk *root = chunk_alloc(NULL, line[0]);
        ll score = analyze(root, line+1);
        if (score < 0LL)
            scores[count++] = -score;   /* the opposite */
    }

    qsort(scores, count, sizeof(ll), llcmp);
    int mid = count / 2;    /* the middle element is this, because of truncated division */
    printf("middle score = %lld\n", scores[mid]);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
