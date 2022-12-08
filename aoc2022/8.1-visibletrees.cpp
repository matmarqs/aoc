#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/* DEFINITIONS */

int visible(vector <vector <int>> forest, int i, int j) {
    int m = forest.size(), n = forest[0].size();
    if (i == 0 || i == m-1 || j == 0 || j == n-1)
        return 1;
    else {
        int k; int top, bot, left, right;
        top = bot = left = right = 1;
        for (k = 0; k < i; k++)
            if (forest[k][j] >= forest[i][j]) {
                top = 0; break;
            }
        if (top) return 1;
        for (k = m-1; k > i; k--)
            if (forest[k][j] >= forest[i][j]) {
                bot = 0; break;
            }
        if (bot) return 1;
        for (k = 0; k < j; k++)
            if (forest[i][k] >= forest[i][j]) {
                left = 0; break;
            }
        if (left) return 1;
        for (k = n-1; k > j; k--)
            if (forest[i][k] >= forest[i][j]) {
                right = 0; break;
            }
        if (right) return 1;
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
    string line;
    vector <vector <int>> forest;
    int i = 0, j;
    while (getline(InputFile, line)) {
        forest.push_back(vector <int> ());
        for (int j = 0; j < (int) line.length(); j++) {
            forest[i].push_back(line[j]);
        }
        i++;
    }
    int m = forest.size(), n = forest[0].size(), count = 0;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            count += visible(forest, i , j);
    cout << count << endl;
}
