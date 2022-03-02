#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

void minmax(ull *array, int len, ull *min, ull *max) {
    *max = *min = array[0];
    for (int i = 1; i < len; i++) {
        if (array[i] > *max)
            *max = array[i];
        if (array[i] < *min)
            *min = array[i];
    }
}

typedef struct {
    char fst, snd, btw; /* first, second and between */
} insert;

typedef struct {
    char type;
    ull count;
} bond_count;

typedef struct {
    char type;
    bond_count linked[12];
} bond_array;

/* returns -1 if not found */
int index_atom(char c, bond_array *array, int num_types) {
    for (int k = 0; k < num_types; k++)
        if (array[k].type == c)
            return k;
    return -1;
}

/* search the rule for the atom "at", returns '-' if it was not found */
/* we assume that at != NULL, but it can happen that at->next == NULL */
char type_btw(char fst, char snd, insert *rules, int len_rules) {
    for (int i = 0; i < len_rules; i++)
        if (rules[i].fst == fst && rules[i].snd == snd)
            return rules[i].btw;
    return '-';
}

/* the input should be the root atom */
void insert_step(insert *rules, int len_rules, bond_array *array, int num_types) {
    int i, j;
    ull storage[num_types][num_types];
    for (i = 0; i < num_types; i++)
        for (j = 0; j < num_types; j++) {
            storage[i][j] = array[i].linked[j].count;
            array[i].linked[j].count = 0ULL;
        }
    for (i = 0; i < num_types; i++)
        for (j = 0; j < num_types; j++) {
            char fst = array[i].type; char snd = array[i].linked[j].type;
            char btw = type_btw(fst, snd, rules, len_rules);
            int btw_index = index_atom(btw, array, num_types);
            array[i].linked[btw_index].count += storage[i][j];
            array[btw_index].linked[j].count += storage[i][j];
        }
}

int bonds_in_str(char *str, bond_array *array, int num_types) {
    int j, last = (int) (strlen(str) - 1);
    for (j = 0; j < last; j++) {
    /* we use the same function index_atom because array and array->linked are ordered in the same way */
        int index_array = index_atom(str[j], array, num_types);
        int index_linked = index_atom(str[j+1], array, num_types);
        array[index_array].linked[index_linked].count++;
    }
    int last_atom_index = index_atom(str[last], array, num_types);
    return last_atom_index;
}

ull count_atom(char atom, bond_array *array, int num_types, int last_atom_index) {
    int its_index = index_atom(atom, array, num_types);
    ull count = 0ULL;
    for (int j = 0; j < num_types; j++)
        count += array[its_index].linked[j].count;
    if (its_index == last_atom_index)
        count++;
    return count;
}

int main(int argc, char *argv[]) {
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    //ssize_t num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (!stream) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char template[30], fst, snd, btw;   // 30 is enough len, the template of input.txt has 20 chars
    insert *rules = malloc(120 * sizeof(insert));   // 120 is enough space, the input.txt file has 100 rules
    int i = 0;

    getline(&line, &len, stream);       /* getting the template */
    sscanf(line, "%s\n", template);
    getline(&line, &len, stream);       /* skipping the "\n" */
    /* getting the rules */
    while ((getline(&line, &len, stream)) != -1) {  /* getline returns -1 when EOF */
        sscanf(line, "%c%c -> %c\n", &fst, &snd, &btw);
        rules[i].fst = fst; rules[i].snd = snd; rules[i].btw = btw;
        i++;
    }
    int len_rules = i;

    /* inicializando a estrutura para contar os atomos */
    int num_types = 0;
    bond_array array[12]; /* we have 10 types at most */
    for (i = 0; i < len_rules; i++) {
        int notin = 1;
        for (int j = 0; j < num_types; j++)
            if (rules[i].fst == array[j].type) {
                notin = 0;
                break;
            }
        if (notin) {
            array[num_types].type = rules[i].fst;
            num_types++;
        }
    }

    /* initializing all the bounds */
    for (i = 0; i < num_types; i++) {
        for (int j = 0; j < num_types; j++) {
            array[i].linked[j].type = array[j].type;
            array[i].linked[j].count = 0ULL;
        }
    }

    /* counting the bounds from the template */
    int last_atom_index = bonds_in_str(template, array, num_types); /* the last atom does not have a right atom to bond */

    for (i = 0; i < 40; i++)
        insert_step(rules, len_rules, array, num_types);

    /* printing final state */
    ull count_array[num_types];
    for (i = 0; i < num_types; i++)
        printf("%c  %llu\n", array[i].type, count_array[i] = count_atom(array[i].type, array, num_types, last_atom_index));

    ull max, min; minmax(count_array, num_types, &min, &max);
    printf("max - min = %llu\n", max - min);

    free(rules);
    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
