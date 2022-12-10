#include <cstdio>
#include <iostream>
#include <fstream>  // read and write to files
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
    int count = 0;
    int a1, b1, a2, b2;
    while (getline(InputFile, line)) {
        sscanf(line.c_str(), "%d-%d,%d-%d", &a1, &b1, &a2, &b2);
        if (!(b1 < a2 || b2 < a1))
            count += 1;
    }
    cout << count << endl;
}
