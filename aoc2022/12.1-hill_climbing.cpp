#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>

class vertex {
public:
    char lv;
    int dist;   // distance from the initial node
    int unvisited;
    vertex *nbr[4];
    vertex (char lvl) {
        lv = lvl;
        dist = -1;
        unvisited = 1;
    }
};

/* -1 is infinity */
int my_min(int a, int b) { return a == -1 ? b : (b == -1 ? a : (a > b ? b : a)); }

void setup_nodes(std::vector <std::vector <vertex *>> &map) {
    int m = (int) map.size(), n = (int) map[0].size();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < 4; k++) {
                int p, q;
                if (k < 2)
                    p = 0, q = (k % 2 == 1) ? i : j;
                else
                    p = (k % 2 == 1) ? i : j, q = (k % 2 == 1) ? m-1 : n-1;
                vertex *u = map[i][j], *v = NULL;
                if (p < q) {
                    switch (k) {
                    case 0: v = map[i][j-1]; break; case 1:  v = map[i-1][j]; break;
                    case 2: v = map[i][j+1]; break; default: v = map[i+1][j]; break;
                    }
                    u->nbr[k] = (v->lv <= u->lv + 1) ? v : NULL;
                }
            }
}


vertex *get_unvisited(std::vector <std::vector <vertex *>> &map) {
    for (int i = 0; i < (int) map.size(); i++)
        for (int j = 0; j < (int) map[i].size(); j++)
            if (map[i][j]->unvisited && map[i][j]->dist != -1)
                return map[i][j];
    return NULL;
}


void dijkstra(vertex *u, std::vector <std::vector <vertex *>> &map) {
    u->unvisited = u->dist = 0;
    while (u) {     // while not NULL
        for (vertex *v : u->nbr)
            if (v)  // not NULL
                v->dist = my_min(u->dist + 1, v->dist);
        u->unvisited = 0;
        u = get_unvisited(map);
    }
}


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return EXIT_FAILURE;   // failure
    }

    std::ifstream InputFile(argv[1]);

    std::vector <std::vector <vertex *>> map;

    /* read until end of file */
    std::string line;
    int i = 0, i_s = 0, j_s = 0, i_e = 0, j_e = 0;
    while (std::getline(InputFile, line)) {
        map.push_back(std::vector <vertex *> ());
        for (int j = 0; j < (int) line.length(); j++) {
            char c = line[j];
            if (line[j] == 'S')
                i_s = i, j_s = j, c = 'a';
            else if (line[j] == 'E')
                i_e = i, j_e = j, c = 'z';
            vertex *v = new vertex(c);
            map[i].push_back(v);
        }
        i++;
    }

    setup_nodes(map);
    dijkstra(map[i_s][j_s], map);
    std::cout << map[i_e][j_e]->dist << std::endl;

    // free space
    for (int i = 0; i < (int) map.size(); i++)
        for (int j = 0; j < (int) map[i].size(); j++)
            delete map[i][j];
}
