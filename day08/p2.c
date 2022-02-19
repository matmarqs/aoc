#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chrcmp(const void *a, const void *b) {
    const char *ia = (const char *) a;
    const char *ib = (const char *) b;
    return (*ia > *ib) - (*ia < *ib);
}

int main(int argc, char *argv[]) {
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t N;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <stream>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (!stream) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int sum = 0;
    while ((N = getline(&line, &len, stream)) != -1) {
        char pattern[10][7 + 1];    /* +1 because of '\0' */
        char digit[4][7 + 1];
        sscanf(line, "%s %s %s %s %s %s %s %s %s %s | %s %s %s %s\n",
                pattern[0], pattern[1], pattern[2], pattern[3],
                pattern[4], pattern[5], pattern[6], pattern[7],
                pattern[8], pattern[9], digit[0], digit[1], digit[2], digit[3]);

        /* somando 1 em todos os arrays para incluir o '\0' */
        char num_1[2+1],
             num_7[3+1],
             num_4[4+1],
             len5[3][5+1], num_2[5+1], num_3[5+1], num_5[5+1],  /* len5 = { num_2, num_3, num_5 } */
             len6[3][6+1], num_0[6+1], num_6[6+1], num_9[6+1],  /* len6 = { num_0, num_6, num_9 } */
             num_8[7+1];

        unsigned long len;
        int i, i5 = 0, i6 = 0;
        for (i = 0; i < 10; i++) {
            switch(len = strlen(pattern[i])) {
                case 2:
                    strcpy(num_1, pattern[i]);
                    break;
                case 3:
                    strcpy(num_7, pattern[i]);
                    break;
                case 4:
                    strcpy(num_4, pattern[i]);
                    break;
                case 5:
                    strcpy(len5[i5++], pattern[i]);
                    break;
                case 6:
                    strcpy(len6[i6++], pattern[i]);
                    break;
                case 7:
                    strcpy(num_8, pattern[i]);
                    break;
            }
        }

        char *p;
        char c = 'c', d = 'd';  /* inicializar so pro compilador nao reclamar. eles ainda vao ser calculados */
        //char a, b, f;
        //for (p = num_7; *p != '\0'; p++)    /* esta em num_7 */
        //    if (!strchr(num_1, *p)) {       /* mas nao em num_1 */
        //        a = *p;
        //        break;
        //    }
        for (i = 0; i < 3; i++) {
            if (strchr(len5[i], num_1[0]) && strchr(len5[i], num_1[1])) /* quem contem num_1 ? */
                break;
        }
        int pos3 = i;
        strcpy(num_3, len5[pos3]); /* quem contem num_1 eh o num_3 */

        char bd[2]; /* chars 'b' e 'd', ainda nao sabemos quem eh quem */
        for (i = 0, p = num_4; *p != '\0'; p++) {   /* esta em num_4 */
            if (!strchr(num_1, *p))                 /* mas nao no num_1 */
                bd[i++] = *p;                       /* sao 'b' ou 'd' */
        }

        /* descobrindo quem eh o num_5 */
        for (i = 0; i < 3; i++) {
            if (strchr(len5[i], bd[0]) && strchr(len5[i], bd[1]))   /* "bd" esta contido no num_5 */
                break;
        }
        int pos5 = i;
        strcpy(num_5, len5[pos5]);

        /* num_2 eh o que restou do array len5 */
        for (i = 0; i < 3; i++)
            if (i != pos3 && i != pos5)
                break;
        int pos2 = i;
        strcpy(num_2, len5[pos2]);

        for (p = num_2; *p != '\0'; p++)    /* char em num_1 e num_2 */
            if (strchr(num_1, *p)) {        /* eh o 'c' */
                c = *p;
                break;
            }

        ///* esta no num_1 mas que nao eh 'c', eh o 'f'  */
        //f = (num_1[0] == c) ? num_1[1] : num_1[0];

        /* esta em "bd" e esta em num_3, eh o 'd' */
        d = (strchr(num_3, bd[0])) ? bd[0] : bd[1];

        for (i = 0; i < 3; i++) {
            if (!strchr(len6[i], d))
                strcpy(num_0, len6[i]);     /* len=6 que nao tem o 'd' é o "0". */
            else if (!strchr(len6[i], c))
                strcpy(num_6, len6[i]);     /* len=6 que nao tem o 'c' é o "6". */
            else
                strcpy(num_9, len6[i]);     /* len=6 que restou é o "9". */
        }

        /* agora basta comparar as strings fazendo uns qsort em ordem alfabetica */
        qsort(num_0, strlen(num_0), sizeof(char), chrcmp);
        qsort(num_1, strlen(num_1), sizeof(char), chrcmp);
        qsort(num_2, strlen(num_2), sizeof(char), chrcmp);
        qsort(num_3, strlen(num_3), sizeof(char), chrcmp);
        qsort(num_4, strlen(num_4), sizeof(char), chrcmp);
        qsort(num_5, strlen(num_5), sizeof(char), chrcmp);
        qsort(num_6, strlen(num_6), sizeof(char), chrcmp);
        qsort(num_7, strlen(num_7), sizeof(char), chrcmp);
        qsort(num_8, strlen(num_8), sizeof(char), chrcmp);
        qsort(num_9, strlen(num_9), sizeof(char), chrcmp);

        qsort(digit[0], strlen(digit[0]), sizeof(char), chrcmp);
        qsort(digit[1], strlen(digit[1]), sizeof(char), chrcmp);
        qsort(digit[2], strlen(digit[2]), sizeof(char), chrcmp);
        qsort(digit[3], strlen(digit[3]), sizeof(char), chrcmp);

        int base = 1000;
        for (i = 0; i < 4; i++) {
            if (strcmp(num_0, digit[i]) == 0)
                sum += 0 * base;
            else if (strcmp(num_1, digit[i]) == 0)
                sum += 1 * base;
            else if (strcmp(num_2, digit[i]) == 0)
                sum += 2 * base;
            else if (strcmp(num_3, digit[i]) == 0)
                sum += 3 * base;
            else if (strcmp(num_4, digit[i]) == 0)
                sum += 4 * base;
            else if (strcmp(num_5, digit[i]) == 0)
                sum += 5 * base;
            else if (strcmp(num_6, digit[i]) == 0)
                sum += 6 * base;
            else if (strcmp(num_7, digit[i]) == 0)
                sum += 7 * base;
            else if (strcmp(num_8, digit[i]) == 0)
                sum += 8 * base;
            else    /* the last case, if num_9 == digit[i] */
                sum += 9 * base;
            base /= 10;
        }

        /* DEBUG PURPOSES */
        //printf("%s %s %s %s %s %s %s %s %s %s\n",
        //        pattern[0], pattern[1], pattern[2], pattern[3],
        //        pattern[4], pattern[5], pattern[6], pattern[7],
        //        pattern[8], pattern[9]);
        //printf("%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu\n",
        //        strlen(pattern[0]), strlen(pattern[1]), strlen(pattern[2]), strlen(pattern[3]),
        //        strlen(pattern[4]), strlen(pattern[5]), strlen(pattern[6]), strlen(pattern[7]),
        //        strlen(pattern[8]), strlen(pattern[9]));
        //printf("%s %s %s %s\n", digit[0], digit[1], digit[2], digit[3]);
        //printf("%lu %lu %lu %lu\n", strlen(digit[0]), strlen(digit[1]), strlen(digit[2]), strlen(digit[3]));

    }

    printf("sum = %d\n", sum);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}
