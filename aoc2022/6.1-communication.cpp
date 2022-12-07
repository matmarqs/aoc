#include <cstdio>
#include <iostream>
#include <fstream>  // read and write to files
using namespace std;

/* DEFINITIONS */

int repeated_char(string str) {
    char hash[128] = { 0 };     // initialize every count as zero
    string::size_type i; char k, found = 0;
    for (i = 0; i < str.size(); i++) {
        k = str[i];
        hash[k]++;
        if (hash[k] == 2) {
            found = 1;
            break;
        }
    }
    if (found)
        return 1;   //pos[k];
    else
        return 0;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;   // failure
    }

    ifstream InputFile(argv[1]);

    /* read until end of file */
    string line;
    string chars;
    int num_distinct = 4;
    while (getline(InputFile, line)) {
        for (string::size_type i = 0; i < line.length(); i++) {
            chars = line.substr(i, num_distinct);
            if (!repeated_char(chars)) {
                cout << i + num_distinct << endl;
                break;
            }
        }
    }
}
