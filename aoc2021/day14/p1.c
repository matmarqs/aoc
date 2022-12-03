#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>

typedef struct atom {
    char type;
    struct atom *prev;
    struct atom *next;
} atom;

typedef struct {
    char fst, snd, btw; /* first, second and between */
} insert;

typedef struct {
    char type;
    int count;
} atom_count;

atom *create_polymer(char *template) {
    int len = strlen(template);
    atom *root = malloc(sizeof(atom));
    root->prev = NULL;
    atom *curr = root;
    for (int i = 0; i < len - 1; i++) {
        curr->type = template[i];
        //putchar(curr->type);    // debug
        curr->next = malloc(sizeof(atom));
        curr->next->prev = curr;
        curr = curr->next;
    }
    /* the last atom does not a proper "next" */
    curr->type = template[len - 1];
    //putchar(curr->type);    // debug
    curr->next = NULL;
    //putchar('\n');  // debug
    return root;
}

/* the input should be the root atom */
void free_polymer(atom *at) {
    while (at) {
        atom *next = at->next;
        free(at);
        at = next;
    }
}

void insert_btw(atom *at, char btw) {
    atom *at_snd = at->next;
    atom *at_btw = malloc(sizeof(atom));
    at_btw->type = btw;
    at_btw->prev = at;
    at_btw->next = at_snd;
    at->next = at_btw;
    at_snd->prev = at_btw;
}

/* search the rule for the atom "at", returns '-' if it was not found */
/* we assume that at != NULL, but it can happen that at->next == NULL */
char type_btw(atom *at, insert *rules, int len_rules) {
    if (at->next) {
        char first = at->type, second = at->next->type;
        for (int i = 0; i < len_rules; i++)
            if (rules[i].fst == first && rules[i].snd == second)
                return rules[i].btw;
    }
    return '-';
}

/* the input should be the root atom */
void insert_step(atom *at, insert *rules, int len_rules, atom_count *array_count, int num_types) {
    while (at) {
        atom *next = at->next;
        char type = type_btw(at, rules, len_rules);
        if (type != '-') {
            insert_btw(at, type);
            for (int j = 0; j < num_types; j++)
                if (array_count[j].type == type)
                    array_count[j].count++;
        }
        at = next;
    }
}

void print_polymer(atom *root) {
    while (root) {
        atom *next = root->next;
        putchar(root->type);
        root = next;
    }
    putchar('\n');
}

int count_char_in_str(char *str, int len, char c) {
    int count = 0;
    for (int i = 0; i < len; i++)
        if (str[i] == c)
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
    //printf("%s\n", template);
    getline(&line, &len, stream);       /* skipping the "\n" */
    /* getting the rules */
    while ((getline(&line, &len, stream)) != -1) {  /* getline returns -1 when EOF */
        sscanf(line, "%c%c -> %c\n", &fst, &snd, &btw);
        //printf("%c %c -> %c\n", fst, snd, btw);
        rules[i].fst = fst; rules[i].snd = snd; rules[i].btw = btw;
        i++;
    }
    int len_rules = i;

    /* inicializando a estrutura para contar os atomos */
    int num_types = 0;
    atom_count count_array[12]; /* we have 10 types at most */
    for (i = 0; i < len_rules; i++) {
        int notin = 1;
        for (int j = 0; j < num_types; j++)
            if (rules[i].fst == count_array[j].type) {
                notin = 0;
                break;
            }
        if (notin) {
            count_array[num_types].type = rules[i].fst;
            count_array[num_types].count = count_char_in_str(template, strlen(template), rules[i].fst);
            num_types++;
        }
    }

    atom *root = create_polymer(template);

    for (i = 0; i < 10; i++)
        insert_step(root, rules, len_rules, count_array, num_types);

    for (i = 0; i < num_types; i++)
        printf("%c  %d\n", count_array[i].type, count_array[i].count);
    //print_polymer(root);

    free_polymer(root);
    free(rules);
    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
