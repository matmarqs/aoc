#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

/* num == -1 <=> it is regular number */
typedef struct snail {
    int num;
    struct snail *left;
    struct snail *right;
} snail;

snail *alloc_regular(int num) {
    snail *s = malloc(sizeof(snail));
    s->num = num;
    s->left = s->right = NULL;
    return s;
}

snail *alloc_snail(snail *s_left, snail *s_right) {
    snail *s = malloc(sizeof(snail));
    s->num = -1;
    s->left = s_left;
    s->right = s_right;
    return s;
}

snail *alloc_pair(int num_left, int num_right) {
    snail *s_left = alloc_regular(num_left);
    snail *s_right = alloc_regular(num_right);
    snail *s = alloc_snail(s_left, s_right);
    return s;
}

void free_snail(snail *s) {
    snail *s_left = s->left, *s_right = s->right;
    free(s);
    if (s_left) /* if not NULL */
        free_snail(s_left);
    if (s_right)
        free_snail(s_right);
}

void print_snail(snail *s) {
    if (s->num == -1) {
        putchar('[');
        print_snail(s->left);
        putchar(',');
        print_snail(s->right);
        putchar(']');
    }
    else
        printf("%d", s->num);
}

void puts_snail(snail *s) {
    print_snail(s);
    putchar('\n');
}

int main(int argc, char *argv[]) {
    //FILE *stream;
    //char *line = NULL;
    //size_t len = 0;
    //ssize_t num;

    //if (argc != 2) {
    //    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    //    exit(EXIT_FAILURE);
    //}

    //stream = fopen(argv[1], "r");
    //if (!stream) {
    //    perror("fopen");
    //    exit(EXIT_FAILURE);
    //}

    //while ((num = getline(&line, &len, stream)) != -1) {  /* getline returns -1 when EOF */
    //    ;
    //}

    snail *a = alloc_pair(1, 2);
    snail *b = alloc_pair(3, 4);
    snail *s = alloc_snail(a, b);
    puts_snail(s);
    free_snail(s);

    //free(line);
    //fclose(stream);
    //exit(EXIT_SUCCESS);
    return 0;
}
