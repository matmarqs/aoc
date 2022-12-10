#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

/* DEFINITIONS */

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;   // failure
    }

    ifstream InputFile(argv[1]);

    /* read until end of file */
    string line;
    char op[4]; int v, x = 1, count = 1, sum = 0;
    while (getline(InputFile, line)) {
        if (line[0] == 'n')     // noop
            count++;
        else {  // addx v
            sscanf(line.c_str(), "%s %d", op, &v);
            if (++count % 40 == 20)
                sum += x * count;
            count++;
            x += v;
        }
        if (count % 40 == 20)
            sum += x * count;
    }
    cout << sum << endl;
}
