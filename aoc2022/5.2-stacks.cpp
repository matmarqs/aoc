#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

/* DEFINITIONS */

void print(std::vector <char> const &a) {
   for (int i = 0; i < (int) a.size(); i++)
       cout << a.at(i) << ' ';
   cout << endl;
}

vector <vector <char>> transpose(vector <vector <char>> matrix, int m, int n) {
    vector <vector <char>> trans; char c;
    for (int j = 0; j < n; j++) {
        trans.push_back(vector <char> ());
        for (int i = m-1; i >= 0; i--) {
            if ((c = matrix[i][j]) != ' ')
                trans[j].push_back(c);
        }
    }
    return trans;
}

vector <vector <char>> make_transstack(int n_stacks, string ss_str) {
    vector <vector <char>> stack;
    stringstream ss; string line;
    ss << ss_str;
    int i = 0;
    while (getline(ss, line) && (!line.empty())) {
        stack.push_back(vector<char> ());
        int s, k;
        for (s = 0; s < n_stacks; s++) {
            k = 1 + 4*s;
            if (k < (int) line.length()) {
                stack[i].push_back(line[k]);
            }
            else
                stack[i].push_back(' ');
        }
        i++;
    }
    return stack;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;   // failure
    }

    ifstream InputFile(argv[1]);

    /* read until end of file */
    string line; stringstream ss;
    int n_stacks = 0, n_lines = 0;
    while (getline(InputFile, line)) {
        if (line.find('1') != line.npos) {
            n_stacks = line[line.find_last_of("0123456789")] - '0';
            break;
        }
        ss << line << endl;
        n_lines++;
    }
    vector <vector <char>> stack = make_transstack(n_stacks, ss.str());
    stack = transpose(stack, n_lines, n_stacks);

    // read movements
    int num, from, to;
    while (getline(InputFile, line)) {
        if (!line.empty()) {
            sscanf(line.c_str(), "move %d from %d to %d", &num, &from, &to);
            from--, to--;   // we index from 0
            char c; int cpnum = num;
            for ( ; num > 0; num--) {
                c = stack[from][stack[from].size() - num];
                stack[to].push_back(c);
            }
            for ( ; cpnum > 0; cpnum--)
                stack[from].pop_back();
        }
    }
    for (int i = 0; i < n_stacks; i++) {
        cout << stack[i].back();
    }
    cout << endl;
}
