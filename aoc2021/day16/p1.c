#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int v;  /* version */
    int t;  /* type */
    int lit;    /* literal value, -1 if it is not literal */
} pac;

int bin2dec(char *bin, int binlen) {
    int dec = 0, fac = 1;
    for (int i = binlen - 1; i >= 0; i--, fac *= 2)
        dec += (bin[i] - '0') * fac;
    return dec;
}

/* copying from "org" until we have "num" characters, including both */
void strcpy_pos(const char *src, char *dest, int org, int num) {
    for (int i = 0; i < num; i++)
        dest[i] = src[org + i];
    dest[num] = '\0';
}

int sum_version(char *bin, int *total_len) {
    int version = 4 * (bin[0] - '0') + 2 * (bin[1] - '0') + (bin[2] - '0');
    int type = 4 * (bin[3] - '0') + 2 * (bin[4] - '0') + (bin[5] - '0');
    if (type == 4) {
        int prefix, num_groups = 1;
        for (prefix = 6; bin[prefix] - '0'; prefix += 5, num_groups++); /* do nothing */
        //int litlen = 4 * num_groups;
        //char lit[litlen + 1];   /* +1 because of '\0' */
        //for (int j = 0; j < num_groups; j++) {
        //    for (int until4 = 0; until4 < 4; until4++)
        //        lit[j + until4] = bin[7 + 5 * j + until4];
        //}
        //lit[litlen] = '\0'; /* end of string */
        //int lit_val = bin2dec(lit, litlen);
        *total_len += 6 + 5 * num_groups;
    }
    else {
        int id = bin[6] - '0';
        if (id) {
            char length_str[12];    /* +1 because of '\0' */
            strcpy_pos(bin, length_str, 7, 11);
            int num = bin2dec(length_str, 11), pos = 18;
            for (int i = 0; i < num; i++)
                version += sum_version(bin + pos, &pos);
            *total_len += pos;
        }
        else {  /* next 15 bits are the total length in bits of the sub-packets */
            char length_str[16];    /* +1 because of '\0' */
            strcpy_pos(bin, length_str, 7, 15);
            int len = bin2dec(length_str, 15);
            int count_len = 0;
            while (count_len < len)
                version += sum_version(bin + 22 + count_len, &count_len);
            *total_len += 22 + count_len;
        }
    }
    return version;
}

void hex2bin(char hex, char *line_bin, int pos) {
    char *bin;
    int valid = 1;
    switch (hex) {
        case '0': bin = "0000"; break; case '1': bin = "0001"; break; case '2': bin = "0010"; break;
        case '3': bin = "0011"; break; case '4': bin = "0100"; break; case '5': bin = "0101"; break;
        case '6': bin = "0110"; break; case '7': bin = "0111"; break; case '8': bin = "1000"; break;
        case '9': bin = "1001"; break; case 'A': bin = "1010"; break; case 'B': bin = "1011"; break;
        case 'C': bin = "1100"; break; case 'D': bin = "1101"; break; case 'E': bin = "1110"; break;
        case 'F': bin = "1111"; break; default: valid = 0; break;
    }
    if (valid) {
        int i;
        for (i = 0; i < 4; i++)
            line_bin[pos + i] = bin[i];
    }
}

/* line_bin will have to be free afterwards */
char *str_hex2bin(char *line, int linelen, int *binlen) {
    *binlen = 4 * linelen;   /* each hexadecimal becomes 4 bits */
    char *line_bin = (char *) malloc((*binlen + 1) * sizeof(char));  /* +1 because of '\0' */
    int j = 0;
    for (int i = 0; i < linelen; i++) {
        hex2bin(line[i], line_bin, j);
        j += 4;
    }
    line_bin[*binlen] = '\0';
    return line_bin;
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

    /* the input is only one line */
    int linelen = (int) getline(&line, &len, stream) - 1;
    line[linelen] = '\0';   /* getting rid of '\n' */

    /* transforming hex to bin */
    int binlen;
    char *line_bin = str_hex2bin(line, linelen, &binlen);

    /* solving the problem */
    int total_len = 0;
    int sum = sum_version(line_bin, &total_len);

    printf("sum of versions = %d\n", sum);

    free(line_bin);
    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
