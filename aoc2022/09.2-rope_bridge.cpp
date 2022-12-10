#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

/* DEFINITIONS */

struct pos {
    int x;
    int y;
    bool operator< (const pos &that) const {
        if (this->x < that.x) return 1;
        else if (this->x == that.x) return (this->y < that.y);
        else return 0;
    }
};

void move_head(char direction, pos *head) {
    switch (direction) {
        case 'R':
            head->x++;
            break;
        case 'L':
            head->x--;
            break;
        case 'U':
            head->y++;
            break;
        case 'D':
            head->y--;
            break;
        default:
            break;
    }
}

int touching(pos *tail, pos *head) {
    return (abs(head->x - tail->x) <= 1) && (abs(head->y - tail->y) <= 1);
}

int diagonal(pos tail, pos *head, int dx, int dy) {
    tail.x = tail.x + dx, tail.y = tail.y + dy;
    return touching(&tail, head);
}

void move_tail(pos *tail, pos *head) {
    if (head->y == tail->y) {   // same line
        if (head->x - tail->x == 2)
            tail->x++;
        else if (head->x - tail->x == -2)
            tail->x--;
    }
    else if (head->x == tail->x) {  // same column
        if (head->y - tail->y == 2)
            tail->y++;
        else if (head->y - tail->y == -2)
            tail->y--;
    }
    else if (!touching(tail, head)) {  // diagonal move
        if (diagonal(*tail, head, 1, 1))
            tail->x++, tail->y++;
        else if (diagonal(*tail, head, -1, 1))
            tail->x--, tail->y++;
        else if (diagonal(*tail, head, -1, -1))
            tail->x--, tail->y--;
        else if (diagonal(*tail, head, 1, -1))
            tail->x++, tail->y--;
    }
}

void print_map(const pos *tail, const pos *head) {
    for (int y = 4; y >= 0; y--) {
        for (int x = 0; x < 7; x++) {
            char c = 0;
            if (x == 0 && y == 0)
                c = 's';
            if (x == tail->x && y == tail->y)
                c = 'T';
            if (x == head->x && y == head->y)
                c = 'H';
            if (!c)
                c = '.';
            putchar(c);
        }
        putchar('\n');
    }
    putchar('\n');
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;   // failure
    }

    ifstream InputFile(argv[1]);

    /* read until end of file */
    string line;
    char direction; int n_steps;
    pos knots[10]; int i;
    for (i = 0; i < 10; i++)
        knots[i] = {0, 0};
    set <pos> visited;
    while (getline(InputFile, line)) {
        sscanf(line.c_str(), "%c %d", &direction, &n_steps);
        for ( ; n_steps > 0; n_steps--) {
            move_head(direction, &knots[0]);
            for (i = 0; i < 9; i++) {
                move_tail(&knots[i+1], &knots[i]);
            }
            visited.insert(knots[9]);
        }
    }
    cout << visited.size() << endl;

}
