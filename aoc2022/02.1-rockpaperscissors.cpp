#include <cstdlib>
#include <iostream>
#include <fstream>  // read and write to files
using namespace std;

/* DEFINITIONS */

int score(char in, char out) {
    int s;
    switch (out) {
        case 'X':
            s = 1;
            break;
        case 'Y':
            s = 2;
            break;
        default:
            s = 3;
            break;
    }
    if (in == 'A') {
        if (out == 'X')
            s += 3;
        else if (out == 'Y')
            s += 6;
    }
    if (in == 'B') {
        if (out == 'Y')
            s += 3;
        else if (out == 'Z')
            s += 6;
    }
    if (in == 'C') {
        if (out == 'Z')
            s += 3;
        else if (out == 'X')
            s += 6;
    }
    return s;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;   // failure
    }

    ifstream InputFile(argv[1]);

    /* read until end of file */
    string line;
    char in, out; int sum = 0;
    while (getline(InputFile, line)) {
        in = line[0], out = line[2];
        sum += score(in, out);
    }
    cout << sum << endl;
}
