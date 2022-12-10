#include <cstdlib>
#include <iostream>
#include <fstream>  // read and write to files
using namespace std;

/* DEFINITIONS */

int update_sums(int s, int *s1, int *s2, int *s3) {
    if (s <= *s3)
        return 0;
    /* we are sure that s > s3 */
    if (s <= *s2) {
        *s3 = s;    // (s3 = s) <= s2 <= s1
        return 0;
    }
    /* now we are sure that s > s2 */
    if (s <= *s1) {
        *s3 = *s2;  // (s3 = s2) <= (s2 = s) <= s1
        *s2 = s;
    }
    else {
        *s3 = *s2;
        *s2 = *s1;  // (s3 = s2) <= (s2 = s1) <= (s1 = s)
        *s1 = s;
    }
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;   // failure
    }

    ifstream InputFile(argv[1]);

    /* read until end of file */
    int s = 0, s1, s2, s3;
    s1 = s2 = s3 = 0;
    string line;
    while (getline(InputFile, line)) {
        if (line.empty()) {
            update_sums(s, &s1, &s2, &s3);
            s = 0;
        }
        else
            s += stoi(line);
    }
    update_sums(s, &s1, &s2, &s3);  // last line
    cout << s1 + s2 + s3 << endl;
}
