#include <cstdlib>
#include <iostream>
#include <fstream>  // read and write to files
using namespace std;

/* DEFINITIONS */

int value(char in) {
    if (in == 'A')
        return 1;
    else if (in == 'B')
        return 2;
    else
        return 3;
}

int score(char in, char out) {
    int s;
    switch (out) {
        case 'X':
            s = 0;
            break;
        case 'Y':
            s = 3;
            break;
        default:
            s = 6;
            break;
    }
    if (in == 'A') {
        if (out == 'X')
            s += value('C');
        else if (out == 'Y')
            s += value('A');
        else
            s += value('B');
    }
    if (in == 'B') {
        if (out == 'X')
            s += value('A');
        else if (out == 'Y')
            s += value('B');
        else
            s += value('C');
    }
    if (in == 'C') {
        if (out == 'X')
            s += value('B');
        else if (out == 'Y')
            s += value('C');
        else
            s += value('A');
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
