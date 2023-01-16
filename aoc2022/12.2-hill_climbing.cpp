#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <deque>

class vertex {
public:
    char lv;
    //int dist;   // distance from the initial node
    int visited;
    vertex *nbr[4];
    vertex *parent;
    vertex (char lvl) {
        lv = lvl;
        //dist = -1;
        visited = 0;
        parent = NULL;
    }
};

// 0 norte, 1 leste, 2 sul, 3 oeste
int boundary_ok(int m, int n, int i, int j, int dir) {
    int ok;
    switch (dir) {
        case 0:
            ok = (i > 0);
            break;
        case 1:
            ok = (j < n-1);
            break;
        case 2:
            ok = (i < m-1);
            break;
        default:
            ok = (j > 0);
            break;
    }
    return ok;
}

void setup_nodes(std::vector <std::vector <vertex *>> &map) {
    int m = (int) map.size(), n = (int) map[0].size();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < 4; k++) {   // 0 norte, 1 leste, 2 sul, 3 oeste
                vertex *u = map[i][j], *v = NULL;
                if (boundary_ok(m, n, i, j, k)) {
                    switch (k) {
                        case 0:
                            v = map[i-1][j]; break;
                        case 1:
                            v = map[i][j+1]; break;
                        case 2:
                            v = map[i+1][j]; break;
                        default:
                            v = map[i][j-1]; break;
                    }
                    u->nbr[k] = (v->lv <= u->lv + 1) ? v : NULL;
                }
                else {
                    u->nbr[k] = NULL;
                }
            }
}

void refresh_nodes(std::vector <std::vector <vertex *>> &map) {
    int m = (int) map.size(), n = (int) map[0].size();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            map[i][j]->visited = 0, map[i][j]->parent = NULL;
}

int shortest_path
(std::vector <std::vector <vertex *>> &map, int i_e, int j_e, int i_s, int j_s) {
    std::deque <vertex *> queue;
    vertex *v = map[i_s][j_s]; v->visited = 1;
    queue.push_back(v);
    while (!queue.empty()) {
        v = queue.front(); queue.pop_front();
        if (v == map[i_e][j_e])
            return 0;
        for (int n = 0; n < 4; n++) {
            vertex *w = v->nbr[n];
            if (w != NULL && !w->visited) {
                w->visited = 1;
                w->parent = v;
                queue.push_back(w);
            }
        }
    }
    return 1;
}

int shortest_len
(std::vector <std::vector <vertex *>> &map, int i_e, int j_e, int i_s, int j_s) {
    int len = 0;
    vertex *v = map[i_e][j_e];
    while (v != map[i_s][j_s]) {
        v = v->parent;
        len += 1;
    }
    return len;
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
    int i = 0, i_e = 0, j_e = 0;
    std::vector <int> is, js;   // lists of starting positions
    while (std::getline(InputFile, line)) {
        map.push_back(std::vector <vertex *> ());
        for (int j = 0; j < (int) line.length(); j++) {
            char c = line[j];
            if (c == 'S' || c == 'a') {
                is.push_back(i); js.push_back(j);
                c = 'a';
            }
            else if (c == 'E') {
                i_e = i, j_e = j, c = 'z';
            }
            vertex *v = new vertex(c);
            map[i].push_back(v);
        }
        i++;
    }

    setup_nodes(map);
    int shortest = 1000000000;
    for (int l = 0; l < (int) is.size(); l++) {
        if (shortest_path(map, i_e, j_e, is[l], js[l]) == 0) {
            int n = shortest_len(map, i_e, j_e, is[l], js[l]);
            //std::cout << n << std::endl;
            refresh_nodes(map);
            shortest = (n < shortest) ? n : shortest;
        }
    }
    std::cout << shortest << std::endl;

    // free space
    for (int i = 0; i < (int) map.size(); i++)
        for (int j = 0; j < (int) map[i].size(); j++)
            delete map[i][j];
}
