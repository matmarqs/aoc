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

char shared_item(string fst, string snd, string thrd) {
    int i, j, k;
    int len1 = fst.length(), len2 = snd.length(), len3 = thrd.length();
    for (i = 0; i < len1; i++)
        for (j = 0; j < len2; j++)
            for (k = 0; k < len3; k++)
                if (fst[i] == snd[j] && snd[j] == thrd[k])
                    return fst[i];
    return EOF;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;   // failure
    }

    ifstream InputFile(argv[1]);

    /* read until end of file */
    int sum = 0, p;
    string line1, line2, line3;
    while (getline(InputFile, line1)) {
        getline(InputFile, line2);
        getline(InputFile, line3);
        p = priority(shared_item(line1, line2, line3));
        sum += p;
    }
    cout << "sum = " << sum << endl;
}
