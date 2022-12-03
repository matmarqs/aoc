#include <stdio.h>
#include <stdlib.h>

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
int score(char c) {
    switch (c) {
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;
        default:    /* if c is not closed */
            return -1;
    }
}

/* a = str[0] is always a valid open char */
/* return -1 if incomplete */
/* else return 0 if not corrupted */
/* return score if corrupted */
int corrupted(chunk *p, const char *str) {
    char next = str[0];
    if (next == complement(p->c)) {
        chunk *out = p->out;
        if (!out) { /* if out == NULL (the root one) */
            free(p);    /* the chunk is over and not corrupted */
            if (open(str[1])) { /* the string has not ended, there are other chunks to analyze */
                chunk *root = chunk_alloc(NULL, str[1]);
                return corrupted(root, str + 2);
            }
            /* assume a chunk always begin valid open */
            else    /* the string has ended and is not corrupted as a whole */
                return 0;
        }
        else {
            free(p);
            out->in = NULL;
            return corrupted(out, str + 1);
        }
    }
    else if (closed(next)) {   /* it is corrupted */
        chunk_free_everything(p);   /* now we return the score */
        return score(next);
    }
    else if (open(next)) {
        p->in = chunk_alloc(p, next);
        return corrupted(p->in, str + 1);
    }
    else {
        chunk_free_everything(p);
        return -1;  /* incomplete */
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
    int total = 0;
    while ((num = getline(&line, &len, stream)) != -1) {    /* getline returns -1 when EOF */
        chunk *root = chunk_alloc(NULL, line[0]);
        int corrup = corrupted(root, line+1);
        if (corrup != 0 && corrup != -1)
            total += corrup;
    }

    printf("total = %d\n", total);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
