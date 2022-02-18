#include <stdio.h>
#include <string.h>

//typedef long long ll;
//typedef unsigned long long ull;

int main() {
    char trash[58 + 1];
    char s[4][7 + 1];       /* +1 means the '\0' */
    unsigned long count = 0UL, length;
    char c;
    int index = -1, i = 0;
    while ((c = getchar()) != EOF) {
        switch(index) {
            case -1:
                if (c == '|') {
                    trash[i-1] = '\0';  /* o ultimo char de trash foi um espaco */
                    index++;    /* passando para depois do '|' */
                    c = getchar();  /* skipando um espaco */
                    i = 0;  /* resetando o indice das strings */
                }
                else
                    trash[i++] = c;
                break;
            case 0: case 1: case 2:
                if (c == ' ') {
                    s[index][i] = '\0'; /* fechando a string */
                    index++;
                    i = 0;
                }
                else
                    s[index][i++] = c;
                break;
            case 3:
                if (c == '\n') {
                    s[index][i] = '\0'; /* fechando a string */
                    index = -1;
                    i = 0;
                    //printf("%s %s %s %s\n", s[0], s[1], s[2], s[3]);
                    for (int k = 0; k < 4; k++) {
                        switch(length = strlen(s[k])) {
                            case 2: case 3: case 4: case 7: /* digits 1, 7, 4 and 8 */
                                count += 1;
                                break;
                            default:
                                break;
                        }
                    }
                }
                else
                    s[index][i++] = c;
            default:
                break;
        }
    }

    printf("count = %lu\n", count);
}
