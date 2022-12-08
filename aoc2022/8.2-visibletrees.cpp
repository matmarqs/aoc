#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/* DEFINITIONS */

int scenic_score(vector <vector <int>> forest, int i, int j) {
    int m = forest.size(), n = forest[0].size();
    int k, tscore, bscore, lscore, rscore;
    tscore = bscore = lscore = rscore = 0;
    for (k = i-1; k >= 0; k--) {
        tscore++;
        if (forest[k][j] >= forest[i][j])
            break;
    }
    for (k = i+1; k <= m-1; k++) {
        bscore++;
        if (forest[k][j] >= forest[i][j])
            break;
    }
    for (k = j-1; k >= 0; k--) {
        lscore++;
        if (forest[i][k] >= forest[i][j])
            break;
    }
    for (k = j+1; k <= n-1; k++) {
        rscore++;
        if (forest[i][k] >= forest[i][j])
            break;
    }
    return tscore * bscore * lscore * rscore;
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
    int m = forest.size(), n = forest[0].size(), score, max_score = 0;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++) {
            score = scenic_score(forest, i, j);
            max_score = (score > max_score) ? score : max_score;
        }
    cout << max_score << endl;
}
