#include <cstdlib>
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
    int sum = 0, max_sum = 0;
    string line;
    while (getline(InputFile, line)) {
        if (line.empty()) {
            max_sum = (sum > max_sum) ? sum : max_sum;
            sum = 0;
        }
        else
            sum += stoi(line);
    }
    cout << max_sum << endl;
}
