#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

/* DEFINITIONS */

void draw_pixel(int *pos, int x) {
    if (*pos == x-1 || *pos == x || *pos == x+1)
        putchar('#');
    else
        putchar('.');
    if (++*pos == 40)
        putchar('\n'), *pos = 0;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;   // failure
    }

    ifstream InputFile(argv[1]);

    /* read until end of file */
    string line;
    char op[4]; int v, x = 1, pos = 0;
    while (getline(InputFile, line)) {
        if (line[0] == 'n')     // noop
            draw_pixel(&pos, x);
        else {  // addx v
            sscanf(line.c_str(), "%s %d", op, &v);
            draw_pixel(&pos, x);
            draw_pixel(&pos, x);
            x += v;
        }
    }
}
