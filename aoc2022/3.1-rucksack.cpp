#include <cstdlib>
#include <iostream>
#include <fstream>  // read and write to files
using namespace std;

/* DEFINITIONS */

int priority(char ch) {
    if (islower(ch))
        return ch - 'a' + 1;
    else
        return ch - 'A' + 27;
}

char shared_item(string fst, string snd) {
    int i, j, len1 = fst.length(), len2 = snd.length();
    for (i = 0; i < len1; i++) {
        for (j = 0; j < len2; j++) {
            if (fst[i] == snd[j])
                return fst[i];
        }
    }
    return EOF;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;   // failure
    }

    ifstream InputFile(argv[1]);

    /* read until end of file */
    int len, sum = 0, p;
    string line, fst, snd;
    while (getline(InputFile, line)) {
        len = line.length();
        fst = line.substr(0, len/2);
        snd = line.substr(len/2, len/2);
        p = priority(shared_item(fst, snd));
        sum += p;
    }
    cout << "sum = " << sum << endl;
}
