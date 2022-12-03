#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct vertex {
    char name[10];
    int big;    /* the cave is big = 1, or small = 0 */
    int deg;    /* degree of vertex */
    int index;
    struct vertex *adj[10]; /* assume that deg <= 10 */
} cave;

/* return the index if the name is in the list of caves */
/* return -1 if it was not found */
int cave_index(const char *name, cave *caves, int num_caves) {
    for (int i = 0; i < num_caves; i++)
        if (strcmp(name, caves[i].name) == 0)
            return i;
    return -1;
}

/* return index of cave with name */
int add_cave(char *name, cave *caves, int *num_caves) {
    int index = cave_index(name, caves, *num_caves);
    if (index != -1) return index;

    /* if we get here, add cave to the list */
    caves[*num_caves].big = (isupper(name[0])) ? 1 : 0; /* big or small cave? */
    caves[*num_caves].deg = 0;  /* there are no adjacents yet */
    strcpy(caves[*num_caves].name, name); /* copying the name */
    *num_caves += 1;    /* increasing num_caves */
    return *num_caves - 1;  /* returning last index */
}

/* assume there are no repeated edges */
void add_edge(cave *caves, int i1, int i2) {
    caves[i1].adj[caves[i1].deg++] = caves + i2;  /* setting the pointer */
    caves[i2].adj[caves[i2].deg++] = caves + i1;  /* setting the pointer */
}

void print_graph(cave *caves, int num_caves) {
    for (int i = 0; i < num_caves; i++)
        for (int j = 0; j < caves[i].deg; j++)
            printf("%s-%s\n", caves[i].name, caves[i].adj[j]->name);
}

/* sets the position bit to 1 and returns */
unsigned int set_one(unsigned int x, int bit) {
    return x | (1 << bit);
}

/* sets the position bit to 1 and returns */
unsigned int set_zero(unsigned int x, int bit) {
    return x & ~(1 << bit);
}

/* return 1 if the position bit is 1, else return 0 */
unsigned int get_bit(unsigned int x, int bit) {
    return (x >> bit) & 1;
}

/* I work with bitwise operations to record the visited small caves */
int num_paths(cave *cave, unsigned int visited_small, int small_twice, const int start_index) {
    if (strcmp(cave->name, "end") == 0)
        return 1;
    int small = !cave->big;
    if (!small_twice && small && get_bit(visited_small, cave->index))   /* we visited the first small cave twice */
        small_twice = 1;

    if (small)  /* small cave */
        visited_small = set_one(visited_small, cave->index);

    int i; unsigned int x = 0;
    for (i = 0; i < cave->deg; i++)
        x = set_one(x, cave->adj[i]->index);    /* everybody that is adjacent */
    x = set_zero(x, start_index);   /* can not go back to start */

    if (small_twice)
        x = x & ~visited_small; /* adjacent but not in visited_small */

    if (x == 0)
        return 0;
    else {
        int sum = 0;
        for (i = 0; i < cave->deg; i++)
            if (get_bit(x, cave->adj[i]->index))    /* eh aqui que eu bloqueio voltar para o START */
                sum += num_paths(cave->adj[i], visited_small, small_twice, start_index);
        return sum;
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

    int num_caves = 0;
    cave caves[50]; /* enough space and automatic memory allocation */
    int i1, i2; /* indexes of cave 1 and 2 */

    /* getting input and constructing the graph */
    while ((num = getline(&line, &len, stream)) != -1) {  /* getline returns -1 when EOF */
        line[num - 1] = '\0';   /* removendo o '\n' de line */
        char *save_ptr;
        char *name1 = strtok_r(line, "-", &save_ptr);    /* separate string by token "-" */
        char *name2 = strtok_r(NULL, "-", &save_ptr);
        i1 = add_cave(name1, caves, &num_caves);
        i2 = add_cave(name2, caves, &num_caves);
        add_edge(caves, i1, i2);
    }

    /* giving everybody indexes */
    int start_index = cave_index("start", caves, num_caves);
    for (int i = 0; i < num_caves; i++) {
        caves[i].index = cave_index(caves[i].name, caves, num_caves);
    }

    int total_paths = num_paths(&caves[start_index], 0, 0, start_index);
    printf("total_paths = %d\n", total_paths);
    //print_graph(caves, num_caves);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
